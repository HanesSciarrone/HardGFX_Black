/*
 * hardgfx_black_sdram.c
 *
 *  Created on: Feb 17, 2023
 *      Author: hanes
 */

#include "hardgfx_black_sdram.h"


HardGFX_SDRAM_HandleTypeDef hsdram;
static MDMA_HandleTypeDef mdmaHandler;
static uint8_t peripheralInitialized = 0;
static SDRAM_Context_t regMode;

/* ------------------------------------- Private functions declaration ------------------------------------- */

/* --------------------------------------------------------------------------------------------------------- */

int32_t HardGFX_SDRAM_Periphreal(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    retVal = HardGFX_SDRAM_GPIO_Init();

    if (retVal == HARDGFX_NONE_ERROR)
    {
        retVal = HardGFX_SDRAM_Init();

        if (retVal == HARDGFX_NONE_ERROR)
        {
            /* External memory mode register configuration */
            regMode.targetBank      = FMC_SDRAM_CMD_TARGET_BANK2;
            regMode.refreshMode     = SDRAM_AUTOREFRESH_MODE_CMD;
            regMode.refreshRate     = SDRAM_REFRESH_COUNT;
            regMode.burstLength     = SDRAM_BURST_LENGTH_1;
            regMode.burstType       = SDRAM_BURST_TYPE_SEQUENTIAL;
            regMode.casLatency      = SDRAM_CAS_LATENCY_2;
            regMode.operationMode   = SDRAM_OPERATING_MODE_STANDARD;
            regMode.writeBurstMode  = SDRAM_WRITEBURST_MODE_SINGLE;

            /* SDRAM initialization sequence */
            if(SDRAM_Init(&hsdram, &regMode) != SDRAM_OK)
            {
                retVal = HARDGFX_SDRAM_INITIALIZATION_FAIL;
            }
        }
    }

    return retVal;
}

int32_t HardGFX_SDRAM_Init(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    FMC_SDRAM_TimingTypeDef sdramTiming = {0};

    /* Perform the SDRAM2 memory initialization sequence */
    hsdram.Instance = FMC_SDRAM_DEVICE;

    /* SDRAM2.Init */
    hsdram.Init.SDBank = FMC_SDRAM_BANK2;
    hsdram.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
    hsdram.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
    hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
    hsdram.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;

    /* SDRAM Timing */
    sdramTiming.LoadToActiveDelay = 2;
    sdramTiming.ExitSelfRefreshDelay = 7;
    sdramTiming.SelfRefreshTime = 5;
    sdramTiming.RowCycleDelay = 7;
    sdramTiming.WriteRecoveryTime = 3;
    sdramTiming.RPDelay = 2;
    sdramTiming.RCDDelay = 2;

    if (HAL_SDRAM_Init(&hsdram, &sdramTiming) != HAL_OK)
    {
        retVal = HARDGFX_SDRAM_INITIALIZATION_FAIL;
    }

    return retVal;
}

int32_t HardGFX_SDRAM_DeInit(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    if (HAL_SDRAM_DeInit(&hsdram) != HAL_OK)
    {
        retVal = HARDGFX_SDRAM_DESINITIALIZATION_FAIL;
    }

    return retVal;
}

int32_t HardGFX_SDRAM_GPIO_Init(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    GPIO_InitTypeDef gpioInit= {0};
    RCC_PeriphCLKInitTypeDef peripheralClockInit = {0};

    if (!peripheralInitialized)
    {
        /*
         * Setting FMC clock with PLL2:
         *
         * PLL2_VCO Input = HSE_VALUE/PLL2_M = 5 Mhz
         * PLL2_VCO Output = PLL2_VCO Input * PLL_N = 800 Mhz
         * FMC Kernel Clock = PLL2_VCO Output/PLL_R = 800/4 = 200 Mhz
         * Maximum FMC clock is 100MHz don't matter the PLL configuration.
         * See the reference manual RM0399 for more information.
         */
        peripheralClockInit.PeriphClockSelection = RCC_PERIPHCLK_FMC;
        peripheralClockInit.PLL2.PLL2M = 5;
        peripheralClockInit.PLL2.PLL2N = 160;
        peripheralClockInit.PLL2.PLL2P = 2;
        peripheralClockInit.PLL2.PLL2Q = 2;
        peripheralClockInit.PLL2.PLL2R = 4;
        peripheralClockInit.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
        peripheralClockInit.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
        peripheralClockInit.FmcClockSelection = RCC_FMCCLKSOURCE_PLL;

        if (HAL_RCCEx_PeriphCLKConfig(&peripheralClockInit) == HAL_OK)
        {
            /* Enable FMC clock */
            __HAL_RCC_FMC_CLK_ENABLE();

            /* Enable MDMA controller clock */
            __HAL_RCC_MDMA_CLK_ENABLE();

            /* Enable GPIOs clock */
            __HAL_RCC_GPIOD_CLK_ENABLE();
            __HAL_RCC_GPIOE_CLK_ENABLE();
            __HAL_RCC_GPIOF_CLK_ENABLE();
            __HAL_RCC_GPIOG_CLK_ENABLE();
            __HAL_RCC_GPIOH_CLK_ENABLE();

            /** FMC GPIO Configuration
             *
             * PD0   ------> FMC_D2
             * PD1   ------> FMC_D3
             * PD8   ------> FMC_D13
             * PD9   ------> FMC_D14
             * PD10   ------> FMC_D15
             * PD14   ------> FMC_D0
             * PD15   ------> FMC_D1
             *
             * PE0   ------> FMC_NBL0
             * PE1   ------> FMC_NBL1
             * PE7   ------> FMC_D4
             * PE8   ------> FMC_D5
             * PE9   ------> FMC_D6
             * PE10   ------> FMC_D7
             * PE11   ------> FMC_D8
             * PE12   ------> FMC_D9
             * PE13   ------> FMC_D10
             * PE14   ------> FMC_D11
             * PE15   ------> FMC_D12
             *
             * PF0   ------> FMC_A0
             * PF1   ------> FMC_A1
             * PF2   ------> FMC_A2
             * PF3   ------> FMC_A3
             * PF4   ------> FMC_A4
             * PF5   ------> FMC_A5
             * PF11   ------> FMC_SDNRAS
             * PF12   ------> FMC_A6
             * PF13   ------> FMC_A7
             * PF14   ------> FMC_A8
             * PF15   ------> FMC_A9
             *
             * PG0   ------> FMC_A10
             * PG1   ------> FMC_A11
             * PG4   ------> FMC_BA0
             * PG5   ------> FMC_BA1
             * PG8   ------> FMC_SDCLK
             * PG15   ------> FMC_SDNCAS
             *
             * PH5   ------> FMC_SDNWE
             * PH6   ------> FMC_SDNE1
             * PH7   ------> FMC_SDCKE1
            */
            gpioInit.Mode = GPIO_MODE_AF_PP;
            gpioInit.Pull = GPIO_PULLUP;
            gpioInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
            gpioInit.Alternate = GPIO_AF12_FMC;

            gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15;
            HAL_GPIO_Init(GPIOD, &gpioInit);

            gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
            HAL_GPIO_Init(GPIOE, &gpioInit);

            gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
            HAL_GPIO_Init(GPIOF, &gpioInit);

            gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
            HAL_GPIO_Init(GPIOG, &gpioInit);

            gpioInit.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
            HAL_GPIO_Init(GPIOH, &gpioInit);


            /* Configure common MDMA parameters */

            /* Configure MDMA channel MDMA_Channel0 */
            /* Configure MDMA request hmdma on MDMA_Channel0 */
            mdmaHandler.Instance = HARDGFX_MDMAx_CHANNEL;
            mdmaHandler.Init.Request = MDMA_REQUEST_SW;
            mdmaHandler.Init.TransferTriggerMode = MDMA_BLOCK_TRANSFER;
            mdmaHandler.Init.Priority = MDMA_PRIORITY_HIGH;
            mdmaHandler.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
            mdmaHandler.Init.SourceInc = MDMA_SRC_INC_WORD;
            mdmaHandler.Init.DestinationInc = MDMA_DEST_INC_WORD;
            mdmaHandler.Init.SourceDataSize = MDMA_SRC_DATASIZE_WORD;
            mdmaHandler.Init.DestDataSize = MDMA_DEST_DATASIZE_WORD;
            mdmaHandler.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
            mdmaHandler.Init.BufferTransferLength = 128;
            mdmaHandler.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;
            mdmaHandler.Init.DestBurst = MDMA_DEST_BURST_SINGLE;
            mdmaHandler.Init.SourceBlockAddressOffset = 0;
            mdmaHandler.Init.DestBlockAddressOffset = 0;

            /* Associate the DMA handle */
            __HAL_LINKDMA(&hsdram, hmdma, mdmaHandler);

            /* Deinitialize the stream for new transfer */
            HAL_MDMA_DeInit(&mdmaHandler);

            if (HAL_MDMA_Init(&mdmaHandler) == HAL_OK)
            {
                /* MDMA interrupt initialization */
                /* MDMA_IRQn interrupt configuration */
                HAL_NVIC_SetPriority(HARDGFX_MDMDx_IRQn, 15, 0);
                HAL_NVIC_EnableIRQ(HARDGFX_MDMDx_IRQn);
                peripheralInitialized = 1;
            }
            else
            {
                retVal = HARDGFX_MDMA_INITIALIZATION_FAIL;
            }
        }
        else
        {
            retVal = HARDGFX_SDRAM_CLOCK_CONFIGURATION_FAIL;
        }
    }

    return retVal;
}

void HardGFX_SDRAM_GPIO_DeInit(void)
{
    if (peripheralInitialized)
    {
        peripheralInitialized = 0;

        /* Disable GPIOs clock */
        __HAL_RCC_FMC_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_15);
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);
        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

        /* Disable NVIC configuration for DMA interrupt */
        HAL_NVIC_DisableIRQ(HARDGFX_MDMDx_IRQn);

        /* Deinitialize the stream for new transfer */
        mdmaHandler.Instance = HARDGFX_MDMAx_CHANNEL;
        HAL_MDMA_DeInit(&mdmaHandler);
    }
}

/**
  * @brief  This function handles SDRAM MDMA interrupt request.
  */
void HardGFX_MDMA_IRQHandler(void)
{
    HAL_MDMA_IRQHandler(&mdmaHandler);
}
