#include "main.h"

/* ------------------------- Private define ------------------------ */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) // HW semaphore 0
#endif
/* ----------------------------------------------------------------- */

int main(void)
{
    // HW semaphore Clock enable
    __HAL_RCC_HSEM_CLK_ENABLE();

    // Activate HSEM notification for Cortex-M4
    HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

    /*
    Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
    perform system initialization (system clock config, external memory configuration.. )
    */
    HAL_PWREx_ClearPendingEvent();
    HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);

    // Clear HSEM flag
    __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

    /* MCU Configuration--------------------------------------------------------*/

    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();

    while (1)
    {
    }

    return 0;
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
