#include "touchpad.h"
#include "hardgfx_black_bsp_ts.h"

#include "lvgl.h"

/* ------------------------- Private define ------------------------ */
/* ----------------------------------------------------------------- */

/* ----------------------- Private variables ----------------------- */
static touchScreenState state = { 0 };
static lv_indev_drv_t touchpadDriver;
static lv_indev_t* touchpad = NULL;
/* ----------------------------------------------------------------- */

/* ------------------ Private function prototypes ------------------ */
static void inputReadCallback(lv_indev_drv_t* driver, lv_indev_data_t* data);
/* ----------------------------------------------------------------- */

int32_t touchpadInit(void)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    touchScreenInit parameters = { 0 };

    parameters.width  = DISPLAY_WIDTH;
    parameters.height = DISPLAY_HEIGHT;
    parameters.orientation = TS_SWAP_XY;
    parameters.accuracy = HARDGFX_TOUCHSCREEN_ACCURACY;

    retVal = HardGFXTouchScreenInit(&parameters);

    if (HARDGFX_NONE_ERROR == retVal)
    {
        lv_indev_drv_init(&touchpadDriver);      /*Basic initialization*/

        touchpadDriver.type     = LV_INDEV_TYPE_POINTER;
        touchpadDriver.read_cb  = inputReadCallback;

        /*Register the driver in LVGL and save the created input device object*/
        touchpad = lv_indev_drv_register(&touchpadDriver);

        if (NULL == touchpad)
        {
            retVal = TOUCHPAD_INIT_ERROR;
        }
    }

    return retVal;
}


/**
 * @brief   Read data from an input device.
 *
 * @param[in]       indev   Pointer to an input device.
 * @param[in,out]   data    Input device will write its data here.
 */

static void inputReadCallback(lv_indev_drv_t* indev, lv_indev_data_t* data)
{
    static uint32_t lastXPos = 0;
    static uint32_t lastYPos = 0;

    if (HARDGFX_NONE_ERROR == HardGFXTouchScreenGetState(&state))
    {
        if (state.touchDetected > 0)
        {
            data->point.x = state.touchX;
            data->point.y = state.touchY;
            data->state = LV_INDEV_STATE_PRESSED;
            lastXPos = state.touchX;
            lastYPos = state.touchY;
        }
        else
        {
            data->point.x = lastXPos;
            data->point.y = lastYPos;
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }


}
