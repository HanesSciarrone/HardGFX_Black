#ifndef FT5336REG_H
#define FT5336REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef int32_t (*FT5336Write)(void*, const uint8_t, const uint8_t*, const uint16_t);
typedef int32_t (*FT5336Read) (void*, const uint8_t, uint8_t*, const uint16_t);


/* Current mode register of the FT5336 (R/W) */
#define FT5336_DEV_MODE_REG             0x00

/* Gesture ID register */
#define FT5336_GEST_ID_REG              0x01

/* Touch Data Status register : gives number of active touch points (0..2) */
#define FT5336_TOUCHDATA_STAT_REG       0x02

/* TOUCH1 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH1_XH_REG            0x03U
#define FT5336_TOUCH1_XL_REG            0x04U
#define FT5336_TOUCH1_YH_REG            0x05U
#define FT5336_TOUCH1_YL_REG            0x06U
#define FT5336_TOUCH1_WEIGHT_REG        0x07U
#define FT5336_TOUCH1_MISC_REG          0x08U

/* TOUCH2 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH2_XH_REG            0x09U
#define FT5336_TOUCH2_XL_REG            0x0AU
#define FT5336_TOUCH2_YH_REG            0x0BU
#define FT5336_TOUCH2_YL_REG            0x0CU
#define FT5336_TOUCH2_WEIGHT_REG        0x0DU
#define FT5336_TOUCH2_MISC_REG          0x0EU

/* TOUCH3 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH3_XH_REG            0x0FU
#define FT5336_TOUCH3_XL_REG            0x10U
#define FT5336_TOUCH3_YH_REG            0x11U
#define FT5336_TOUCH3_YL_REG            0x12U
#define FT5336_TOUCH3_WEIGHT_REG        0x13U
#define FT5336_TOUCH3_MISC_REG          0x14U

/* TOUCH4 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH4_XH_REG            0x15U
#define FT5336_TOUCH4_XL_REG            0x16U
#define FT5336_TOUCH4_YH_REG            0x17U
#define FT5336_TOUCH4_YL_REG            0x18U
#define FT5336_TOUCH4_WEIGHT_REG        0x19U
#define FT5336_TOUCH4_MISC_REG          0x1AU

/* TOUCH5 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH5_XH_REG            0x1BU
#define FT5336_TOUCH5_XL_REG            0x1CU
#define FT5336_TOUCH5_YH_REG            0x1DU
#define FT5336_TOUCH5_YL_REG            0x1EU
#define FT5336_TOUCH5_WEIGHT_REG        0x1FU
#define FT5336_TOUCH5_MISC_REG          0x20U

/* TOUCH6 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH6_XH_REG            0x21U
#define FT5336_TOUCH6_XL_REG            0x22U
#define FT5336_TOUCH6_YH_REG            0x23U
#define FT5336_TOUCH6_YL_REG            0x24U
#define FT5336_TOUCH6_WEIGHT_REG        0x25U
#define FT5336_TOUCH6_MISC_REG          0x26U

/* TOUCH7 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH7_XH_REG            0x27U
#define FT5336_TOUCH7_XL_REG            0x28U
#define FT5336_TOUCH7_YH_REG            0x29U
#define FT5336_TOUCH7_YL_REG            0x2AU
#define FT5336_TOUCH7_WEIGHT_REG        0x2BU
#define FT5336_TOUCH7_MISC_REG          0x2CU

/* TOUCH8 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH8_XH_REG            0x2DU
#define FT5336_TOUCH8_XL_REG            0x2EU
#define FT5336_TOUCH8_YH_REG            0x2FU
#define FT5336_TOUCH8_YL_REG            0x30U
#define FT5336_TOUCH8_WEIGHT_REG        0x31U
#define FT5336_TOUCH8_MISC_REG          0x32U

/* TOUCH9 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH9_XH_REG            0x33U
#define FT5336_TOUCH9_XL_REG            0x34U
#define FT5336_TOUCH9_YH_REG            0x35U
#define FT5336_TOUCH9_YL_REG            0x36U
#define FT5336_TOUCH9_WEIGHT_REG        0x37U
#define FT5336_TOUCH9_MISC_REG          0x38U

/* TOUCH10 X, Y coordinates, weight and misc registers */
#define FT5336_TOUCH10_XH_REG           0x39U
#define FT5336_TOUCH10_XL_REG           0x3AU
#define FT5336_TOUCH10_YH_REG           0x3BU
#define FT5336_TOUCH10_YL_REG           0x3CU
#define FT5336_TOUCH10_WEIGHT_REG       0x3DU
#define FT5336_TOUCH10_MISC_REG         0x3EU

/* Threshold for touch detection */
#define FT5336_THRESHOLD_GROUP_REG      0x80

/* Filter function coefficient */
#define FT5336_THRESHOLD_DIFFERENT_REG  0x85

/* Control register to mode operation */
#define FT5336_CONTROL_REG              0x86

/* The time period of switching from Active mode to Monitor mode when there is no touching */
#define FT5336_TIME_ENTER_MONITOR_REG   0x87

/* Report rate in Active mode */
#define FT5336_PERIOD_ACTIVE_REG        0x88

/* Report rate in Monitor mode */
#define FT5336_PERIOD_MONITOR_REG       0x89

/* The value of the minimum allowed angle while Rotating gesture mode */
#define FT5336_RADIAN_VALUE_REG         0x91

/* Maximum offset while Moving Left and Moving Right gesture */
#define FT5336_OFFSET_LEFT_RIGHT_REG    0x92

/* Maximum offset while Moving Up and Moving Down gesture */
#define FT5336_OFFSET_UP_DOWN_REG       0x93

/* Minimum distance while Moving Left and Moving Right gesture */
#define FT5336_DISTANCE_LEFT_RIGHT_REG  0x94

/* Minimum distance while Moving Up and Moving Down gesture */
#define FT5336_DISTANCE_UP_DOWN_REG     0x95

/* Maximum distance while Zoom In and Zoom Out gesture */
#define FT5336_DISTANCE_ZOOM_REG        0x96

/* High 8-bit of LIB Version info */
#define FT5336_LIB_VER_HIGH_REG         0xA1

/* Low 8-bit of LIB Version info */
#define FT5336_LIB_VER_LOW_REG          0xA2

/* Chip Selecting */
#define FT5336_CIPHER_REG               0xA3

/* Interrupt mode register (used when in interrupt mode) */
#define FT5336_GMODE_REG                0xA4

/* Current power mode the FT5336 system is in (R) */
#define FT5336_POWER_MODE_REG           0xA5

/* FT5336 firmware version */
#define FT5336_FIRMWARE_ID_REG          0xA6

/* FT5336 Chip identification register */
#define FT5336_CHIP_ID_REG              0xA8

/* Release code version */
#define FT5336_RELEASE_CODE_ID_REG      0xAF

/* Current operating mode the FT5336 system is in (R) */
#define FT5336_STATE_REG                0xBC

typedef struct
{
    FT5336Write write;
    FT5336Read read;
    void* handler;
}ft5336Context;

/*******************************************************************************
 * Register      : DEV_MODE
 * Address       : 0X00
 * Permission    : RW
 ******************************************************************************/
#define FT5336_DEV_MODE_BIT_MASK                        0x70U
#define FT5336_DEV_MODE_BIT_POSITION                    4
int32_t ft5336DeviceModeWrite(ft5336Context *context, const uint8_t value);
int32_t ft5336DeviceModeRead(ft5336Context *context, uint8_t *value);

/*******************************************************************************
 * Register      : GEST_ID
 * Address       : 0X01
 * Bit Group Name: Gesture ID
 * Permission    : R
 ******************************************************************************/
#define FT5336_GEST_ID_BIT_MASK                         0xFFU
#define FT5336_GEST_ID_BIT_POSITION                     0
int32_t ft5336GestureId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
 * Register      : TD_STATUS
 * Address       : 0X02
 * Bit Group Name: Touch data status
 * Permission    : R
 ******************************************************************************/
#define FT5336_TOUCHDATA_STATUS_BIT_MASK                0x0FU
#define FT5336_TOUCHDATA_STATUS_BIT_POSITION            0
int32_t ft5336TouchDataStatus(ft5336Context *context, uint8_t *value);

/*******************************************************************************
 * Register      : EVT_FLAG
 * Address       : 0X03
 * Bit Group Name: First Event Flag
 * Permission    : R
 * Default value : 0xF0U
 *******************************************************************************/
#define FT5336_TOUCH1_EVENT_FLAG_BIT_MASK               0xC0U
#define FT5336_TOUCH1_EVENT_FLAG_BIT_POSITION           6
int32_t ft5336Touch1EventFlag(ft5336Context *context, uint8_t *value);

/*******************************************************************************
 * Register      : TOUCH1_XH
 * Address       : 0X03
 * Bit Group Name: MSB of the X coordinate of the first touch point
 * Permission    : R
 * Default value : 0x0FU
 *******************************************************************************/
#define FT5336_TOUCH1_XH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH1_XH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch1XHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
 * Register      : TOUCH1_XL
 * Address       : 0X04
 * Bit Group Name: LSB of the X coordinate of the first touch point.
 * Permission    : R
 * Default value : 0xFFU
 *******************************************************************************/
#define FT5336_TOUCH1_XL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH1_XL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch1XLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH1_YL
* Address       : 0X05
* Bit Group Name: First touch ID
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH1_YH_TOUCHID_BIT_MASK               0xF0U
#define FT5336_TOUCH1_YH_TOUCHID_BIT_POSITION           4
int32_t ft5336Touch1YHTouchId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH1_YH
* Address       : 0x06
* Bit Group Name: MSB of the Y coordinate of the first touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH1_YH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH1_YH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch1YHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH1_YL
* Address       : 0X06
* Bit Group Name: LSB of the Y coordinate of the first touch point.
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH1_YL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH1_YL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch1YLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH1_WEIGHT
* Address       : 0X07
* Bit Group Name: First Touch Weight(pressure)
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH1_WEIGHT_BIT_MASK                   0xFFU
#define FT5336_TOUCH1_WEIGHT_BIT_POSITION               0
int32_t ft5336Touch1Weight(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH1_MISC
* Address       : 0X08
* Bit Group Name: First Touch Area
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH1_MISC_BIT_MASK                     0xF0U
#define FT5336_TOUCH1_MISC_BIT_POSITION                 4
int32_t ft5336Touch1Misc(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_XH
* Address       : 0X09
* Bit Group Name: Second Event Flag
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH2_XH_EVENTFLAG_BIT_MASK             0xC0U
#define FT5336_TOUCH2_XH_EVENTFLAG_BIT_POSITION         6
int32_t ft5336Touch2EventFlag(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_XH
* Address       : 0X09
* Bit Group Name: MSB of the X coordinate of the second touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH2_XH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH2_XH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch2XHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_XL
* Address       : 0X0A
* Bit Group Name: LSB of the X coordinate of the second touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH2_XL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH2_XL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch2XLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_YH
* Address       : 0X0B
* Bit Group Name: Second Touch ID
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH2_YH_TOUCHID_BIT_MASK               0xF0U
#define FT5336_TOUCH2_YH_TOUCHID_BIT_POSITION           4
int32_t ft5336Touch2YHTouchId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_YH
* Address       : 0x0B
* Bit Group Name: MSB of the Y coordinate of the second touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH2_YH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH2_YH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch2YHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_YL
* Address       : 0X0C
* Bit Group Name: LSB of the Y coordinate of the second touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH2_YL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH2_YL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch2YLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_WEIGHT
* Address       : 0X0D
* Bit Group Name: Second Touch Weight(pressure)
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH2_WEIGHT_BIT_MASK                   0xFFU
#define FT5336_TOUCH2_WEIGHT_BIT_POSITION               0
int32_t ft5336Touch2Weight(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH2_MISC
* Address       : 0X0E
* Bit Group Name: Second Touch Area
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH2_MISC_BIT_MASK                     0xF0U
#define FT5336_TOUCH2_MISC_BIT_POSITION                 4
int32_t ft5336Touch2Misc(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_XH
* Address       : 0X09
* Bit Group Name: Third Event Flag
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH3_XH_EVENTFLAG_BIT_MASK             0xC0U
#define FT5336_TOUCH3_XH_EVENTFLAG_BIT_POSITION         6
int32_t ft5336Touch3EventFlag(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_XH
* Address       : 0X09
* Bit Group Name: MSB of the X coordinate of the third touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH3_XH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH3_XH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch3XHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_XL
* Address       : 0X0A
* Bit Group Name: LSB of the X coordinate of the third touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH3_XL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH3_XL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch3XLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_YH
* Address       : 0X0B
* Bit Group Name: Third Touch ID
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH3_YH_TOUCHID_BIT_MASK               0xF0U
#define FT5336_TOUCH3_YH_TOUCHID_BIT_POSITION           4
int32_t ft5336Touch3YHTouchId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_YH
* Address       : 0x0B
* Bit Group Name: MSB of the Y coordinate of the third touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH3_YH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH3_YH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch3YHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_YL
* Address       : 0X0C
* Bit Group Name: LSB of the Y coordinate of the third touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH3_YL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH3_YL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch3YLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_WEIGHT
* Address       : 0X0D
* Bit Group Name: Third Touch Weight(pressure)
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH3_WEIGHT_BIT_MASK                   0xFFU
#define FT5336_TOUCH3_WEIGHT_BIT_POSITION               0
int32_t ft5336Touch3Weight(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH3_MISC
* Address       : 0X0E
* Bit Group Name: Third Touch Area
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH3_MISC_BIT_MASK                     0xF0U
#define FT5336_TOUCH3_MISC_BIT_POSITION                 4
int32_t ft5336Touch3Misc(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_XH
* Address       : 0X09
* Bit Group Name: Fourth Event Flag
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH4_XH_EVENTFLAG_BIT_MASK             0xC0U
#define FT5336_TOUCH4_XH_EVENTFLAG_BIT_POSITION         6
int32_t ft5336Touch4EventFlag(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_XH
* Address       : 0X09
* Bit Group Name: MSB of the X coordinate of the fourth touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH4_XH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH4_XH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch4XHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_XL
* Address       : 0X0A
* Bit Group Name: LSB of the X coordinate of the fourth touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH4_XL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH4_XL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch4XLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_YH
* Address       : 0X0B
* Bit Group Name: Fourth Touch ID
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH4_YH_TOUCHID_BIT_MASK               0xF0U
#define FT5336_TOUCH4_YH_TOUCHID_BIT_POSITION           4
int32_t ft5336Touch4YHTouchId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_YH
* Address       : 0x0B
* Bit Group Name: MSB of the Y coordinate of the fourth touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH4_YH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH4_YH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch4YHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_YL
* Address       : 0X0C
* Bit Group Name: LSB of the Y coordinate of the fourth touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH4_YL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH4_YL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch4YLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_WEIGHT
* Address       : 0X0D
* Bit Group Name: Fourth Touch Weight(pressure)
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH4_WEIGHT_BIT_MASK                   0xFFU
#define FT5336_TOUCH4_WEIGHT_BIT_POSITION               0
int32_t ft5336Touch4Weight(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH4_MISC
* Address       : 0X0E
* Bit Group Name: Fourth Touch Area
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH4_MISC_BIT_MASK                     0xF0U
#define FT5336_TOUCH4_MISC_BIT_POSITION                 4
int32_t ft5336Touch4Misc(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_XH
* Address       : 0X09
* Bit Group Name: Fifth Event Flag
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH5_XH_EVENTFLAG_BIT_MASK             0xC0U
#define FT5336_TOUCH5_XH_EVENTFLAG_BIT_POSITION         6
int32_t ft5336Touch5EventFlag(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_XH
* Address       : 0X09
* Bit Group Name: MSB of the X coordinate of the fifth touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH5_XH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH5_XH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch5XHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_XL
* Address       : 0X0A
* Bit Group Name: LSB of the X coordinate of the fifth touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH5_XL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH5_XL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch5XLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_YH
* Address       : 0X0B
* Bit Group Name: Fifth Touch ID
* Permission    : R
* Default value : 0xF0U
*******************************************************************************/
#define FT5336_TOUCH5_YH_TOUCHID_BIT_MASK               0xF0U
#define FT5336_TOUCH5_YH_TOUCHID_BIT_POSITION           4
int32_t ft5336Touch5YHTouchId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_YH
* Address       : 0x0B
* Bit Group Name: MSB of the Y coordinate of the fifth touch point
* Permission    : R
* Default value : 0x0FU
*******************************************************************************/
#define FT5336_TOUCH5_YH_TOUCHPOINT_BIT_MASK            0x0FU
#define FT5336_TOUCH5_YH_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch5YHTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_YL
* Address       : 0X0C
* Bit Group Name: LSB of the Y coordinate of the fifth touch point
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH5_YL_TOUCHPOINT_BIT_MASK            0xFFU
#define FT5336_TOUCH5_YL_TOUCHPOINT_BIT_POSITION        0
int32_t ft5336Touch5YLTouchPoint(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_WEIGHT
* Address       : 0X0D
* Bit Group Name: Fifth Touch Weight(pressure)
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH5_WEIGHT_BIT_MASK                   0xFFU
#define FT5336_TOUCH5_WEIGHT_BIT_POSITION               0
int32_t ft5336Touch5Weight(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TOUCH5_MISC
* Address       : 0X0E
* Bit Group Name: Fifth Touch Area
* Permission    : R
* Default value : 0xFFU
*******************************************************************************/
#define FT5336_TOUCH5_MISC_BIT_MASK                     0xF0U
#define FT5336_TOUCH5_MISC_BIT_POSITION                 4
int32_t ft5336Touch5Misc(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : TH_GROUP
* Address       : 0X80
* Bit Group Name: Threshold for touch detection
* Permission    : RW
* Default value : None
*******************************************************************************/
#define FT5336_THRESHOLD_GROUP_BIT_MASK                 0xFFU
#define FT5336_THRESHOLD_GROUP_BIT_POSITION             0
int32_t ft5336ThresHoldGroup(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : TH_DIFF
* Address       : 0X85
* Bit Group Name: Filter function coefficient
* Permission    : RW
* Default value : None
*******************************************************************************/
#define FT5336_THRESHOLD_DIFFERENT_BIT_MASK             0xFFU
#define FT5336_THRESHOLD_DIFFERENT_BIT_POSITION         0
int32_t ft5336ThresHoldDifferent(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : CTRL
* Address       : 0X86
* Bit Group Name:
* Permission    : RW
* Default value : 0x01
*******************************************************************************/
#define FT5336_CONTROL_BIT_MASK                         0xFFU
#define FT5336_CONTROL_BIT_POSITION                     0
int32_t ft5336Control(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : TIMEENTERMONITOR
* Address       : 0X87
* Bit Group Name: The timer of entering monitor status
* Permission    : RW
* Default value : 0x0A
*******************************************************************************/
#define FT5336_TIME_ENTER_MONITOR_BIT_MASK              0xFFU
#define FT5336_TIME_ENTER_MONITOR_BIT_POSITION          0
int32_t ft5336TimeEnterMonitorStatus(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : PERIODACTIVE
* Address       : 0X88
* Bit Group Name: Period of active status
* Permission    : RW
* Default value : None
*******************************************************************************/
#define FT5336_PERIOD_ACTIVE_BIT_MASK                   0xFFU
#define FT5336_PERIOD_ACTIVE_BIT_POSITION               0
int32_t ft5336PeriodActive(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : PERIODMONITOR
* Address       : 0X89
* Bit Group Name: Period of monitor status
* Permission    : RW
* Default value : 0x28
*******************************************************************************/
#define FT5336_PERIOD_MONITOR_BIT_MASK                  0xFFU
#define FT5336_PERIOD_MONITOR_BIT_POSITION              0
int32_t ft5336PeriodMonitor(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : RADIAN_VALUE
* Address       : 0X91
* Bit Group Name: The value of the minimum allowed angle while rotating gesture mode
* Permission    : RW
* Default value : 0x0A
*******************************************************************************/
#define FT5336_RADIAN_VALUE_BIT_MASK                    0xFFU
#define FT5336_RADIAN_VALUE_BIT_POSITION                0
int32_t ft5336RadianValue(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : OFFSET_LEFT_RIGHT
* Address       : 0X92
* Bit Group Name: Maximum offset while moving left and moving right gesture
* Permission    : RW
* Default value : 0x19
*******************************************************************************/
#define FT5336_OFFSET_LEFT_RIGHT_BIT_MASK               0xFFU
#define FT5336_OFFSET_LEFT_RIGHT_BIT_POSITION           0
int32_t ft5336OffsetLeftRight(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : OFFSET_UP_DOWN
* Address       : 0X93
* Bit Group Name: Maximum offset while moving up and moving down gesture
* Permission    : RW
* Default value : 0x19
*******************************************************************************/
#define FT5336_OFFSET_UP_DOWN_BIT_MASK                  0xFFU
#define FT5336_OFFSET_UP_DOWN_BIT_POSITION              0
int32_t ft5336OffsetUpDown(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : DISTANCE_LEFT_RIGHT
* Address       : 0X94
* Bit Group Name: Minimum distance while moving left and moving right gesture
* Permission    : RW
* Default value : 0x19
*******************************************************************************/
#define FT5336_DISTANCE_LEFT_RIGHT_BIT_MASK             0xFFU
#define FT5336_DISTANCE_LEFT_RIGHT_BIT_POSITION         0
int32_t ft5336DistanceLeftRight(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : DISTANCE_UP_DOWN
* Address       : 0X95
* Bit Group Name: Minimum distance while moving up and moving down gesture
* Permission    : RW
* Default value : 0x19
*******************************************************************************/
#define FT5336_DISTANCE_UP_DOWN_BIT_MASK                0xFFU
#define FT5336_DISTANCE_UP_DOWN_BIT_POSITION            0
int32_t ft5336DistanceUpDown(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : DISTANCE_ZOOM
* Address       : 0X96
* Bit Group Name: Maximum distance while zoom in and zoom out gesture
* Permission    : RW
* Default value : 0x32
*******************************************************************************/
#define FT5336_DISTANCE_ZOOM_BIT_MASK                   0xFFU
#define FT5336_DISTANCE_ZOOM_BIT_POSITION               0
int32_t ft5336DistanceZoom(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : LIB_VER_H
* Address       : 0XA1
* Bit Group Name: High 8-bit of LIB version info
* Permission    : R
* Default value : None
*******************************************************************************/
#define FT5336_LIB_VER_H_BIT_MASK                       0xFFU
#define FT5336_LIB_VER_H_BIT_POSITION                   0
int32_t ft5336LibVerHigh(ft5336Context *context, uint8_t *value);


/*******************************************************************************
* Register      : LIB_VER_L
* Address       : 0XA2
* Bit Group Name: Low 8-bit of LIB version info
* Permission    : R
* Default value : None
*******************************************************************************/
#define FT5336_LIB_VER_LOW_BIT_MASK                     0xFFU
#define FT5336_LIB_VER_LOW_BIT_POSITION                 0
int32_t ft5336LibVerLow(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : CIPHER
* Address       : 0XA3
* Bit Group Name: Chip Selecting
* Permission    : R
* Default value : 0x06
*******************************************************************************/
#define FT5336_CIPHER_BIT_MASK                          0xFFU
#define FT5336_CIPHER_BIT_POSITION                      0
int32_t ft5336Cipher(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : G_MODE
* Address       : 0XA4
* Bit Group Name: Select interrupt mode (0x00: Interrupt Polling mode | 0x01: Interrupt Trigger mode)
* Permission    : RW
* Default value : 0x01
*******************************************************************************/
#define FT5336_G_MODE_BIT_MASK                          0xFFU
#define FT5336_G_MODE_BIT_POSITION                      0
int32_t ft5336InterruptMode(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : PWR_MODE
* Address       : 0XA5
* Bit Group Name: Current power mode which system is in
* Permission    : RW
* Default value : 0x00
*******************************************************************************/
#define FT5336_POWER_MODE_BIT_MASK                      0xFFU
#define FT5336_POWER_MODE_BIT_POSITION                  0
int32_t ft5336PowerMode(ft5336Context *context, const uint8_t value);

/*******************************************************************************
* Register      : FIRMID
* Address       : 0XA6
* Bit Group Name: Firmware Version
* Permission    : R
* Default value : None
*******************************************************************************/
#define FT5336_FIRMWARE_ID_BIT_MASK                     0xFFU
#define FT5336_FIRMWARE_ID_BIT_POSITION                 0
int32_t ft5336FirmwareId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* register      : focaltech_id
* address       : 0xa8
* bit group name: FocalTech’s Panel ID
* permission    : r
* default value : 0x11
*******************************************************************************/
#define FT5336_CHIP_ID_BIT_MASK                         0xFFU
#define FT5336_CHIP_ID_BIT_POSITION                     0
int32_t ft5336ChipId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : RELEASE_CODE_ID
* Address       : 0XAF
* Bit Group Name: Release code version
* Permission    : R
* Default value : 0x001
*******************************************************************************/
#define FT5336_RELEASE_CODE_ID_BIT_MASK                 0xFFU
#define FT5336_RELEASE_CODE_ID_BIT_POSITION             0
int32_t ft5336ReleaseCodeId(ft5336Context *context, uint8_t *value);

/*******************************************************************************
* Register      : STATE
* Address       : 0XBC
* Bit Group Name: Current Operating mode
* Permission    : RW
* Default value : 0x01
*******************************************************************************/
#define FT5336_STATE_BIT_MASK                           0xFFU
#define FT5336_STATE_BIT_POSITION                       0
int32_t ft5336SetState(ft5336Context *context, const uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* FT5336REG_H */
