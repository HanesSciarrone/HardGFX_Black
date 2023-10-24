#include <stddef.h>

#include "ft5336.h"


/* ------------------------------------- Private functions declaration ------------------------------------- */
#if (FT5336_AUTO_CALIBRATION == 1)
static int32_t ft5336TouchScreenCalibration(ft5336Object* object);
static int32_t ft5336Delay(ft5336Object* object, uint32_t delay);
#endif // FT5336_AUTO_CALIBRATION == 1
static int32_t ft5336DetectTocuh(ft5336Object* object);
static int32_t ft5336WriteRegisterWrap(void* handler, const uint8_t registerAddress, const uint8_t* buffer, const uint16_t sizeBuffer);
static int32_t ft5336ReadRegisterWrap(void* handler, const uint8_t registerAddress, uint8_t* buffer, const uint16_t sizeBuffer);

/* ------------------------------------ Global function implementations ------------------------------------ */

/*
 * @brief  Register input and output bus to component on the ft5336 object.
 *
 * @param[in,out]   object      ft5336 object pointer.
 * @param[in]       inputOutput Input and output functions used in the bus.
 *
 * @retval Return the status operation.
 */
int32_t ft5336RegisterBus(ft5336Object* object, ft5336InputOutput* inputOutput)
{
    int32_t retVal = FT5336_ERROR;

    if (object != NULL)
    {
        object->InputOutput.Init            = inputOutput->Init;
        object->InputOutput.DeInit          = inputOutput->DeInit;
        object->InputOutput.GetTick         = inputOutput->GetTick;
        object->InputOutput.WriteRegister   = inputOutput->WriteRegister;
        object->InputOutput.ReadRegister    = inputOutput->ReadRegister;
        object->InputOutput.Address         = inputOutput->Address;

        object->Context.handler = object;
        object->Context.write = ft5336WriteRegisterWrap;
        object->Context.read = ft5336ReadRegisterWrap;

        retVal = FT5336_OK;
    }

    return retVal;
}

/*
 * @brief  Initialize the ft5336 communication input and output bus.
 *
 * @param[in]   object  ft5336 object pointer.
 *
 * @retval Return the status operation.
 */
int32_t ft5336Initialization(ft5336Object* object)
{
    if (!object->IsInitialized)
    {
        // Initialize Bus layer
        if (object->InputOutput.Init() != FT5336_OK)
        {
            return FT5336_ERROR;
        }

#if (FT5336_AUTO_CALIBRATION == 1)
        if (ft5336TouchScreenCalibration(object) != FT5336_OK)
        {
            return FT5336_ERROR;
        }
#endif

        // By default the ft5336 is in Polling mode, no interrupt will be generated for new touch available.
        if (ft5336DisableIT(object) != FT5336_OK)
        {
            return FT5336_ERROR;
        }

        object->IsInitialized = true;
    }

    return FT5336_OK;
}

/*
 * @brief  Des-initialize the ft5336 communication input and output bus.
 *
 * @param[in]   object  ft5336 object pointer.
 *
 * @retval Return the status operation.
 */
int32_t ft5336DesInitialize(ft5336Object* object)
{
    if (!object->IsInitialized)
    {
        if (object->InputOutput.DeInit() != FT5336_OK)
        {
            return FT5336_ERROR;
        }

        if (ft5336DisableIT(object) != FT5336_OK)
        {
            return FT5336_ERROR;
        }

        object->IsInitialized = false;
    }

    return FT5336_OK;
}

/*
 * @brief  Configure the ft5336 gesture parameters.
 *
 * @param[in]   object      ft5336 object pointer.
 * @param[in]   parameters  Gestures parameters to configure.
 *
 * @retval Return the status operation.
 */
int32_t ft5336GestureConfiguration(ft5336Object* object, const ft5336GestureParameters* parameters)
{
    if (ft5336RadianValue(&(object->Context), parameters->Radian) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    if (ft5336OffsetLeftRight(&(object->Context), parameters->OffsetLeftRight) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    if (ft5336OffsetUpDown(&(object->Context), parameters->OffsetUpDown) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    if (ft5336DistanceLeftRight(&(object->Context), parameters->DistanceLeftRight) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    if (ft5336DistanceUpDown(&(object->Context), parameters->DistanceUpDown) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    if (ft5336DistanceZoom(&(object->Context), parameters->DistanceZoom) != FT5336_OK)
    {
        return FT5336_ERROR;
    }

    return FT5336_OK;
}

/*
 * @brief  Get the device ID of ft5336.
 *
 * @param[in]       object  ft5336 object pointer.
 * @param[in,out]   id      Device ID.
 *
 * @retval Return the status operation.
 */
int32_t ft5336ReadId(ft5336Object* object, uint8_t* id)
{
    return ft5336ChipId(&(object->Context), id);
}

/*
 * @brief  Get the touch screen X and Y positions values.
 *
 * @param[in]       object  ft5336 object pointer.
 * @param[in,out]   state   Single touch data.
 *
 * @retval Return the status operation.
 */
int32_t ft5336GetTouchState(ft5336Object* object, ft5336TouchState *state)
{
    int32_t retVal = FT5336_OK;
    uint8_t data[4] = { 0 };

    state->touchDetected = (uint32_t)ft5336DetectTocuh(object);

    if(object->Context.read(object->Context.handler, FT5336_TOUCH1_XH_REG, data, (uint16_t)sizeof(data)) != FT5336_OK)
    {
        retVal = FT5336_ERROR;
    }
    else
    {
        // Send back first ready X and Y position to caller
        state->touchX = (((uint32_t)data[0] & FT5336_TOUCH1_XH_TOUCHPOINT_BIT_MASK) << 8) | ((uint32_t)data[1] & FT5336_TOUCH1_XL_TOUCHPOINT_BIT_MASK);
        state->touchY = (((uint32_t)data[2] & FT5336_TOUCH1_YH_TOUCHPOINT_BIT_MASK) << 8) | ((uint32_t)data[3] & FT5336_TOUCH1_YL_TOUCHPOINT_BIT_MASK);
    }

    return retVal;
}

/*
 * @brief  Get the touch screen X and Y positions values in multiple touch mode.
 *
 * @param[in]       object  ft5336 object pointer.
 * @param[in,out]   state   Multiple touch data.
 *
 * @retval Return the status operation.
 */
int32_t ft5336GetMultipleTouchState(ft5336Object* object, ft5336MultipleTouchState *state)
{
    int32_t retVal = FT5336_OK;
    uint8_t data[30] = { 0 };
    uint8_t index = 0;
    int32_t touchNumber;

    touchNumber = ft5336DetectTocuh(object);
    state->touchDetected = (touchNumber >= 0) ? touchNumber : 0;

    if(object->Context.read(object->Context.handler, FT5336_TOUCH1_XH_REG, data, (uint16_t)sizeof(data)) != FT5336_OK)
    {
        retVal = FT5336_ERROR;
    }
    else
    {
        for (index = 0; index < FT5336_MAXIMUM_SIMULTANEOUS_TOUCH; index++)
        {
            // Send back event touch,X and Y position, weight touch and area touch to caller
            state->touchEvent[index] = (uint32_t)data[(index*6U)] & FT5336_TOUCH1_EVENT_FLAG_BIT_MASK >> FT5336_TOUCH1_EVENT_FLAG_BIT_POSITION;
            state->touchX[index] = (((uint32_t)data[(index*6)] & FT5336_TOUCH1_XH_TOUCHPOINT_BIT_MASK) << 8) | ((uint32_t)data[(index*6) + 1] & FT5336_TOUCH1_XL_TOUCHPOINT_BIT_MASK);
            state->touchY[index] = (((uint32_t)data[(index*6U) + 2] & FT5336_TOUCH1_YH_TOUCHPOINT_BIT_MASK) << 8) | ((uint32_t)data[(index*6U) + 3] & FT5336_TOUCH1_YL_TOUCHPOINT_BIT_MASK);
            state->touchWeight[index] = (uint32_t)data[(index*6U) + 4] & FT5336_TOUCH1_WEIGHT_BIT_MASK;
            state->touchArea[index] = ((uint32_t)data[(index*6U) + 5] & FT5336_TOUCH1_MISC_BIT_MASK) >> FT5336_TOUCH1_MISC_BIT_POSITION;
        }
    }

    return retVal;
}

/*
 * @brief  Get Gesture ID of ft5336
 *
 * @param[in]       object      ft5336 object pointer.
 * @param[in,out]   gestureId   Gesture id.
 *
 * @retval Return the status operation.
 */
int32_t ft5336GetGesture(ft5336Object* object, uint8_t* gestureId)
{
    return ft5336GestureId(&object->Context, gestureId);
}

/*
 * @brief Configure the ft5336 device to generate IT on the INT pin.
 *
 * @param[in]   object  ft5336 object pointer.
 *
 * @retval Return the status operation.
 */
int32_t ft5336EnableIT(ft5336Object* object)
{
    return ft5336InterruptMode(&object->Context, FT5336_TRIGGER_INTERRUPT_MODE);
}

/*
 * @brief Configure the ft5336 device to stop generating IT on the INT pin.
 *
 * @param[in]   object  ft5336 object pointer.
 *
 * @retval Return the status operation.
 */
int32_t ft5336DisableIT(ft5336Object* object)
{
    return ft5336InterruptMode(&object->Context, FT5336_POLLING_INTERRUPT_MODE);
}

/*
 * @brief Get sensor capabilities.
 *
 * @param[in,out]  capabilities Capabilities module.
 */
void ft5336GetCapabilities(ft5336Capabilities* capabilities)
{
    capabilities->multiTouch = (FT5336_MAXIMUM_SIMULTANEOUS_TOUCH > 1) ? 1 : 0;
    capabilities->gesture = 1;
    capabilities->simultaneousTouch = FT5336_MAXIMUM_SIMULTANEOUS_TOUCH;
    capabilities->maxLenghtX = FT5336_MAXIMUM_X_LENGTH;
    capabilities->maxLenghtY = FT5336_MAXIMUM_Y_LENGTH;
}
/* ------------------------------------ Private function implementations ----------------------------------- */

#if (FT5336_AUTO_CALIBRATION == 1)

/*
 * @brief  Start TouchScreen calibration phase.
 *
 * @param[in]   object  ft5336 object pointer.
 *
 * @retval return FT5336_OK if was success or FT5336_ERROR in otherwise.
 */
static int32_t ft5336TouchScreenCalibration(ft5336Object* object)
{
    int32_t retVal = FT5336_ERROR;
    uint8_t dataRead = 0;
    uint8_t retries = 0;

    // Go back to factory mode to calibrate
    if (ft5336DeviceModeWrite(&object->Context, FT5336_DEVICE_MODE_FACTORY) == FT5336_OK)
    {
        // Check if the factory mode was configured.
        if (ft5336DeviceModeRead(&object->Context, &dataRead) == FT5336_OK)
        {
            // Wait for 300 ms
            ft5336Delay(object, 300);

            if (dataRead == FT5336_DEVICE_MODE_FACTORY)
            {
                // Starting calibration command
                dataRead = 0x04;
                if (object->InputOutput.WriteRegister(object->InputOutput.Address, FT5336_TOUCHDATA_STAT_REG, &dataRead, 1) == FT5336_OK)
                {
                    // Wait for 300 ms
                    ft5336Delay(object, 300);

                    // Try 100 attempts to check if pass from Factory (Calibration) mode to Working mode
                    for (retries = 0; retries < 100; retries++)
                    {
                        if (ft5336DeviceModeRead(&object->Context, &dataRead) == FT5336_OK)
                        {
                            if (dataRead == FT5336_DEVICE_MODE_WORKING)
                            {
                                // Auto switch to Working mode happen when the calibration finish.
                                retVal = FT5336_OK;
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                        // Wait for 300 ms
                        ft5336Delay(object, 300);
                    }
                }
            }
        }
    }

    return retVal;
}

static int32_t ft5336Delay(ft5336Object* object, uint32_t delay)
{
    uint32_t tickStart = 0;

    tickStart = object->InputOutput.GetTick();
    while (object->InputOutput.GetTick() - tickStart < delay);
    return FT5336_OK;
}

#endif // FT5336_AUTO_CALIBRATION == 1

/*
 * @brief  Get whether there is touches detected or not.
 *         Try to detect new touches and forget the old ones (reset internal global
 *         variables).
 *
 * @param[in]   object Object ft5336 pointer.
 *
 * @retval Return the number of active touches detected (can be 0, 1 or 2) or FT5336_ERROR
 *         in case of error
 */
static int32_t ft5336DetectTocuh(ft5336Object* object)
{
    int32_t retVal = FT5336_ERROR;
    uint8_t  touchNumber = 0;


    if (ft5336TouchDataStatus(&object->Context, &touchNumber) == FT5336_OK)
    {
        if (touchNumber > FT5336_MAXIMUM_SIMULTANEOUS_TOUCH)
        {
            retVal = 0;
        }
        else
        {
            retVal = (int32_t)touchNumber;
        }
    }

    return retVal;
}

/*
 * @brief  Function to write registers used in ft5336Reg.h.
 *
 * @param[in]  handler          ft5336 object pointer.
 * @param[in]  registerAddress  The target register address to write,
 * @param[in]  buffer           Buffer with the value to be written.
 * @param[in]  sizeBuffer       Buffer size to be written
 *
 * @retval Return 0 if was success.
 */
static int32_t ft5336WriteRegisterWrap(void* handler, const uint8_t registerAddress, const uint8_t* buffer, const uint16_t sizeBuffer)
{
    ft5336Object* object = (ft5336Object*)handler;

    return object->InputOutput.WriteRegister(object->InputOutput.Address, registerAddress, buffer, sizeBuffer);
}

/*
 * @brief  Function to read registers used in ft5336Reg.h.
 *
 * @param[in]       handler          ft5336 object pointer.
 * @param[in]       registerAddress  The target register address to read,
 * @param[in, out]  buffer           Buffer with the value read.
 * @param[in]       sizeBuffer       Buffer size to be written
 *
 * @retval Return 0 if was success.
 */
static int32_t ft5336ReadRegisterWrap(void* handler, const uint8_t registerAddress, uint8_t* buffer, const uint16_t sizeBuffer)
{
    ft5336Object* object = (ft5336Object*)handler;

    return object->InputOutput.ReadRegister(object->InputOutput.Address, registerAddress, buffer, sizeBuffer);
}
