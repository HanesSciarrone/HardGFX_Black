#ifndef INC_HARDGFX_BLACK_BSP_TS_H_
#define INC_HARDGFX_BLACK_BSP_TS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hardgfx_black_conf.h"
#include "hardgfx_black_errno.h"
#include "ft5336.h"


#ifndef HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH
#define HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH     1U
#endif

#ifndef HARDGFX_USE_TOUCHSCREEN_GESTURE
#define HARDGFX_USE_TOUCHSCREEN_GESTURE         1U
#endif

#ifndef HARDGFX_TOUCHSCREEN_NUMBER
#define HARDGFX_TOUCHSCREEN_NUMBER              2U
#endif

#define HARDGFX_TS_MAX_WIDTH                    480U     // Touchscreen pad max width
#define HARDGFX_TS_MAX_HEIGHT                   272U     // Touchscreen pad max height

#define HARDGFX_TS_ADDRESS                      0x70U



#define HARDGFX_TS_INT_PIN                      GPIO_PIN_2
#define HARDGFX_TS_INT_GPIO_PORT                GPIOG
#define HARDGFX_TS_INT_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOG_CLK_ENABLE()
#define HARDGFX_TS_INT_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOG_CLK_DISABLE()
#define HARDGFX_TS_INT_EXTI_IRQn                EXTI2_IRQn
#define HARDGFX_TS_EXTI_LINE                    EXTI_LINE_2


typedef enum
{
    TS_SWAP_NONE,
    TS_SWAP_X,
    TS_SWAP_Y,
    TS_SWAP_XY
}touchScreenOrientation;

typedef enum
{
    GESTURE_ID_NO_GESTURE,  /*!< No Gesture*/
    GESTURE_ID_MOVE_UP,     /*!< Gesture Move Up */
    GESTURE_ID_MOVE_RIGHT,  /*!< Gesture Move Right */
    GESTURE_ID_MOVE_DOWN,   /*!< Gesture Move Down */
    GESTURE_ID_MOVE_LEFT,   /*!< Gesture Move Left */
    GESTURE_ID_ZOOM_IN,     /*!< Gesture Zoom In */
    GESTURE_ID_ZOOM_OUT     /*!< Gesture Zoom Out */
}touchScreenGestureId;


typedef struct
{
  uint32_t   width;                  // Screen Width
  uint32_t   height;                 // Screen Height
  uint32_t   orientation;            // Touch Screen orientation from the upper left position
  uint32_t   accuracy;               // Expressed in pixel and means the x or y difference vs old position to consider the new values valid
}touchScreenInit;

typedef struct
{
    uint32_t width;
    uint32_t height;
    touchScreenOrientation orientation;
    uint32_t accuracy;
    uint32_t maxX;
    uint32_t maxY;
    uint32_t previousX[HARDGFX_TOUCHSCREEN_NUMBER];
    uint32_t previousY[HARDGFX_TOUCHSCREEN_NUMBER];
}touchScreenCapabilities;

typedef struct
{
    uint8_t  touchDetected;
    uint32_t touchX;
    uint32_t touchY;
}touchScreenState;

#if (HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH == 1)
typedef struct
{
  uint32_t  touchDetected;
  uint32_t  touchX[HARDGFX_TOUCHSCREEN_NUMBER];
  uint32_t  touchY[HARDGFX_TOUCHSCREEN_NUMBER];
}touchScreenMultiTouchState;
#endif

#if (HARDGFX_USE_TOUCHSCREEN_GESTURE == 1)
typedef struct
{
    uint32_t Radian;
    uint32_t OffsetLeftRight;
    uint32_t OffsetUpDown;
    uint32_t DistanceLeftRight;
    uint32_t DistanceUpDown;
    uint32_t DistanceZoom;
}touchScreenGestureParameters;
#endif

int32_t HardGFXTouchScreenInit(const touchScreenInit* parameters);
int32_t HardGFXTouchScreenDeInit(void);
int32_t HardGFXTouchScreenEnableIT(void);
int32_t HardGFXTouchScreenDisableIT(void);
int32_t HardGFXTouchScreenGetState(touchScreenState* state);
#if (HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH == 1)
int32_t HardGFXTouchScreenGetMultiTouchState(touchScreenMultiTouchState* state);
#endif
#if (HARDGFX_USE_TOUCHSCREEN_GESTURE == 1)
int32_t HardGFXTouchScreenGestureConfig(const touchScreenGestureParameters* parameters);
int32_t HardGFXTouchScreenGetGestureId(uint8_t* gestureId);
#endif
void HardGFXTouchScreenSetOrientation(const touchScreenOrientation orientation);
touchScreenOrientation HardGFXTouchScreenGetOrientation(void);
void HardGFXTouchScreenIRQHandler(void);
void HardGFXTouchScreenCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_HARDGFX_BLACK_BSP_TS_H_ */
