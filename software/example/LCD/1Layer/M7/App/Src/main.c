#include <string.h>

#include "main.h"
#include "images.h"
#include "hardgfx_rcc.h"
#include "hardgfx_black_lcd.h"

/* ------------------------- Private define ------------------------ */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) // HW semaphore 0
#endif
/* ----------------------------------------------------------------- */

/* ------------------------- Private macro ------------------------- */
#define BUFFER_SIZE            ((uint32_t)0x200)
#define BUFFER_SIZE_IN_BYTES   BUFFER_SIZE*4
#define WRITE_READ_ADDR        ((uint32_t)0x00000000)
/* ----------------------------------------------------------------- */

/* ----------------------- Private variables ----------------------- */
/* ----------------------------------------------------------------- */

/* ------------------ Private function prototypes ------------------ */
static void MPUConfig(void);
static void HardGFXCPUCacheEnable(void);
static int32_t HardGFX_BSP_LCD_SetBrightness(const uint32_t brightness);
/* ----------------------------------------------------------------- */

int main(void)
{
    int32_t retVal = HAL_OK;
    int32_t timeout = 0xFFFF;
    HardGFX_LDC_LayerInit_t layerInit = { 0 };

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

    layerInit.startX        = 0;
    layerInit.endX          = DISPLAY_WIDTH;
    layerInit.startY        = 0;
    layerInit.endY          = DISPLAY_HEIGHT;
    layerInit.pixelFormat   = HARDGFX_LCD_PIXEL_FORMAT_RGB565;
    layerInit.imageWidth    = DISPLAY_WIDTH;
    layerInit.imageHeight   = DISPLAY_HEIGHT;
    layerInit.startAddress  = (uint32_t)&images;

    retVal = HardGFX_LCD_Layer_Init(&lcdHandler, &layerInit, 1);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    retVal = HardGFX_LCD_Backlight_Init();

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    retVal = HardGFX_BSP_LCD_SetBrightness(100);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    HAL_Delay(10000);

    retVal = HardGFX_BSP_LCD_SetBrightness(20);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    while (1)
    {
    }

    return 0;
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

/* MPU Configuration */
void MPUConfig(void)
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
