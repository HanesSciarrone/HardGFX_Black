#include "main.h"
#include "hardgfx_rcc.h"

/* ------------------------- Private define ------------------------ */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) // HW semaphore 0
#endif
/* ----------------------------------------------------------------- */


/* ------------------ Private function prototypes ------------------ */
static void MPU_Config(void);
static void HardGFX_CPU_Cache_Enable(void);
/* ----------------------------------------------------------------- */

int main(void)
{
    uint32_t errno = HAL_OK;
    int32_t timeout = 0xFFFF;

    // MPU Configuration
    MPU_Config();

    HardGFX_CPU_Cache_Enable();

    // Wait until CPU2 boots and enters in stop mode or timeout
    while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));

    if ( timeout < 0 )
    {
        Error_Handler();
    }
    // MCU Configuration

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

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

    while (1)
    {
    }

    return 0;
}

static void HardGFX_CPU_Cache_Enable(void)
{
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
}


/* MPU Configuration */
void MPU_Config(void)
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

    /* Initializes and configures the Region and the memory to be protected */
    mpuInit.Number = MPU_REGION_NUMBER1;
    mpuInit.BaseAddress = 0xD0000000;
    mpuInit.Size = MPU_REGION_SIZE_32MB;
    mpuInit.SubRegionDisable = 0x0;
    mpuInit.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpuInit.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpuInit.IsCacheable = MPU_ACCESS_CACHEABLE;

    HAL_MPU_ConfigRegion(&mpuInit);
    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

void ErrorHandler(void)
{
    __disable_irq();

    while (1)
    {
    }
}
