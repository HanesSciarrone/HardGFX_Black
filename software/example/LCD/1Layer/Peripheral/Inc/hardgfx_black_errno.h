
#ifndef HARDGFX_BLACK_ERRNO_H
#define HARDGFX_BLACK_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Common errors */
#define HARDGFX_NONE_ERROR                                  0
#define HARDGFX_NULL_POINTER_ARGUMENT                       -1
#define HARDGFX_PERIPHERAL_ERROR                            -2
#define HARDGFX_BLACKLIGHT_ERROR                            -3

/* LCD errors */
#define HARDGFX_LCD_WRONG_ORIENTATION_PARAMETER             -4
#define HARDGFX_LCD_WRONG_PIXEL_FORMAT                      -5
#define HARDGFX_LCD_WRONG_INSTANCE_HANDLER                  -6
#define HARDGFX_LCD_CLOCK_CONFIGURATION_FAIL                -7
#define HARDGFX_LCD_INITIALIZATION_FAIL                     -8
#define HARDGFX_LCD_LAYER_CONFIGURATION_FAIL                -9

/* Backlight errors */
#define HARDGFX_PWM_BASE_INITIALIZATION_FAIL                -10
#define HARDGFX_PWM_CLOCK_INITIALIZATION_FAIL               -11
#define HARDGFX_PWM_INITIALIZATION_FAIL                     -12
#define HARDGFX_PWM_MASTER_CONFIGURATION_FAIL               -13
#define HARDGFX_PWM_CHANNEL_CONFIGURATION_FAIL              -14
#define HARDGFX_PWM_BREAK_DEAD_TIME_INITIALIZATION_FAIL     -15

/* BUS errors */
#define HARDGFX_BUS_WRONG_INSTANCE_HANDLER                  -16
#define HARDGFX_BUS_CLOCK_INITIALIZATION_FAIL               -17
#define HARDGFX_BUS_INITIALIZATION_FAIL                     -18
#define HARDGFX_BUS_DESINITIALIZATION_FAIL                  -19
#define HARDGFX_BUS_ANALOG_FILTER_INITIALIZATION_FAIL       -20
#define HARDGFX_BUS_DIGITAL_FILTER_INITIALIZATION_FAIL      -21
#define HARDGFX_BUS_TRANSMISSION_FAIL                       -22
#define HARDGFX_BUS_RECEPTION_FAIL                          -23
#define HARDGFX_BUS_ACKNOWLEDGE_FAILURE                     -24
#define HARDGFX_BUS_PERIPHERAL_FAILURE                      -25
#define HARDGFX_BUS_BUSY                                    -26

/* Touch screen errors */
#define HARDGFX_TOUCHSCREEN_REGISTER_BUS_FAIL               -27
#define HARDGFX_TOUCHSCREEN_MODULE_FAIL                     -28
#define HARDGFX_TOUCHSCREEN_RECOGNIZE_MODULE_FAIL           -29
#define HARDGFX_TOUCHSCREEN_WRONG_PARAMETERS                -30
#define HARDGFX_TOUCHSCREEN_DESINITIALIZATION_FAIL          -31
#define HARDGFX_TOUCHSCREEN_INTERRUP_ENABLE_FAIL            -32
#define HARDGFX_TOUCHSCREEN_INTERRUP_DISABLE_FAIL           -33
#define HARDGFX_TOUCHSCREEN_GET_STATE_FAIL                  -34
#define HARDGFX_TOUCHSCREEN_GESTURE_CONFIGURATION_FAIL      -35
#define HARDGFX_TOUCHSCREEN_GET_GESTUREID_FAIL              -35

/* DMAGFX errors */
#define HARDGFX_DMAGFX_INITIALIZATION_FAIL                  -36

/* SDRAM and MDMA errors */
#define HARDGFX_SDRAM_INITIALIZATION_FAIL                   -37
#define HARDGFX_SDRAM_DESINITIALIZATION_FAIL                -38
#define HARDGFX_SDRAM_CLOCK_CONFIGURATION_FAIL              -39
#define HARDGFX_MDMA_INITIALIZATION_FAIL                    -40

#ifdef __cplusplus
}
#endif

#endif // #endif HARDGFX_BLACK_ERRNO_H
