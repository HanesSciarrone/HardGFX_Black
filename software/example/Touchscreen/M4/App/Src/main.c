
#include "main.h"


#ifdef HARDGFX_HWDSEM_ID_0
#define HARDGFX_HWDSEM_ID_0 0U /* Hardware semaphore 0 */
#endif

int main(void)
{
    /* USER CODE BEGIN Boot_Mode_Sequence_1 */
    /*HW semaphore Clock enable*/
    __HAL_RCC_HSEM_CLK_ENABLE();
    /* Activate HSEM notification for Cortex-M4*/
    HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HARDGFX_HWDSEM_ID_0));
    /**
     * Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
     * perform system initialization (system clock config, external memory configuration.. )
    */
    HAL_PWREx_ClearPendingEvent();
    HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
    /* Clear HSEM flag */
    __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HARDGFX_HWDSEM_ID_0));

    /* USER CODE END Boot_Mode_Sequence_1 */
    /* MCU Configuration */

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Initialize all configured peripherals */

    while (1)
    {
    }

    return 0;
}
