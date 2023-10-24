#include <images1.h>
#include <string.h>

#include "main.h"
#include "images1.h"
#include "images2.h"
#include "hardgfx_rcc.h"
#include "hardgfx_black_lcd.h"

/* ------------------------- Private define ------------------------ */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) // HW semaphore 0
#endif
/* ----------------------------------------------------------------- */

/* ------------------------- Private macro ------------------------- */
/* ----------------------------------------------------------------- */

/* ----------------------- Private variables ----------------------- */

volatile uint32_t reloadFlag = 0;

// Pictures position
uint32_t xPos1 = 0;
uint32_t xPos2 = 160;
uint32_t yPos1 = 0;
uint32_t yPos2 = 32;

/* ----------------------------------------------------------------- */

/* ------------------ Private function prototypes ------------------ */
static void MPUConfig(void);
static void HardGFXCPUCacheEnable(void);
static int32_t HardGFX_BSP_LCD_SetBrightness(const uint32_t brightness);
static void picturePosition(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t index);

/* ----------------------------------------------------------------- */

int main(void)
{
    int32_t retVal = HAL_OK;
    int32_t timeout = 0xFFFF;
    HardGFX_LDC_LayerInit_t layerInit[2] = { 0 };
    uint32_t index = 0;

    // MPU Configuration
    MPUConfig();

    HardGFXCPUCacheEnable();

    // Wait until CPU2 boots and enters in stop mode or timeout
    while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));

    if ( timeout < 0 )
    {
        Error_Handler();
    }
    // MCU Configuration

    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();

    // Configure Clock CPU
    HardGFX_SystemClock_Configure();

    /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of HSEM notification */

    // HW semaphore Clock enable
    __HAL_RCC_HSEM_CLK_ENABLE();
    // Take HSEM
    HAL_HSEM_FastTake(HSEM_ID_0);
    // Release HSEM in order to notify the CPU2(CM4)
    HAL_HSEM_Release(HSEM_ID_0,0);
    // wait until CPU2 wakes up from stop mode
    timeout = 0xFFFF;

    while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));

    if ( timeout < 0 )
    {
        Error_Handler();
    }

    /* Initialize all configured peripherals */
    HardGFX_RCC_GPIO_Init();

    lcdHandler.Instance = LTDC;

    HardGFX_LDC_GPIO_Init(&lcdHandler);
    retVal = HardGFX_LCD_ClockConfig(&lcdHandler);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    retVal = HardGFX_LDC_Init(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    layerInit[0].startX         = 0;
    layerInit[0].endX           = 320;
    layerInit[0].startY         = 0;
    layerInit[0].endY           = 240;
    layerInit[0].pixelFormat    = HARDGFX_LCD_PIXEL_FORMAT_L8;
    layerInit[0].imageWidth     = 320;
    layerInit[0].imageHeight    = 240;
    layerInit[0].alpha          = 255;
    layerInit[0].startAddress   = (uint32_t)&images2;

    layerInit[1].startX         = 160;
    layerInit[1].endX           = 480;
    layerInit[1].startY         = 32;
    layerInit[1].endY           = 272;
    layerInit[1].pixelFormat    = LTDC_PIXEL_FORMAT_RGB565;
    layerInit[0].alpha          = 200;
    layerInit[0].imageWidth     = 320;
    layerInit[0].imageHeight    = 240;
    layerInit[1].startAddress   = (uint32_t)&images1;

    retVal = HardGFX_LCD_Layer_Init(&lcdHandler, layerInit, 2);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    retVal = HardGFX_LCD_Backlight_Init();

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    // CLUT configuration
    HAL_LTDC_ConfigCLUT(&lcdHandler, (uint32_t *)imagesCLUT, 256, 0);

    // Enable CLUT for layer 1
    HAL_LTDC_EnableCLUT(&lcdHandler, 0);

    retVal = HardGFX_BSP_LCD_SetBrightness(100);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    while (1)
    {
        for (index = 0; index < 32; index++)
        {
            // Calculate new picture position
            picturePosition(&xPos1, &yPos1, &xPos2, &yPos2, (index+1));
            // Reconfigure the layer1 position  without Reloading
            HAL_LTDC_SetWindowPosition_NoReload(&lcdHandler, xPos1, yPos1, 0);
            // Reconfigure the layer2 position  without Reloading
            HAL_LTDC_SetWindowPosition_NoReload(&lcdHandler, xPos2, yPos2, 1);

            // Ask for LTDC reload within next vertical blanking
            reloadFlag = 0;
            HAL_LTDC_Reload(&lcdHandler, HARDGFX_LCD_RELOAD_VERTICAL_BLANKING);

            while(reloadFlag == 0) {}
        }
        HAL_Delay(500);

        for (index = 0; index < 32; index++)
        {
            // Calculate new picture position
            picturePosition(&xPos2, &yPos2, &xPos1, &yPos1, (index+1));
            // Reconfigure the layer1 position  without Reloading
            HAL_LTDC_SetWindowPosition_NoReload(&lcdHandler, xPos1, yPos1, 0);
            // Reconfigure the layer2 position  without Reloading
            HAL_LTDC_SetWindowPosition_NoReload(&lcdHandler, xPos2, yPos2, 1);

            // Ask for LTDC reload within next vertical blanking
            reloadFlag = 0;
            HAL_LTDC_Reload(&lcdHandler, HARDGFX_LCD_RELOAD_VERTICAL_BLANKING);

            while(reloadFlag == 0) {}
        }
        HAL_Delay(500);
    }

    return 0;
}

/* MPU Configuration */
static void MPUConfig(void)
{
    MPU_Region_InitTypeDef mpuInit = {0};

    /* Disables the MPU */
    HAL_MPU_Disable();

    /* Initializes and configures the Region and the memory to be protected */
    mpuInit.Enable = MPU_REGION_ENABLE;
    mpuInit.Number = MPU_REGION_NUMBER0;
    mpuInit.BaseAddress = 0x0;
    mpuInit.Size = MPU_REGION_SIZE_4GB;
    mpuInit.SubRegionDisable = 0x87;
    mpuInit.TypeExtField = MPU_TEX_LEVEL0;
    mpuInit.AccessPermission = MPU_REGION_NO_ACCESS;
    mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpuInit.IsShareable = MPU_ACCESS_SHAREABLE;
    mpuInit.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpuInit.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&mpuInit);

    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

static void HardGFXCPUCacheEnable(void)
{
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
}

static int32_t HardGFX_BSP_LCD_SetBrightness(const uint32_t brightness)
{
    int32_t errno = HARDGFX_NONE_ERROR;
    TIM_OC_InitTypeDef configureOC;

    if (HAL_TIM_PWM_Stop(&timHandler, LCD_TIMx_CHANNEL) == HAL_OK)
    {
        configureOC.OCMode = TIM_OCMODE_PWM1;
        configureOC.Pulse = (LCD_TIMX_PERIOD_VALUE * brightness) / 100U;
        configureOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        configureOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        configureOC.OCFastMode = TIM_OCFAST_DISABLE;
        configureOC.OCIdleState = TIM_OCIDLESTATE_RESET;
        configureOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

        if (HAL_TIM_PWM_ConfigChannel(&timHandler, &configureOC, LCD_TIMx_CHANNEL) == HAL_OK)
        {
            if (HAL_TIM_PWM_Start(&timHandler, LCD_TIMx_CHANNEL) != HAL_OK)
            {
                errno = HARDGFX_BLACKLIGHT_ERROR;
            }
        }
        else
        {
            errno = HARDGFX_BLACKLIGHT_ERROR;
        }
    }
    else
    {
        errno = HARDGFX_BLACKLIGHT_ERROR;
    }

    return errno;
}

/*
 * @brief  calculate pictures position.
 *
 * @param[in, out]  x1      Picture1 x position.
 * @param[in, out]  y1      Picture1 y position.
 * @param[in, out]  x2      Picture2 x position.
 * @param[in, out]  y2      Picture2 y position.
 * @param[in]       index
 */

static void picturePosition(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t index)
{
    /* picture1 position */
    *x1 = index*5;
    *y1 = index;

    /* picture2 position */
    *x2 = 160 - index*5;
    *y2 = 32 - index;
}

/**
  * @brief  Reload Event callback.
  *
  * @param[in]  hltdc   Pointer to a handler structure that contains
  *                     the configuration information for the LTDC.
  */
void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc)
{
    reloadFlag = 1;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
