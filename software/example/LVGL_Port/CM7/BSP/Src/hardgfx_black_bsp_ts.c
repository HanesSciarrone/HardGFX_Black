#include "hardgfx_black_bsp_ts.h"
#include "hardgfx_black_bus.h"


/* -------------------------------------------- Private defines -------------------------------------------- */
#define TOUCHSCREEN_MIN(a,b) ((a > b) ? b : a)


/* -------------------------------------- Structure types declaration -------------------------------------  */


/* ------------------------------------- Private variables declaration ------------------------------------- */
static ft5336Object handler;
static touchScreenCapabilities capacities;
static EXTI_HandleTypeDef handlerTouchScrennEXTI = {0};


/* ------------------------------------- Private functions declaration ------------------------------------- */
static int32_t TestTouchScreenModule(void);

/* ------------------------------------ Global function implementations ------------------------------------ */

/*
 * @brief  Initialize and configure the touch screen functionalities.
 *
 * @param[in]   parameters  Touch screen parameters used on the initialization..
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenInit(const touchScreenInit* parameters)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    if ((parameters->width == 0U) || (parameters->width > HARDGFX_TS_MAX_WIDTH) ||\
        (parameters->height == 0U) || (parameters->height > HARDGFX_TS_MAX_HEIGHT)\
        || (parameters->accuracy > TOUCHSCREEN_MIN(parameters->width, parameters->height)))
    {
        retVal = HARDGFX_TOUCHSCREEN_WRONG_PARAMETERS;
    }
    else
    {
        ft5336Capabilities moduleCapabilities;

        retVal = TestTouchScreenModule();
        ft5336GetCapabilities(&moduleCapabilities);

        /* Store the touch screen capabilities */
        capacities.width       = parameters->width;
        capacities.height      = parameters->height;
        capacities.accuracy    = parameters->accuracy;
        capacities.orientation = parameters->orientation;
        capacities.maxX        = moduleCapabilities.maxLenghtX;
        capacities.maxY        = moduleCapabilities.maxLenghtY;

        for (uint8_t index = 0; index < HARDGFX_TOUCHSCREEN_NUMBER; index++)
        {
            capacities.previousX[index] = parameters->width  + parameters->accuracy + 1U;
            capacities.previousY[index] = parameters->height + parameters->accuracy + 1U;
        }
    }

    return retVal;
}

/*
 * @brief  DesInitializes the touch screen functionalities.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenDeInit(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    if (ft5336DesInitialize(&handler) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_DESINITIALIZATION_FAIL;
    }

    return retVal;
}

/*
 * @brief  Configures and enables the touch screen interrupts pin.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenEnableIT(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    GPIO_InitTypeDef gpioInit = {0};

    HARDGFX_TS_INT_GPIO_CLK_ENABLE();

    /**
     * Configure interrupt mode for TS_INT pin. Falling edge:
     * when a new touch is available TS_INT pin is active on low level
     */
    gpioInit.Pin        = HARDGFX_TS_INT_PIN;
    gpioInit.Mode       = GPIO_MODE_IT_FALLING;
    gpioInit.Pull       = GPIO_PULLUP;
    gpioInit.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(HARDGFX_TS_INT_GPIO_PORT, &gpioInit);

    if (ft5336EnableIT(&handler) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_INTERRUP_ENABLE_FAIL;
    }
    else
    {
        if (HAL_EXTI_GetHandle(&handlerTouchScrennEXTI, HARDGFX_TS_EXTI_LINE) != HAL_OK)
        {
            retVal = HARDGFX_PERIPHERAL_ERROR;
        }
        else if (HAL_EXTI_RegisterCallback(&handlerTouchScrennEXTI, HAL_EXTI_COMMON_CB_ID, HardGFXTouchScreenCallback) != HAL_OK)
        {
            retVal = HARDGFX_PERIPHERAL_ERROR;
        }
        else
        {
            HAL_NVIC_SetPriority(HARDGFX_TS_INT_EXTI_IRQn, HARDGFX_TOUCHSCREEN_IT_PRIORITY, 0);
            HAL_NVIC_EnableIRQ(HARDGFX_TS_INT_EXTI_IRQn);
        }

    }

    return retVal;
}

/*
 * @brief  Disables the touch screen interrupts pin.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenDisableIT(void)
{
    HAL_NVIC_DisableIRQ(HARDGFX_TS_INT_EXTI_IRQn);
    HAL_GPIO_DeInit(HARDGFX_TS_INT_GPIO_PORT, HARDGFX_TS_INT_PIN);

    /*
     * Disable the TS in interrupt mode, when  the INT output of FT5336 detects a
     * new touch available it will be active on low level and directed on EXTI
     */
    return (ft5336DisableIT(&handler) != FT5336_OK) ? HARDGFX_TOUCHSCREEN_INTERRUP_DISABLE_FAIL : HARDGFX_NONE_ERROR;
}

/*
 * @brief  Get the positions of a single touch screen.
 *
 * @param[in,out]   state   Data structure with current state touch screen.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenGetState(touchScreenState* state)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    uint32_t xOriented = 0, yOriented = 0;
    uint32_t xDifference = 0, yDifference = 0;

    ft5336TouchState ft5336State = {0};

    if (ft5336GetTouchState(&handler, &ft5336State) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_GET_STATE_FAIL;
    }
    else if (ft5336State.touchDetected != 0)
    {
        xOriented = ft5336State.touchX;
        yOriented = ft5336State.touchY;

        if (capacities.orientation == TS_SWAP_XY)
        {
            xOriented = ft5336State.touchY;
            yOriented = ft5336State.touchX;
        }

        if (capacities.orientation == TS_SWAP_X)
        {
            xOriented = capacities.maxX - ft5336State.touchX - 1U;
        }

        if (capacities.orientation == TS_SWAP_Y)
        {
            yOriented = capacities.maxY - ft5336State.touchY - 1U;
        }

        state->touchDetected = ft5336State.touchDetected;
        // Apply boundary
        state->touchX = (xOriented * capacities.width) / capacities.maxX;
        state->touchY = (yOriented * capacities.height) / capacities.maxY;

        // Check the accuracy
        xDifference = (state->touchX > capacities.previousX[0]) ? state->touchX - capacities.previousX[0] : capacities.previousX[0] - state->touchX;
        yDifference = (state->touchY > capacities.previousY[0]) ? state->touchY - capacities.previousY[0] : capacities.previousY[0] - state->touchY;

        if (xDifference > capacities.accuracy || yDifference > capacities.accuracy)
        {
            // New touch detected
            capacities.previousX[0] = state->touchX;
            capacities.previousY[0] = state->touchY;
        }
        else
        {
            state->touchX = capacities.previousX[0];
            state->touchY = capacities.previousY[0];
        }
    }
    else
    {
        state->touchDetected = 0;
        state->touchX = capacities.previousX[0];
        state->touchY = capacities.previousY[0];
    }

    return retVal;
}

#if (HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH == 1)

/*
 * @brief  Get the positions of a multiple touch screen.
 *
 * @param[in,out]   state   Data structure with current state touch screen.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenGetMultiTouchState(touchScreenMultiTouchState* state)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    uint32_t index;
    uint32_t xOriented = 0, yOriented = 0;
    uint32_t xDifference = 0, yDifference = 0;

    ft5336MultipleTouchState moduleState = {0};

    if (ft5336GetMultipleTouchState(&handler, &moduleState) != HAL_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_GET_STATE_FAIL;
    }
    else if (moduleState.touchDetected != 0)
    {
        state->touchDetected = (moduleState.touchDetected < HARDGFX_TOUCHSCREEN_NUMBER) ? moduleState.touchDetected : HARDGFX_TOUCHSCREEN_NUMBER;

        for (index = 0; index < moduleState.touchDetected; index++)
        {
            if (index >= HARDGFX_TOUCHSCREEN_NUMBER)
            {
                continue;
            }

            xOriented = moduleState.touchX[index];
            yOriented = moduleState.touchY[index];

            if (capacities.orientation == TS_SWAP_XY)
            {
                xOriented = moduleState.touchY[index];
                yOriented = moduleState.touchX[index];
            }

            if (capacities.orientation == TS_SWAP_X)
            {
                xOriented = capacities.maxX - moduleState.touchX[index] - 1U;
            }

            if (capacities.orientation == TS_SWAP_Y)
            {
                yOriented = capacities.maxY - moduleState.touchY[index] - 1U;
            }

            // Apply boundary
            state->touchX[index] = (xOriented * capacities.width) / capacities.maxX;
            state->touchY[index] = (yOriented * capacities.height) / capacities.maxY;

            xDifference = (state->touchX[index] > capacities.previousX[index]) ? state->touchX[index] - capacities.previousX[index] : capacities.previousX[index] - state->touchX[index];
            yDifference = (state->touchY[index] > capacities.previousY[index]) ? state->touchY[index] - capacities.previousY[index] : capacities.previousY[index] - state->touchY[index];

            if (xDifference > capacities.accuracy || yDifference > capacities.accuracy)
            {
                // New tocuh detected
                capacities.previousX[index] = state->touchX[index];
                capacities.previousY[index] = state->touchY[index];
            }
            else
            {
                state->touchX[index] = capacities.previousX[index];
                state->touchY[index] = capacities.previousY[index];
            }
        }
    }
    else
    {
        state->touchDetected = 0;

        for (index = 0; index < HARDGFX_TOUCHSCREEN_NUMBER; index++)
        {
            state->touchX[index] = capacities.previousX[index];
            state->touchY[index] = capacities.previousY[index];
        }
    }

    return retVal;
}

#endif

#if (HARDGFX_USE_TOUCHSCREEN_GESTURE == 1)

/*
 * @brief Configure the gesture parameters of the touch screen module.
 *
 * @param[in,out]   parameters  Parameters to be configured.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenGestureConfig(const touchScreenGestureParameters* parameters)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    ft5336GestureParameters gestureParameters = {0};

    gestureParameters.Radian = parameters->Radian;
    gestureParameters.OffsetLeftRight = parameters->OffsetLeftRight;
    gestureParameters.OffsetUpDown = parameters->OffsetUpDown;
    gestureParameters.DistanceLeftRight = parameters->DistanceLeftRight;
    gestureParameters.DistanceUpDown = parameters->DistanceUpDown;
    gestureParameters.DistanceZoom = parameters->DistanceZoom;

    if (ft5336GestureConfiguration(&handler, &gestureParameters) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_GESTURE_CONFIGURATION_FAIL;
    }

    return retVal;
}

/*
 * @brief  Get the gesture id with a new touch detected.
 *
 * @param[in,put]   gestureId   Gesture ID detected.
 *
 * @retval Return the status of the operation.
 */
int32_t HardGFXTouchScreenGetGestureId(uint8_t* gestureId)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    if (ft5336GetGesture(&handler, gestureId) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_GET_GESTUREID_FAIL;
    }

    switch(*gestureId)
    {
    case FT5336_NO_GESTURE_ID:
    {
        *gestureId = GESTURE_ID_NO_GESTURE;
    }
    break;

    case FT5336_GESTURE_ID_MOVE_UP:
    {
        *gestureId = GESTURE_ID_MOVE_UP;
    }
    break;

    case FT5336_GESTURE_ID_MOVE_RIGHT:
    {
        *gestureId = GESTURE_ID_MOVE_RIGHT;
    }
    break;

    case FT5336_GESTURE_ID_MOVE_DOWN:
    {
        *gestureId = GESTURE_ID_MOVE_DOWN;
    }
    break;

    case FT5336_GESTURE_ID_MOVE_LEFT:
    {
        *gestureId = GESTURE_ID_MOVE_LEFT;
    }
    break;

    case FT5336_GESTURE_ID_ZOOM_IN:
    {
        *gestureId = GESTURE_ID_ZOOM_IN;
    }
    break;

    case FT5336_GESTURE_ID_ZOOM_OUT:
    {
        *gestureId = GESTURE_ID_ZOOM_OUT;
    }
    break;

    default:
        *gestureId = GESTURE_ID_NO_GESTURE;
    }

    return retVal;
}
#endif

/*
 * @brief   Wrapper function used to handle the touch screen interrupt request.
 */
void HardGFXTouchScreenIRQHandler(void)
{
  HAL_EXTI_IRQHandler(&handlerTouchScrennEXTI);
}


/*
 * @brief   Touch screen EXTI touch detection callback.
 */
__weak void HardGFXTouchScreenCallback(void)
{

}

/*
 * @brief  Set the touch screen orientation.
 *
 * @retval Returns the current configured orientation.
 */
void HardGFXTouchScreenSetOrientation(const touchScreenOrientation orientation)
{
    capacities.orientation = orientation;
}

/*
 * @brief  Get the touch screen orientation.
 *
 * @param[in,out]   orientation Orientation to be configure.
 */
touchScreenOrientation HardGFXTouchScreenGetOrientation(void)
{
    return capacities.orientation;
}

/* ------------------------------------ Private function implementations ----------------------------------- */

/*
 * @brief  Register input and output bus and checks if the module ID is OK.
 *
 * @retval Return the status of the operation.
 */
static int32_t TestTouchScreenModule(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    ft5336InputOutput inputOutput;
    uint8_t ft5336Id = 0;

    inputOutput.Address = HARDGFX_TS_ADDRESS;
    inputOutput.Init = HardGFXBusInit;
    inputOutput.DeInit = HardGFXBusDeInit;
    inputOutput.ReadRegister = HardGFXBusReadRegister;
    inputOutput.WriteRegister = HardGFXBusWriteRegister;
    inputOutput.GetTick = HardGFXBusGetTick;

    if (ft5336RegisterBus(&handler, &inputOutput) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_REGISTER_BUS_FAIL;
    }
    else if (ft5336Initialization(&handler) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_MODULE_FAIL;
    }
    else if (ft5336ReadId(&handler, &ft5336Id) != FT5336_OK)
    {
        retVal = HARDGFX_TOUCHSCREEN_MODULE_FAIL;
    }
    else if (ft5336Id != FT5336_ID)
    {
        retVal = HARDGFX_TOUCHSCREEN_RECOGNIZE_MODULE_FAIL;
    }

    return retVal;
}
