#include <ft5336Reg.h>

/*
 * @brief  Configure the ft5336 working mode.
 *
 * @param[in]  context  ft5336 context driver.
 * @param[in]  value    Value to write to FT5336_DEV_MODE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336DeviceModeWrite(ft5336Context *context, const uint8_t value)
{
    int32_t retVal = 0;
    uint8_t buffer = 0;

    retVal = context->read(context->handler, FT5336_DEV_MODE_REG, &buffer, 1);

    if (retVal == 0)
    {
        buffer |= value << FT5336_DEV_MODE_BIT_POSITION;
        retVal = context->write(context->handler, FT5336_DEV_MODE_REG, &buffer, 1);
    }

    return retVal;
}

/*
 * @brief  Get ft5336 working mode.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_DEV_MODE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336DeviceModeRead(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_DEV_MODE_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_DEV_MODE_BIT_MASK;
        *value = *value >> FT5336_DEV_MODE_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 gesture ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_GEST_ID_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336GestureId(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_GEST_ID_REG, value, 1);
}

/*
 * @brief  Get ft5336 touch data status.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of touch data Status register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336TouchDataStatus(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;

    retVal = context->read(context->handler, FT5336_TOUCHDATA_STAT_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCHDATA_STATUS_BIT_MASK;
        *value = *value >> FT5336_TOUCHDATA_STATUS_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 First X Event Flag.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1EventFlag(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH1_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH1_EVENT_FLAG_BIT_MASK;
        *value = *value >> FT5336_TOUCH1_EVENT_FLAG_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the X coordinate of the first touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1XHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH1_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH1_XH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH1_XH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the X coordinate of the first touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_XL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1XLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH1_XL_REG, value, 1);
}

/*
 * @brief  Get ft5336 first touch ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1YHTouchId(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH1_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH1_YH_TOUCHID_BIT_MASK;
        *value = *value >> FT5336_TOUCH1_YH_TOUCHID_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the Y coordinate of the first touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1YHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH1_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH1_YH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH1_YH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the Y coordinate of the first touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_YL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1YLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH1_YL_REG, value, 1);
}

/*
 * @brief  Get ft5336 first touch pressure.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_WEIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1Weight(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH1_WEIGHT_REG, value, 1);
}

/*
 * @brief  Get ft5336 first touch area.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH1_MISC_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch1Misc(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH1_MISC_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH1_MISC_BIT_MASK;
        *value = *value >> FT5336_TOUCH1_MISC_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 second event flag.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2EventFlag(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH2_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH2_XH_EVENTFLAG_BIT_MASK;
        *value = *value >> FT5336_TOUCH2_XH_EVENTFLAG_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the X coordinate of the second touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2XHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH2_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH2_XH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH2_XH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the X coordinate of the second touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_XL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2XLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH2_XL_REG, value, 1);
}

/*
 * @brief  Get ft5336 second touch ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2YHTouchId(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH2_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH2_YH_TOUCHID_BIT_MASK;
        *value = *value >> FT5336_TOUCH2_YH_TOUCHID_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the Y coordinate of the second touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2YHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH2_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH2_YH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH2_YH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the Y coordinate of the second touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_YL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2YLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH2_YL_REG, value, 1);
}

/*
 * @brief  Get ft5336 second touch pressure.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_WEIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2Weight(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH2_WEIGHT_REG, value, 1);
}

/*
 * @brief  Get ft5336 second touch area.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH2_MISC_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch2Misc(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH2_MISC_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH2_MISC_BIT_MASK;
        *value = *value >> FT5336_TOUCH2_MISC_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 third event flag.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3EventFlag(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH3_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH3_XH_EVENTFLAG_BIT_MASK;
        *value = *value >> FT5336_TOUCH3_XH_EVENTFLAG_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the X coordinate of the third touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3XHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH3_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH3_XH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH3_XH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the X coordinate of the third touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_XL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3XLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH3_XL_REG, value, 1);
}

/*
 * @brief  Get ft5336 third touch ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3YHTouchId(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH3_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH3_YH_TOUCHID_BIT_MASK;
        *value = *value >> FT5336_TOUCH3_YH_TOUCHID_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the Y coordinate of the third touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3YHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH3_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH3_YH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH3_YH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the Y coordinate of the third touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_YL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3YLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH3_YL_REG, value, 1);
}

/*
 * @brief  Get ft5336 third touch pressure.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_WEIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3Weight(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH3_WEIGHT_REG, value, 1);
}

/*
 * @brief  Get ft5336 third touch area.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH3_MISC_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch3Misc(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH3_MISC_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH3_MISC_BIT_MASK;
        *value = *value >> FT5336_TOUCH3_MISC_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 fourth event flag.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4EventFlag(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH4_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH4_XH_EVENTFLAG_BIT_MASK;
        *value = *value >> FT5336_TOUCH4_XH_EVENTFLAG_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the X coordinate of the fourth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4XHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH4_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH4_XH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH4_XH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the X coordinate of the fourth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_XL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4XLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH4_XL_REG, value, 1);
}

/*
 * @brief  Get ft5336 fourth touch ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4YHTouchId(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH4_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH4_YH_TOUCHID_BIT_MASK;
        *value = *value >> FT5336_TOUCH4_YH_TOUCHID_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the Y coordinate of the fourth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4YHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH4_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH4_YH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH4_YH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the Y coordinate of the fourth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_YL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4YLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH4_YL_REG, value, 1);
}

/*
 * @brief  Get ft5336 fourth touch pressure.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_WEIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4Weight(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH4_WEIGHT_REG, value, 1);
}

/*
 * @brief  Get ft5336 fourth touch area.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH4_MISC_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch4Misc(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH4_MISC_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH4_MISC_BIT_MASK;
        *value = *value >> FT5336_TOUCH4_MISC_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 fifth event flag.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5EventFlag(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH5_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH5_XH_EVENTFLAG_BIT_MASK;
        *value = *value >> FT5336_TOUCH5_XH_EVENTFLAG_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the X coordinate of the fifth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_XH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5XHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH5_XH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH5_XH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH5_XH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the X coordinate of the fifth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_XL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5XLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH5_XL_REG, value, 1);
}

/*
 * @brief  Get ft5336 fifth touch ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5YHTouchId(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH5_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH5_YH_TOUCHID_BIT_MASK;
        *value = *value >> FT5336_TOUCH5_YH_TOUCHID_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 MSB of the Y coordinate of the fifth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_YH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5YHTouchPoint(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH5_YH_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH5_YH_TOUCHPOINT_BIT_MASK;
        *value = *value >> FT5336_TOUCH5_YH_TOUCHPOINT_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Get ft5336 LSB of the Y coordinate of the fifth touch point.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_YL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5YLTouchPoint(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH5_YL_REG, value, 1);
}

/*
 * @brief  Get ft5336 fifth touch pressure.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_WEIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5Weight(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_TOUCH5_WEIGHT_REG, value, 1);
}

/*
 * @brief  Get ft5336 fifth touch area.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read of FT5336_TOUCH5_MISC_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Touch5Misc(ft5336Context *context, uint8_t *value)
{
    int32_t retVal = 0;


    retVal = context->read(context->handler, FT5336_TOUCH5_MISC_REG, value, 1);

    if (retVal == 0)
    {
        *value &= FT5336_TOUCH5_MISC_BIT_MASK;
        *value = *value >> FT5336_TOUCH5_MISC_BIT_POSITION;
    }

    return retVal;
}

/*
 * @brief  Set ft5336 threshold for touch detection.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in]  value   Value to write to FT5336_THRESHOLD_GROUP_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336ThresHoldGroup(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_THRESHOLD_GROUP_REG, &value, 1);
}

/*
 * @brief  Set ft5336 filter function coefficient.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_THRESHOLD_DIFFERENT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336ThresHoldDifferent(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_THRESHOLD_DIFFERENT_REG, &value, 1);
}

/*
 * @brief  Control the mode operation between active and monitoring mode.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_CONTROL_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Control(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_CONTROL_REG, &value, 1);
}

/*
 * @brief  Set the time period of change from active mode to monitor.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_TIME_ENTER_MONITOR_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336TimeEnterMonitorStatus(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_TIME_ENTER_MONITOR_REG, &value, 1);
}

/*
 * @brief  Set the time period of active mode.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_PERIOD_ACTIVE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336PeriodActive(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_PERIOD_ACTIVE_REG, &value, 1);
}

/*
 * @brief  Set the time period of monitor mode.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_PERIOD_MONITOR_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336PeriodMonitor(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_PERIOD_MONITOR_REG, &value, 1);
}

/*
 * @brief  Set the value of the minimum allowed angle while rotating.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_RADIAN_VALUE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336RadianValue(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_RADIAN_VALUE_REG, &value, 1);
}

/*
 * @brief  Set maximum offset while moving left and moving right gesture.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_OFFSET_LEFT_RIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336OffsetLeftRight(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_OFFSET_LEFT_RIGHT_REG, &value, 1);
}

/*
 * @brief  Set maximum offset while moving up and moving down gesture.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_OFFSET_UP_DOWN_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336OffsetUpDown(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_OFFSET_UP_DOWN_REG, &value, 1);
}

/*
 * @brief  Set minimum distance while moving left and moving right gesture.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_DISTANCE_LEFT_RIGHT_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336DistanceLeftRight(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_DISTANCE_LEFT_RIGHT_REG, &value, 1);
}

/*
 * @brief  Set minimum distance while moving up and moving down gesture.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_DISTANCE_UP_DOWN_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336DistanceUpDown(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_DISTANCE_UP_DOWN_REG, &value, 1);
}

/*
 * @brief  Set maximum distance while zoom in and zoom out gesture.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_DISTANCE_ZOOM_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336DistanceZoom(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_DISTANCE_ZOOM_REG, &value, 1);
}

/*
 * @brief  Get high 8-bit of LIB version info.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_LIB_VER_HIGH_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336LibVerHigh(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_LIB_VER_HIGH_REG, value, 1);
}

/*
 * @brief  Get low 8-bit of LIB version info.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_LIB_VER_LOW_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336LibVerLow(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_LIB_VER_LOW_REG, value, 1);
}

/*
 * @brief  Get chip selected.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_CIPHER_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336Cipher(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_CIPHER_REG, value, 1);
}

/*
 * @brief  Select interrupt mode (polling or trigger).
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_DISTANCE_ZOOM_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336InterruptMode(ft5336Context *context, const uint8_t value)
{
  return context->write(context->handler, FT5336_GMODE_REG, &value, 1);
}

/*
 * @brief  Select current power mode.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_POWER_MODE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336PowerMode(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_POWER_MODE_REG, &value, 1);
}

/*
 * @brief  Get Firmware version.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_FIRMWARE_ID_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336FirmwareId(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_FIRMWARE_ID_REG, value, 1);
}

/*
 * @brief  Get the FocalTech’s Panel ID.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_CHIP_ID_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336ChipId(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_CHIP_ID_REG, value, 1);
}

/*
 * @brief  Get Release code version.
 *
 * @param[in]       context ft5336 context driver.
 * @param[in, out]  value   Value read to FT5336_RELEASE_CODE_ID_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336ReleaseCodeId(ft5336Context *context, uint8_t *value)
{
    return context->read(context->handler, FT5336_RELEASE_CODE_ID_REG, value, 1);
}

/*
 * @brief  Select current operating mode.
 *
 * @param[in]   context ft5336 context driver.
 * @param[in]   value   Value to write to FT5336_STATE_REG register.
 *
 * @retval Return 0 if was success.
 */
int32_t ft5336SetState(ft5336Context *context, const uint8_t value)
{
    return context->write(context->handler, FT5336_STATE_REG, &value, 1);
}






