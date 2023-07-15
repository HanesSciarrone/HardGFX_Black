/*
 * hardgfx_black_bus.c
 *
 *  Created on: May 30, 2023
 *      Author: hanes
 */

#include "hardgfx_black_bus.h"

/* -------------------------------------------- Private defines -------------------------------------------- */
#define BUS_I2C_SPEED_FREQ_STANDARD                 0U  // 100KHz maximum
#define BUS_I2C_SPEED_FREQ_FAST                     1U  // 400KHz maximum
#define BUS_I2C_SPEED_FREQ_FAST_PLUS                2U  // 1MHz maximum
#define BUS_I2C_SPEED_MODE                          3U  // Quantity speed mode
#define SIZE_BUS_I2C_TIMING_NBR                     128U

#define MAX_BUS_I2C_PRESC                           16U
#define MAX_BUS_I2C_SCLDEL                          16U
#define MAX_BUS_I2C_SDADEL                          16U
#define MAX_SIZE_BUS_I2C_SCLL                       256U
#define MAX_SIZE_BUS_I2C_SCLH                       256U
#define MIN_BUS_I2C_ANALOG_FILTER_DELAY             50U
#define MAX_BUS_I2C_ANALOG_FILTER_DELAY             260U
#define SEC2NSEC                                1000000000UL

/* -------------------------------------- Structure types declaration -------------------------------------  */
struct  i2cFeaturesStruct
{
    uint32_t frequency;     // Frecuency in Hz
    uint32_t freqMin;       // Minimum frequency in Hz
    uint32_t freqMax;       // Maximum frequency in Hz
    uint32_t tHdDataMin;    // Minimum Data Hold time in ns
    uint32_t tVdDataMax;    // Maximum Valid Data Hold time in ns
    uint32_t tSuDataMin;    // Minimum Setup Up Data Hold time in ns
    uint32_t tLowSCLMin;    // Minimum low time of SCL clock in ns
    uint32_t tHighSCLMin;   // Minimum high time of SCL clock in ns
    uint32_t tRiseMax;      // Maximum rise time in ns
    uint32_t tFallMax;      // Maximum fall time in ns
    uint32_t dnf;           // Digital noise filter coefficient
};

struct i2cTimingRegisterStruct
{
    uint32_t presc;
    uint32_t scldel;
    uint32_t sdadel;
    uint32_t highSCL;
    uint32_t lowSCL;
};

/* ------------------------------------- Private variables declaration ------------------------------------- */
static const struct i2cFeaturesStruct i2cFeature[BUS_I2C_SPEED_MODE] =
{
    {
        .frequency = 100000,
        .freqMin = 1,
        .freqMax = 100000,
        .tHdDataMin = 0,
        .tVdDataMax = 3450,
        .tSuDataMin = 250,
        .tLowSCLMin = 4700,
        .tHighSCLMin = 4000,
        .tRiseMax = 1000,
        .tFallMax = 300,
        .dnf = BUS_I2C_DIGITAL_FILTER_COEFICIENTE
    },
    {
        .frequency = 400000,
        .freqMin = 100001,
        .freqMax = 400000,
        .tHdDataMin = 0,
        .tVdDataMax = 900,
        .tSuDataMin = 100,
        .tLowSCLMin = 1300,
        .tHighSCLMin = 600,
        .tRiseMax = 300,
        .tFallMax = 300,
        .dnf = BUS_I2C_DIGITAL_FILTER_COEFICIENTE

    },
    {
        .frequency = 1000000,
        .freqMin = 400001,
        .freqMax = 1000000,
        .tHdDataMin = 0,
        .tVdDataMax = 450,
        .tSuDataMin = 50,
        .tLowSCLMin = 500,
        .tHighSCLMin = 260,
        .tRiseMax = 120,
        .tFallMax = 120,
        .dnf = BUS_I2C_DIGITAL_FILTER_COEFICIENTE
    }
};

static struct i2cTimingRegisterStruct i2cTiming[SIZE_BUS_I2C_TIMING_NBR] = { 0 };
static uint32_t i2cTimingNBR = 0;
HardGFXBusHandlerTypeDef i2cHandler = { 0 };

/* ------------------------------------- Private functions declaration ------------------------------------- */
static int32_t I2CGPIOInit(void);
static void I2CGPIODeInit(void);
static int32_t I2CInit(void);
static int32_t I2CWriteRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint16_t memoryAddressSize, const uint8_t *data, const uint16_t length);
static int32_t I2CReadRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint16_t memoryAddressSize, uint8_t *data, const uint16_t length);
static uint32_t GetI2CTiming(const uint32_t i2cSrcFreq, const uint32_t i2cFreq);
static void ComputePRESCTimeSCLDELTimeSDADEL(const uint32_t i2cSrcFreq, const uint32_t speedMode);
static uint32_t ComputeSCLLandSCLH(const uint32_t i2cSrcFreq, const uint32_t speedMode);


/* ------------------------------------ Global function implementations ------------------------------------ */

/*
 * @brief  Initializes BUS
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
int32_t HardGFXBusInit(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    i2cHandler.Instance = BUS_I2C;

    if (HAL_I2C_GetState(&i2cHandler) == HAL_I2C_STATE_RESET)
    {
        retVal = I2CGPIOInit();

        if (retVal != HARDGFX_NONE_ERROR)
        {
            return retVal;
        }

        retVal = I2CInit();
    }

    return retVal;
}

/*
 * @brief  Initializes BUS used in the touch screen.
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
int32_t HardGFXBusDeInit(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    I2CGPIODeInit();

    if (HAL_I2C_DeInit(&i2cHandler) != HAL_OK)
    {
        retVal = HARDGFX_BUS_DESINITIALIZATION_FAIL;
    }

    return retVal;
}

/*
 * @brief  Write a 8bit value in a register of the device with BUS.
 *
 * @param[in]  deviceAddress    Device address on Bus.
 * @param[in]  registerAddress  The target register address to write.
 * @param[in]  data             The target register value to be written.
 * @param[in]  length           Buffer size to be written.
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
int32_t HardGFXBusWriteRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint8_t *data, const uint16_t length)
{
    uint32_t retVal = HARDGFX_NONE_ERROR;

    retVal = I2CWriteRegister(deviceAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, data, length);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        if (HAL_I2C_GetError(&i2cHandler) == HAL_I2C_ERROR_AF)
        {
            retVal = HARDGFX_BUS_ACKNOWLEDGE_FAILURE;
        }
        else
        {
            retVal = HARDGFX_BUS_PERIPHERAL_FAILURE;
        }
    }

    return retVal;
}

/*
 * @brief  Read a 8bit value in a register of the device with BUS.
 *
 * @param[in]       deviceAddress    Device address on Bus.
 * @param[in]       registerAddress  The target register address to write.
 * @param[in, out]  data             Data buffer.
 * @param[in]       length           Buffer size to be written.
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
int32_t HardGFXBusReadRegister(const uint16_t deviceAddress, const uint16_t registerAddress, uint8_t *data, const uint16_t length)
{
    uint32_t retVal = HARDGFX_NONE_ERROR;

    retVal = I2CReadRegister(deviceAddress, registerAddress, I2C_MEMADD_SIZE_8BIT, data, length);

    if (retVal != HARDGFX_NONE_ERROR)
    {
        if (HAL_I2C_GetError(&i2cHandler) == HAL_I2C_ERROR_AF)
        {
            retVal = HARDGFX_BUS_ACKNOWLEDGE_FAILURE;
        }
        else
        {
            retVal = HARDGFX_BUS_PERIPHERAL_FAILURE;
        }
    }

    return retVal;
}

/*
 * @brief  Checks if target device is ready for communication.
 *
 * @param[in]  deviceAddress    Target device address
 * @param[in]  retries          Retries number
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
int32_t HardGFXBusIsReady(const uint16_t deviceAddress, uint32_t retries)
{
    uint32_t retVal = HARDGFX_NONE_ERROR;

    if(HAL_I2C_IsDeviceReady(&i2cHandler, deviceAddress, retries, 1000) != HAL_OK)
    {
        retVal = HARDGFX_BUS_BUSY;
    }

    return retVal;
}

/*
 * @brief  Get the current count tick of the MCU.
 *
 * @retval Numbers tick.
 */
uint32_t HardGFXBusGetTick(void)
{
    return HAL_GetTick();
}



/* ------------------------------------ Private function implementations ----------------------------------- */

/*
 * @brief Initialize the GPIO I2C peripheral used to Touch screen.
 *
 * @retval Return 0 if it was success or a negative number in the case fail.
 */
static int32_t I2CGPIOInit(void)
{
    GPIO_InitTypeDef gpioInit = { 0 };
    RCC_PeriphCLKInitTypeDef peripheralClockInit = { 0 };

    if (i2cHandler.Instance != BUS_I2C)
    {
        return HARDGFX_BUS_WRONG_INSTANCE_HANDLER;
    }

    // Initializes the peripherals clock.
    peripheralClockInit.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
    peripheralClockInit.I2c4ClockSelection = RCC_I2C4CLKSOURCE_D3PCLK1;

    if (HAL_RCCEx_PeriphCLKConfig(&peripheralClockInit) != HAL_OK)
    {
        return HARDGFX_BUS_CLOCK_INITIALIZATION_FAIL;
    }

    BUS_I2C_GPIO_CLK_ENABLE();

    /*
    * I2C4 GPIO Configuration
    * PD12     ------> I2C4_SCL
    * PD13     ------> I2C4_SDA
    */
    gpioInit.Pin = BUS_I2C_SCL_PIN;
    gpioInit.Mode = GPIO_MODE_AF_OD;
    gpioInit.Pull = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioInit.Alternate = GPIO_AF4_I2C4;
    HAL_GPIO_Init(BUS_I2C_SCL_GPIO_PORT, &gpioInit);

    gpioInit.Pin = BUS_I2C_SDA_PIN;
    gpioInit.Mode = GPIO_MODE_AF_OD;
    gpioInit.Pull = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioInit.Alternate = GPIO_AF4_I2C4;
    HAL_GPIO_Init(BUS_I2C_SDA_GPIO_PORT, &gpioInit);

    /* I2C4 clock enable */
    BUS_I2C_CLK_ENABLE();

    return HARDGFX_NONE_ERROR;
}

/*
 * @brief Des-initialize the GPIO I2C peripheral used to Touch screen.
 */
static void I2CGPIODeInit(void)
{

    if(i2cHandler.Instance != BUS_I2C)
    {
        // Peripheral clock disable.
        BUS_I2C_CLK_DISABLE();

        /*
        * I2C4 GPIO Configuration
        * PD12     ------> I2C4_SCL
        * PD13     ------> I2C4_SDA
        */
        HAL_GPIO_DeInit(BUS_I2C_SCL_GPIO_PORT, BUS_I2C_SCL_PIN);
        HAL_GPIO_DeInit(BUS_I2C_SDA_GPIO_PORT, BUS_I2C_SDA_PIN);
    }
}

/*
 * @brief Initialize the I2C peripheral used to Touch screen.
 *
 * @retval Return 0 if it was successful or a negative number in otherwise.
 */
static int32_t I2CInit(void)
{
    i2cHandler.Instance = BUS_I2C;
    i2cHandler.Init.Timing = GetI2CTiming(HAL_RCCEx_GetD3PCLK1Freq(), BUS_I2C_FREQUENCY);
    i2cHandler.Init.OwnAddress1 = 0;
    i2cHandler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2cHandler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2cHandler.Init.OwnAddress2 = 0;
    i2cHandler.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    i2cHandler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2cHandler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&i2cHandler) != HAL_OK)
    {
      return HARDGFX_BUS_INITIALIZATION_FAIL;
    }

    // Configure Analogue filter
    if (HAL_I2CEx_ConfigAnalogFilter(&i2cHandler, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
      return HARDGFX_BUS_ANALOG_FILTER_INITIALIZATION_FAIL;
    }

    // Configure Digital filter
    if (HAL_I2CEx_ConfigDigitalFilter(&i2cHandler, BUS_I2C_DIGITAL_FILTER_COEFICIENTE) != HAL_OK)
    {
        return HARDGFX_BUS_DIGITAL_FILTER_INITIALIZATION_FAIL;
    }

    return HARDGFX_NONE_ERROR;
}

/**
 * @brief Get the value of the I2C timing register.
 *
 * @param[in]   i2cSrcFreq  I2C frequency source value.
 * @param[in]   i2cFreq     I2C frequency desired.
 *
 * @retval  Return the timing register value.
 */
static uint32_t GetI2CTiming(const uint32_t i2cSrcFreq, const uint32_t i2cFreq)
{
    uint32_t retVal = 0;
    uint8_t speedMode = 0;
    uint32_t id;

    if (i2cSrcFreq != 0 && i2cFreq != 0)
    {
        for (speedMode = 0; speedMode < BUS_I2C_SPEED_MODE; speedMode++)
        {
            if (i2cFreq >= i2cFeature[speedMode].freqMin && i2cFreq <= i2cFeature[speedMode].freqMax)
            {
                ComputePRESCTimeSCLDELTimeSDADEL(i2cSrcFreq, speedMode);
                id = ComputeSCLLandSCLH(i2cSrcFreq, speedMode);

                if (id < SIZE_BUS_I2C_TIMING_NBR)
                {
                    retVal = ((i2cTiming[id].presc  & 0x0FU) << 28) |\
                    ((i2cTiming[id].scldel & 0x0FU) << 20) |\
                    ((i2cTiming[id].sdadel & 0x0FU) << 16) |\
                    ((i2cTiming[id].highSCL & 0xFFU) << 8) |\
                    ((i2cTiming[id].lowSCL & 0xFFU) << 0);
                }
                break;
            }
        }
    }

    return retVal;
}

/**
 * @brief Calculate the PRESC value, SCLDEL, and SDADEL time of the I2C. These values will be used to build the I2C Timing register.
 *
 * @param[in]   i2cSrcFreq  I2C frequency source value.
 * @param[in]   speedMode   I2C speed mode.
 */
static void ComputePRESCTimeSCLDELTimeSDADEL(const uint32_t i2cSrcFreq, const uint32_t speedMode)
{
    uint32_t prevPresc = MAX_BUS_I2C_PRESC;
    uint32_t presc, sdadel, scldel;
    uint32_t tSCLDEL = 0, tSDADEL = 0;
    const uint32_t tI2CCLK = (SEC2NSEC / i2cSrcFreq);
    const uint32_t tAFMin = MIN_BUS_I2C_ANALOG_FILTER_DELAY, tAFMax = MAX_BUS_I2C_ANALOG_FILTER_DELAY;

    /*
     * tDNF = DNF x tI2CCLK
     * tPRESC = (PRESC + 1) x tI2CCLK
     * SDADEL >= {tFall(Max) + tHDDAT(Min) - tAF(Min) - [(DNF + 3) x tI2CCLK]} / [(PRESC + 1) x tI2CCLK]
     * SDADEL <= {tVDDAT(Max) - tAF(Max) - [(DNF + 4) x tI2CCLK]} / [(PRESC + 1) x tI2CCLK]
     */
    int32_t tSDADELMin = i2cFeature[speedMode].tFallMax + i2cFeature[speedMode].tHdDataMin - tAFMin - (i2cFeature[speedMode].dnf + 3) * tI2CCLK;
    int32_t tSDADELMax = i2cFeature[speedMode].tVdDataMax - tAFMax - (i2cFeature[speedMode].dnf + 4) * tI2CCLK;

    if (tSDADELMin < 0)
    {
        tSDADELMin = 0;
    }

    if (tSDADELMax < 0)
    {
        tSDADELMax = 0;
    }

    /* SCLDEL >= { [tRise(Max) - tSUDAT(min)] / [(PRESC + 1) x tI2CCLK] } - 1 */
    const uint32_t tSCLDELMin = i2cFeature[speedMode].tRiseMax - i2cFeature[speedMode].tSuDataMin;

    for (presc = 0; presc < MAX_BUS_I2C_PRESC; presc++)
    {
        for (scldel = 0; scldel < MAX_BUS_I2C_SCLDEL; scldel++)
        {
            /* tSCLDEL = (SCLDEL + 1) * (PRESC + 1) * tI2CCLK */
            tSCLDEL = (scldel + 1) * (presc + 1) * tI2CCLK;

            if (tSCLDEL >= tSCLDELMin)
            {
                for (sdadel = 0; sdadel < MAX_BUS_I2C_SDADEL; sdadel++)
                {
                    /* tSDADEL = [SDADEL * (PRESC + 1) * tI2CCLK] + tI2CCLK*/
                    tSDADEL = (sdadel * (presc + 1) * tI2CCLK) + tI2CCLK;

                    if (tSDADEL >= tSDADELMin && tSDADEL <= tSDADELMax)
                    {
                        if(presc != prevPresc)
                        {
                            i2cTiming[i2cTimingNBR].presc = presc;
                            i2cTiming[i2cTimingNBR].scldel = scldel;
                            i2cTiming[i2cTimingNBR].sdadel = sdadel;
                            prevPresc = presc;
                            i2cTimingNBR++;

                            if(i2cTimingNBR >= SIZE_BUS_I2C_TIMING_NBR)
                            {
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
/**
  * @brief  Calculate SCLL and SCLH for the best configuration.
  *
  * @param[in]  i2cSrcFreq  I2C frequency source value.
  * @param[in]  speedMode   I2C speed mode.
  *
  * @retval Return the index of the i2cTiming vector with the best configuration,
  *         0xFFFFFFFF for invalid configuration. The index is between 0 and  SIZE_I2C_TIMING_NBR.
  */
static uint32_t ComputeSCLLandSCLH(const uint32_t i2cSrcFreq, const uint32_t speedMode)
{
    uint32_t retVal = 0xFFFFFFFF;
    uint32_t prevError = 0;
    int32_t error = 0;
    uint32_t scll = 0, sclh = 0, tSCL = 0;
    uint32_t tSCLLow = 0, tSCLHigh = 0;
    uint32_t tPRESC = 0;
    const uint32_t tI2CSpeed = (SEC2NSEC / i2cFeature[speedMode].frequency);
    const uint32_t tI2CCLK = (SEC2NSEC / i2cSrcFreq);
    const uint32_t clkMax = (SEC2NSEC / i2cFeature[speedMode].freqMin);
    const uint32_t clkMin = (SEC2NSEC / i2cFeature[speedMode].freqMax);
    const uint32_t tAFMin = MIN_BUS_I2C_ANALOG_FILTER_DELAY;
    const uint32_t dnfDelay = i2cFeature[speedMode].dnf * tI2CCLK;


    prevError = tI2CSpeed;

    for (uint32_t count = 0; count < i2cTimingNBR;count++)
    {
        tPRESC = (i2cTiming[count].presc + 1) * tI2CCLK;

        for (scll = 0; scll < MAX_SIZE_BUS_I2C_SCLL; scll++)
        {
            /* tLow(min) <= tAF(min) + tDNF + (2 x tI2CCLK) + [(SCLL + 1)* tPRESC]*/
            tSCLLow = tAFMin + dnfDelay + (2 * tI2CCLK) + ((scll + 1) * tPRESC);

            /*
             * tI2CCLK has the following constrain
             *
             * tI2CCLK > (tLOW - tFilter) / 4
             * tI2CCLK < tHIGH
             */
            if ((tSCLLow >= i2cFeature[speedMode].tLowSCLMin) && (tI2CCLK < (tSCLLow - tAFMin - dnfDelay)/4))
            {
                for (sclh = 0; sclh < MAX_SIZE_BUS_I2C_SCLH; sclh++)
                {
                    /* tHigh(min) <= tAF(min) + tDNF + (2 x tI2CCLK) + [(SCLH + 1)* tPRESC]*/
                    tSCLHigh = tAFMin + dnfDelay + (2 * tI2CCLK) + ((sclh + 1) * tPRESC);
                    /* tSCL = tf + tLow + tr + tHigh */
                    tSCL = BUS_I2C_TIME_FALL + tSCLLow + BUS_I2C_TIME_RISE + tSCLHigh;

                    if ((tSCL >= clkMin) && (tSCL <= clkMax) && (tSCLHigh >= i2cFeature[speedMode].tHighSCLMin) && tI2CCLK < tSCLHigh)
                    {
                       error = (int32_t)tSCL - (int32_t)tI2CSpeed;

                       if (error < 0)
                       {
                           error = (-1)*error;
                       }

                       //
                       if ((uint32_t)error < prevError)
                       {
                           prevError = (uint32_t)error;
                           i2cTiming[count].lowSCL = scll;
                           i2cTiming[count].highSCL = sclh;
                           retVal = count;

                       }
                    }

                }
            }
        }
    }

    return retVal;
}

/*
 * @brief  Write a value in a register of the device through I2C.
 *
 * @param[in]  deviceAddress        Device address.
 * @param[in]  registerAddress      The target register address to write
 * @param[in]  memoryAddressSize    Size of internal memory address
 * @param[in]  data                 The target register value to be written
 * @param[in]  length               Data length in bytes
 *
 * @retval Return status operation.
 */
static int32_t I2CWriteRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint16_t memoryAddressSize, const uint8_t *data, const uint16_t length)
{
    return (HAL_I2C_Mem_Write(&i2cHandler, deviceAddress, registerAddress, memoryAddressSize, (uint8_t *)data, length, 1000) == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_BUS_TRANSMISSION_FAIL;
}

/*
 * @brief  Read a register of the device through I2C.
 *
 * @param[in]       deviceAddress        Device address.
 * @param[in]       registerAddress      The target register address to read
 * @param[in]       memoryAddressSize    Size of internal memory address
 * @param[in,out]   data                 The target register value to be read
 * @param[in]       length               Data length in bytes
 *
 * @retval Return status operation.
 */
static int32_t I2CReadRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint16_t memoryAddressSize, uint8_t *data, const uint16_t length)
{
  return (HAL_I2C_Mem_Read(&i2cHandler, deviceAddress, registerAddress, memoryAddressSize, data, length, 1000) == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_BUS_RECEPTION_FAIL;
}
