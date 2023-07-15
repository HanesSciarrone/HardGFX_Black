#ifndef FT5336_H
#define FT5336_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "ft5336Reg.h"

/* These parameters must be edited according the configuration that you want and the size screen you are using. */
#define FT5336_AUTO_CALIBRATION             0
#define FT5336_MAXIMUM_X_LENGTH             800U
#define FT5336_MAXIMUM_Y_LENGTH             480U
/* ------------------------------------------------------------------------------------------------------------ */

#define FT5336_OK                           0
#define FT5336_ERROR                        -1

// Maximum detectable simultaneous touches
#define FT5336_MAXIMUM_SIMULTANEOUS_TOUCH   5

// Touch ft5336 ID
#define FT5336_ID                           0x51U

// Possible device mode
#define FT5336_DEVICE_MODE_WORKING          0x00U
#define FT5336_DEVICE_MODE_FACTORY          0x04U

// Possible Gesture ID
#define FT5336_NO_GESTURE_ID                0x00U
#define FT5336_GESTURE_ID_MOVE_UP           0x10U
#define FT5336_GESTURE_ID_MOVE_RIGHT        0x14U
#define FT5336_GESTURE_ID_MOVE_DOWN         0x18U
#define FT5336_GESTURE_ID_MOVE_LEFT         0x1CU
#define FT5336_GESTURE_ID_ZOOM_IN           0x48U
#define FT5336_GESTURE_ID_ZOOM_OUT          0x49U

// Possible event flag on X high touch-n
#define FT5336_EVENT_FLAG_PRESS_DOWN        0x00U
#define FT5336_EVENT_FLAG_LIFT_UP           0x01U
#define FT5336_EVENT_FLAG_CONTACT           0x02U
#define FT5336_NO_EVENT_FLAG                0x03U

// Possible interrupt mode
#define FT5336_POLLING_INTERRUPT_MODE       0x00U
#define FT5336_TRIGGER_INTERRUPT_MODE       0x01U

typedef int32_t (*ft5336Init)(void);
typedef int32_t (*ft5336DeInit)(void);
typedef uint32_t (*ft5336GetTick)(void);
typedef int32_t (*ft5336WriteRegister)(const uint16_t, const uint16_t, const uint8_t*, const uint16_t);
typedef int32_t (*ft5336ReadRegister)(const uint16_t, const uint16_t, uint8_t*, const uint16_t);

typedef struct
{
    uint32_t Radian;
    uint32_t OffsetLeftRight;
    uint32_t OffsetUpDown;
    uint32_t DistanceLeftRight;
    uint32_t DistanceUpDown;
    uint32_t DistanceZoom;
}ft5336GestureParameters;

typedef struct
{
  uint32_t  touchDetected;
  uint32_t  touchX[FT5336_MAXIMUM_SIMULTANEOUS_TOUCH];
  uint32_t  touchY[FT5336_MAXIMUM_SIMULTANEOUS_TOUCH];
  uint32_t  touchWeight[FT5336_MAXIMUM_SIMULTANEOUS_TOUCH];
  uint32_t  touchEvent[FT5336_MAXIMUM_SIMULTANEOUS_TOUCH];
  uint32_t  touchArea[FT5336_MAXIMUM_SIMULTANEOUS_TOUCH];
} ft5336MultipleTouchState;

typedef struct
{
  uint32_t  touchDetected;
  uint32_t  touchX;
  uint32_t  touchY;
} ft5336TouchState;


typedef struct
{
    ft5336Init          Init;
    ft5336DeInit        DeInit;
    ft5336GetTick       GetTick;
    ft5336WriteRegister WriteRegister;
    ft5336ReadRegister  ReadRegister;
    uint16_t            Address;
}ft5336InputOutput;

typedef struct
{
    ft5336InputOutput   InputOutput;
    ft5336Context       Context;
    bool                IsInitialized;
}ft5336Object;

typedef struct
{
    uint8_t multiTouch;
    uint8_t gesture;
    uint8_t simultaneousTouch;
    uint32_t maxLenghtX;
    uint32_t maxLenghtY;
}ft5336Capabilities;

int32_t ft5336RegisterBus(ft5336Object* object, ft5336InputOutput* inputOutput);
int32_t ft5336Initialization(ft5336Object* object);
int32_t ft5336DesInitialize(ft5336Object* object);
int32_t ft5336GestureConfiguration(ft5336Object* object, const ft5336GestureParameters* parameters);
int32_t ft5336ReadId(ft5336Object* object, uint8_t* id);
int32_t ft5336GetTouchState(ft5336Object* object, ft5336TouchState *state);
int32_t ft5336GetMultipleTouchState(ft5336Object* object, ft5336MultipleTouchState *state);
int32_t ft5336GetGesture(ft5336Object* object, uint8_t* gestureId);
int32_t ft5336EnableIT(ft5336Object* object);
int32_t ft5336DisableIT(ft5336Object* object);
void ft5336GetCapabilities(ft5336Capabilities* capabilities);

#ifdef __cplusplus
}
#endif

#endif /* FT5336_H */
