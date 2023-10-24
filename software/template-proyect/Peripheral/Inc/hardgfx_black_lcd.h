#ifndef HARDGFX_LCD_H
#define HARDGFX_LCD_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "hardgfx_black_conf.h"
#include "hardgfx_black_errno.h"

/* Public macros */
#define LCD_DISP_PIN                                    GPIO_PIN_7
#define LCD_DISP_GPIO_PORT                              GPIOD

#define LCD_INT_PIN                                     GPIO_PIN_2
#define LCD_INT_GPIO_PORT                               GPIOG

/* Backlight control pin */
#define LCD_BL_PIN                                      GPIO_PIN_0
#define LCD_BL_GPIO_PORT                                GPIOK
#define LCD_BL_CTRL_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOK_CLK_ENABLE()
#define LCD_BL_CTRL_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOK_CLK_DISABLE()

/* Backlight control configuration */
#define LCD_TIMx                                        TIM8
#define LCD_TIMx_CLK_ENABLE()                           __HAL_RCC_TIM8_CLK_ENABLE()
#define LCD_TIMx_CLK_DISABLE()                          __HAL_RCC_TIM8_CLK_DISABLE()
#define LCD_TIMx_CHANNEL                                TIM_CHANNEL_3
#define LCD_TIMx_CHANNEL_AF                             GPIO_AF3_TIM8
#define LCD_TIMX_PERIOD_VALUE                           50000U  // Period Value
#define LCD_TIMX_PRESCALER_VALUE                        4U      // Prescaler Value

#define LCD_RST_PIN                                     GPIO_PIN_12
#define LCD_RST_GPIO_PORT                               GPIOB

#define HARDGFX_LCD_RELOAD_NONE                         0U                            // No reload executed
#define HARDGFX_LCD_RELOAD_IMMEDIATE                    LTDC_RELOAD_IMMEDIATE         // Immediate Reload
#define HARDGFX_LCD_RELOAD_VERTICAL_BLANKING            LTDC_RELOAD_VERTICAL_BLANKING // Vertical Blanking Reload


typedef LTDC_HandleTypeDef  HardGFX_LCD_HandlerTypeDef;
typedef TIM_HandleTypeDef   HardGFX_PWM_HandlerTypedef;

/* Pixel format available */
typedef enum
{
    HARDGFX_LCD_PIXEL_FORMAT_ARGB8888 = LTDC_PIXEL_FORMAT_ARGB8888,
    HARDGFX_LCD_PIXEL_FORMAT_RGB888 = LTDC_PIXEL_FORMAT_RGB888,
    HARDGFX_LCD_PIXEL_FORMAT_RGB565 = LTDC_PIXEL_FORMAT_RGB565,
    HARDGFX_LCD_PIXEL_FORMAT_ARGB1555 = LTDC_PIXEL_FORMAT_ARGB1555,
    HARDGFX_LCD_PIXEL_FORMAT_ARGB4444 = LTDC_PIXEL_FORMAT_ARGB4444,
    HARDGFX_LCD_PIXEL_FORMAT_L8 = LTDC_PIXEL_FORMAT_L8,
    HARDGFX_LCD_PIXEL_FORMAT_AL44 = LTDC_PIXEL_FORMAT_AL44,
    HARDGFX_LCD_PIXEL_FORMAT_AL88 = LTDC_PIXEL_FORMAT_AL88,
}HardGFX_Pixel_Format_t;

typedef struct
{
    uint32_t startX;
    uint32_t endX;
    uint32_t startY;
    uint32_t endY;
    uint32_t imageWidth;
    uint32_t imageHeight;
    uint32_t alpha;
    uint32_t pixelFormat;
    uint32_t startAddress;
}HardGFX_LDC_LayerInit_t;

extern HardGFX_LCD_HandlerTypeDef lcdHandler;
extern HardGFX_PWM_HandlerTypedef timHandler;

/* API used to configure the LCD peripheral */
int32_t HardGFX_LDC_GPIO_Init(HardGFX_LCD_HandlerTypeDef* lcdHandler);
void HardGFX_LDC_GPIO_DeInit(HardGFX_LCD_HandlerTypeDef* lcdHandler);
int32_t HardGFX_LCD_ClockConfig(HardGFX_LCD_HandlerTypeDef* lcdHandler);
int32_t HardGFX_LDC_Init(const uint32_t width, const uint32_t height);
int32_t HardGFX_LCD_Layer_Init(HardGFX_LCD_HandlerTypeDef* lcdHandler, HardGFX_LDC_LayerInit_t *layers, const char countLayers);
int32_t HardGFX_LCD_Backlight_Init(void);
void HardGFX_LCD_Backlight_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif // #endif HARDGFX_LCD_H
