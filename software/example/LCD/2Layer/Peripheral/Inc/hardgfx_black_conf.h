#ifndef HARDGFX_BLACK_CONF_H
#define HARDGFX_BLACK_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"

#define HARDGFX_LCD_INTERRUPT_ENABLE                1
#define HARDGFX_LCD_LAYER_0_ADDRESS                 0xD0000000U
#define HARDGFX_LCD_LAYER_1_ADDRESS                 0xD0200000U

// Touch screen supported features defines
#define HARDGFX_USE_TOUCHSCREEN_MULTI_TOUCH         1U
#define HARDGFX_USE_TOUCHSCREEN_GESTURE             1U

// Default Touch screen touch number
#define HARDGFX_TOUCHSCREEN_NUMBER                  2U

// Accuracy used in touch detection
#define HARDGFX_TOUCHSCREEN_ACCURACY                5U

/** @defgroup DISPLAY_Exported_Constants
  * @{
  */

/**
  * @brief  Display Size
  */
#define  DISPLAY_WIDTH                              ((uint16_t)480) /* LCD PIXEL WIDTH */
#define  DISPLAY_HEIGHT                             ((uint16_t)272) /* LCD PIXEL HEIGHT */

/**
  * @brief  Display Timing
  */
#define  DISPLAY_HSYNC                              ((uint16_t)41)  /* Horizontal synchronization */
#define  DISPLAY_HBP                                ((uint16_t)13)  /* Horizontal back porch      */
#define  DISPLAY_HFP                                ((uint16_t)32)  /* Horizontal front porch     */
#define  DISPLAY_VSYNC                              ((uint16_t)10)  /* Vertical synchronization   */
#define  DISPLAY_VBP                                ((uint16_t)2)   /* Vertical back porch        */
#define  DISPLAY_VFP                                ((uint16_t)2)   /* Vertical front porch       */


/* IRQ priorities */
#define HARDGFX_LCD_IT_PRIORITY                     15U
#define HARDGFX_TOUCHSCREEN_IT_PRIORITY             15U
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif // endif HARDGFX_BLACK_CONF_H
