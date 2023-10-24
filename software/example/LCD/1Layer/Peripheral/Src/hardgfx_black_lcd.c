#include <stdlib.h>

#include "hardgfx_black_lcd.h"

/* ------------------------------------------- Private variables ------------------------------------------- */
HardGFX_LCD_HandlerTypeDef lcdHandler = { 0 };
HardGFX_PWM_HandlerTypedef timHandler = { 0 };

/* --------------------------------------------------------------------------------------------------------- */

/* ------------------------------------- Private functions declaration ------------------------------------- */
static void HardGFX_LCD_Backlight_GPIO_Init(void);
static void HardGFX_LCD_Backlight_GPIO_DeInit(void);
/* --------------------------------------------------------------------------------------------------------- */

/* ------------------------------------ Public functions implementation ------------------------------------ */
int32_t HardGFX_LDC_GPIO_Init(HardGFX_LCD_HandlerTypeDef* lcdHandler)
{
    int32_t retVal = HARDGFX_LCD_WRONG_INSTANCE_HANDLER;

    if (lcdHandler->Instance == LTDC)
    {
        GPIO_InitTypeDef gpioInit = {0};

        /* LTDC clock enable */
        __HAL_RCC_LTDC_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        __HAL_RCC_GPIOK_CLK_ENABLE();

        /**LCD GPIO Configuration
        PK5  ------> LTDC_B6
        PI1  ------> LTDC_G6
        PI0  ------> LTDC_G5
        PK4  ------> LTDC_B5
        PJ15 ------> LTDC_B3
        PK6  ------> LTDC_B7
        PK3  ------> LTDC_B4
        PK7  ------> LTDC_DE
        PJ14 ------> LTDC_B2
        PJ12 ------> LTDC_B0
        PI9  ------> LTDC_VSYNC
        PJ13 ------> LTDC_B1
        PI12 ------> LTDC_HSYNC
        PI14 ------> LTDC_CLK
        PK2  ------> LTDC_G7
        PJ11 ------> LTDC_G4
        PJ10 ------> LTDC_G3
        PJ9  ------> LTDC_G2
        PJ0  ------> LTDC_R1
        PJ8  ------> LTDC_G1
        PJ7  ------> LTDC_G0
        PJ6  ------> LTDC_R7
        PI15 ------> LTDC_R0
        PJ1  ------> LTDC_R2
        PJ5  ------> LTDC_R6
        PH9  ------> LTDC_R3
        PJ3  ------> LTDC_R4
        PJ4  ------> LTDC_R5
        */
        gpioInit.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_7|GPIO_PIN_2;
        gpioInit.Mode = GPIO_MODE_AF_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        gpioInit.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOK, &gpioInit);

        gpioInit.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15;
        gpioInit.Mode = GPIO_MODE_AF_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        gpioInit.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOI, &gpioInit);

        gpioInit.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                   |GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_4;
        gpioInit.Mode = GPIO_MODE_AF_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        gpioInit.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOJ, &gpioInit);

        gpioInit.Pin = GPIO_PIN_9;
        gpioInit.Mode = GPIO_MODE_AF_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        gpioInit.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOH, &gpioInit);


        /*Configure LCD_DISP GPIO pin */
        gpioInit.Pin = LCD_DISP_PIN;
        gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(LCD_DISP_GPIO_PORT, &gpioInit);

        /*Configure LCD_INT GPIO pin */
        gpioInit.Pin = LCD_INT_PIN;
        gpioInit.Mode = GPIO_MODE_IT_RISING;
        gpioInit.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(LCD_INT_GPIO_PORT, &gpioInit);

        /*Configure LCD_BL GPIO pin */
        gpioInit.Pin = LCD_BL_PIN;
        gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpioInit);

        gpioInit.Pin = LCD_RST_PIN;
        gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
        gpioInit.Pull = GPIO_NOPULL;
        gpioInit.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(LCD_RST_GPIO_PORT, &gpioInit);

        /*Configure GPIOs pines Output Level */
        HAL_GPIO_WritePin(LCD_DISP_GPIO_PORT, LCD_DISP_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LCD_RST_GPIO_PORT, LCD_RST_PIN, GPIO_PIN_RESET);

        /* Toggle Sw reset of LCD IP */
        __HAL_RCC_LTDC_FORCE_RESET();
        __HAL_RCC_LTDC_RELEASE_RESET();

#if HARDGFX_LCD_INTERRUPT_ENABLE == 1
        /* LTDC interrupt Init */
        HAL_NVIC_SetPriority(LTDC_IRQn, HARDGFX_LCD_IT_PRIORITY, 0);
        HAL_NVIC_EnableIRQ(LTDC_IRQn);
#endif

        retVal = HARDGFX_NONE_ERROR;
    }

    return retVal;
}

void HardGFX_LDC_GPIO_DeInit(HardGFX_LCD_HandlerTypeDef* lcdHandler)
{
    if(lcdHandler->Instance == LTDC)
    {
        /* Peripheral clock disable */
        __HAL_RCC_LTDC_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOK, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_7|GPIO_PIN_2);

        HAL_GPIO_DeInit(GPIOI, GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15);

        HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                              |GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_4);

        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9);

        /*Configure LCD_DISP GPIO pin */
        HAL_GPIO_DeInit(LCD_DISP_GPIO_PORT, LCD_DISP_PIN);

        /*Configure LCD_INT GPIO pin */
        HAL_GPIO_DeInit(LCD_INT_GPIO_PORT, LCD_INT_PIN);

        /*Configure LCD_BL GPIO pin */
        HAL_GPIO_DeInit(LCD_BL_GPIO_PORT, LCD_BL_PIN);

        HAL_GPIO_DeInit(LCD_RST_GPIO_PORT, LCD_RST_PIN);

#if HARDGFX_LCD_INTERRUPT_ENABLE == 1
        HAL_NVIC_DisableIRQ(LTDC_IRQn);
#endif
    }
}

__weak int32_t HardGFX_LCD_ClockConfig(HardGFX_LCD_HandlerTypeDef* lcdHandler)
{
    int32_t retVal = HARDGFX_LCD_WRONG_INSTANCE_HANDLER;

    if (lcdHandler->Instance == LTDC)
    {
        RCC_PeriphCLKInitTypeDef peripheralClock = {0};

        /* LCD clock configuration */
        /* PLL3_VCO Input = HSE_VALUE/PLL3M = 5 Mhz */
        /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 800 Mhz */
        /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 800/83 = 9.63 Mhz */
        /* LTDC clock frequency = PLLLCDCLK = 9.63 Mhz */
        peripheralClock.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
        peripheralClock.PLL3.PLL3M = 5;
        peripheralClock.PLL3.PLL3N = 160;
        peripheralClock.PLL3.PLL3P = 2;
        peripheralClock.PLL3.PLL3Q = 2;
        peripheralClock.PLL3.PLL3R = 83;
        peripheralClock.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
        peripheralClock.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
        peripheralClock.PLL3.PLL3FRACN = 0;

        if (HAL_RCCEx_PeriphCLKConfig(&peripheralClock) != HAL_OK)
        {
            retVal = HARDGFX_LCD_CLOCK_CONFIGURATION_FAIL;
        }
        else
        {
            retVal = HARDGFX_NONE_ERROR;
        }
    }

    return retVal;
}

__weak int32_t HardGFX_LDC_Init(const uint32_t width, const uint32_t height)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    lcdHandler.Instance = LTDC;

    lcdHandler.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    lcdHandler.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    lcdHandler.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    lcdHandler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

    lcdHandler.Init.HorizontalSync = DISPLAY_HSYNC - 1U;
    lcdHandler.Init.VerticalSync = DISPLAY_VSYNC -1U;
    lcdHandler.Init.AccumulatedHBP = (DISPLAY_HSYNC + DISPLAY_HBP -1U);
    lcdHandler.Init.AccumulatedVBP = DISPLAY_VSYNC + DISPLAY_VBP -1U;
    lcdHandler.Init.AccumulatedActiveW = DISPLAY_HSYNC + width + DISPLAY_HBP - 1U;
    lcdHandler.Init.AccumulatedActiveH = DISPLAY_VSYNC + height + DISPLAY_VBP - 1U;
    lcdHandler.Init.TotalWidth = DISPLAY_HSYNC + width + DISPLAY_HBP + DISPLAY_HFP - 1U;
    lcdHandler.Init.TotalHeigh = DISPLAY_VSYNC + height + DISPLAY_VBP + DISPLAY_VFP - 1U;

    lcdHandler.Init.Backcolor.Blue = 0x00;
    lcdHandler.Init.Backcolor.Green = 0x80;
    lcdHandler.Init.Backcolor.Red = 0x00;

    if (HAL_LTDC_Init(&lcdHandler) != HAL_OK)
    {
        retVal = HARDGFX_LCD_INITIALIZATION_FAIL;
    }

    return retVal;
}

__weak int32_t HardGFX_LCD_Layer_Init(HardGFX_LCD_HandlerTypeDef* lcdHandler, HardGFX_LDC_LayerInit_t *layers, const char countLayers)
{
    int32_t retVal = HARDGFX_NULL_POINTER_ARGUMENT;
    LTDC_LayerCfgTypeDef *layerConfig = NULL;
    uint8_t index = 0;

    if (lcdHandler != NULL)
    {
        layerConfig = calloc(countLayers, sizeof(LTDC_LayerCfgTypeDef));

        if (layerConfig != NULL)
        {
            if (lcdHandler->Instance != LTDC)
            {
                retVal = HARDGFX_LCD_WRONG_INSTANCE_HANDLER;
            }
            else
            {
                for (index = 0; index < countLayers; index++)
                {
                    layerConfig[index].WindowX0 = layers[index].startX;
                    layerConfig[index].WindowX1 = layers[index].endX;
                    layerConfig[index].WindowY0 = layers[index].startY;
                    layerConfig[index].WindowY1 = layers[index].endY;
                    layerConfig[index].PixelFormat = layers[index].pixelFormat;
                    layerConfig[index].Alpha = layers[index].alpha;
                    layerConfig[index].Alpha0 = 0;
                    layerConfig[index].BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
                    layerConfig[index].BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
                    layerConfig[index].FBStartAdress = layers[index].startAddress;
                    layerConfig[index].ImageWidth = layers[index].imageWidth;
                    layerConfig[index].ImageHeight = layers[index].imageHeight;
                    layerConfig[index].Backcolor.Blue = 0;
                    layerConfig[index].Backcolor.Green = 0;
                    layerConfig[index].Backcolor.Red = 0;

                    retVal = HAL_LTDC_ConfigLayer(lcdHandler, (layerConfig + index), index);

                    if (retVal != HAL_OK)
                    {
                        retVal = HARDGFX_LCD_LAYER_CONFIGURATION_FAIL;
                        break;
                    }

                    retVal = HARDGFX_NONE_ERROR;
                }
            }
        }
    }

    if (retVal != HARDGFX_NULL_POINTER_ARGUMENT)
    {
        free(layerConfig);
    }

    return retVal;
}

/**
  * @brief  Initialize Timer in PWM mode
  */
int32_t HardGFX_LCD_Backlight_Init(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    TIM_ClockConfigTypeDef clockSource = {0};
    TIM_MasterConfigTypeDef masterConfiguration = {0};
    TIM_OC_InitTypeDef configureOC = {0};
    TIM_BreakDeadTimeConfigTypeDef breakDeadTime = {0};

    HardGFX_LCD_Backlight_GPIO_Init();

    /*
     * APB timer clock = 2 x APB2 peripheral Clock = 240 MHz
     * PWM_frequency = APB timer clock / ((LCD_TIMX_PRESCALER_VALUE +1) + LCD_TIMX_PERIOD_VALUE)
     * PWM_frequency = 240MHz/(5 + 60000) = 800Hz
     */
    timHandler.Instance = LCD_TIMx;
    timHandler.Init.Prescaler = LCD_TIMX_PRESCALER_VALUE;
    timHandler.Init.CounterMode = TIM_COUNTERMODE_UP;
    timHandler.Init.Period = LCD_TIMX_PERIOD_VALUE;
    timHandler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timHandler.Init.RepetitionCounter = 0;
    timHandler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&timHandler) == HAL_OK)
    {
        clockSource.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

        if (HAL_TIM_ConfigClockSource(&timHandler, &clockSource) == HAL_OK)
        {
            if (HAL_TIM_PWM_Init(&timHandler) == HAL_OK)
            {
                masterConfiguration.MasterOutputTrigger = TIM_TRGO_RESET;
                masterConfiguration.MasterOutputTrigger2 = TIM_TRGO2_RESET;
                masterConfiguration.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

                if (HAL_TIMEx_MasterConfigSynchronization(&timHandler, &masterConfiguration) == HAL_OK)
                {
                    configureOC.OCMode = TIM_OCMODE_PWM1;
                    configureOC.Pulse = LCD_TIMX_PERIOD_VALUE;
                    configureOC.OCPolarity = TIM_OCPOLARITY_HIGH;
                    configureOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
                    configureOC.OCFastMode = TIM_OCFAST_DISABLE;
                    configureOC.OCIdleState = TIM_OCIDLESTATE_RESET;
                    configureOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

                    if (HAL_TIM_PWM_ConfigChannel(&timHandler, &configureOC, LCD_TIMx_CHANNEL) == HAL_OK)
                    {
                        breakDeadTime.OffStateRunMode = TIM_OSSR_DISABLE;
                        breakDeadTime.OffStateIDLEMode = TIM_OSSI_DISABLE;
                        breakDeadTime.LockLevel = TIM_LOCKLEVEL_OFF;
                        breakDeadTime.DeadTime = 0;
                        breakDeadTime.BreakState = TIM_BREAK_DISABLE;
                        breakDeadTime.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
                        breakDeadTime.BreakFilter = 0;
                        breakDeadTime.Break2State = TIM_BREAK2_DISABLE;
                        breakDeadTime.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
                        breakDeadTime.Break2Filter = 0;
                        breakDeadTime.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

                        if (HAL_TIMEx_ConfigBreakDeadTime(&timHandler, &breakDeadTime) != HAL_OK)
                        {
                            retVal = HARDGFX_PWM_BREAK_DEAD_TIME_INITIALIZATION_FAIL;
                        }
                    }
                    else
                    {
                        retVal = HARDGFX_PWM_CHANNEL_CONFIGURATION_FAIL;
                    }
                }
                else
                {
                    retVal = HARDGFX_PWM_MASTER_CONFIGURATION_FAIL;
                }
            }
            else
            {
                retVal = HARDGFX_PWM_INITIALIZATION_FAIL;
            }
        }
        else
        {
            retVal = HARDGFX_PWM_CLOCK_INITIALIZATION_FAIL;
        }
    }
    else
    {
        retVal = HARDGFX_PWM_BASE_INITIALIZATION_FAIL;
    }

    return retVal;
}

/**
  * @brief  De-Initializes Timer in PWM mode
  */
void HardGFX_LCD_Backlight_DeInit(void)
{
    HAL_TIM_PWM_DeInit(&timHandler);
    HardGFX_LCD_Backlight_GPIO_DeInit();
}
/* --------------------------------------------------------------------------------------------------------- */



/* ------------------------------------ Private functions implementation ----------------------------------- */

/**
  * @brief  Initializes GPIO timer.
  */
static void HardGFX_LCD_Backlight_GPIO_Init(void)
{
    GPIO_InitTypeDef gpioInit;

    LCD_BL_CTRL_GPIO_CLK_ENABLE();

    // TIMx Peripheral clock enable
    LCD_TIMx_CLK_ENABLE();

    // Timer gpio configuration
    gpioInit.Mode      = GPIO_MODE_AF_PP;
    gpioInit.Pull      = GPIO_NOPULL;
    gpioInit.Speed     = GPIO_SPEED_FREQ_MEDIUM;
    gpioInit.Alternate = LCD_TIMx_CHANNEL_AF;
    gpioInit.Pin       = LCD_BL_PIN;

    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpioInit);
}

/**
  * @brief  De-Initializes GPIO timer.
  */
static void HardGFX_LCD_Backlight_GPIO_DeInit(void)
{
    /* TIMx Peripheral clock enable */
    LCD_BL_CTRL_GPIO_CLK_DISABLE();

    HAL_GPIO_DeInit(LCD_BL_GPIO_PORT, LCD_BL_PIN);
}
/* --------------------------------------------------------------------------------------------------------- */
