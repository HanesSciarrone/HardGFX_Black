#include "hardgfx_rcc.h"
#include "main.h"

/* -------------- Private functions ------------- */

void HardGFX_SystemClock_Configure(void)
{
    RCC_OscInitTypeDef oscInitStruct = {0};
    RCC_ClkInitTypeDef clkInitStruct = {0};

    // Supply configuration update enable
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY));

    // Macro to configure the PLL clock source
    __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

    // Initializes the RCC Oscillators
    oscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscInitStruct.HSEState = RCC_HSE_ON;
    oscInitStruct.PLL.PLLState = RCC_PLL_ON;
    oscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    oscInitStruct.PLL.PLLM = 5;
    oscInitStruct.PLL.PLLN = 160;
    oscInitStruct.PLL.PLLP = 2;
    oscInitStruct.PLL.PLLQ = 4;
    oscInitStruct.PLL.PLLR = 2;
    oscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    oscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    oscInitStruct.PLL.PLLFRACN = 0;

    if (HAL_RCC_OscConfig(&oscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    // Initializes the CPU, AHB and APB buses clocks
    clkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
    clkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    clkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    clkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    clkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    clkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    clkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&clkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }

    /*
     * Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
     *       (GPIO, SPI, FMC, QSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
     *
     *       The I/O Compensation Cell activation  procedure requires :
     *     - The activation of the CSI clock.
     *     - The activation of the SYSCFG clock.
     *     - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR.
    */

     // Activate CSI clock. It is mandatory for I/O Compensation Cell
     __HAL_RCC_CSI_ENABLE() ;

     // Enable SYSCFG clock. It is mandatory for I/O Compensation Cell
     __HAL_RCC_SYSCFG_CLK_ENABLE() ;

     // Enables the I/O Compensation Cell
     HAL_EnableCompensationCell();

}

void HardGFX_RCC_GPIO_Init(void)
{
    // GPIO Ports Clock Enable
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
}
