/*
 * hardgfx_black_bsp_lcd.h
 *
 *  Created on: Feb 25, 2023
 *      Author: hanes
 */

#ifndef INC_HARDGFX_BLACK_BSP_LCD_H_
#define INC_HARDGFX_BLACK_BSP_LCD_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <hardgfx_black_lcd.h>
#include <hardgfx_black_dmagfx.h>
#include <hardgfx_black_sdram.h>


#define HARDGFX_BSP_LCD_RELOAD_NONE                         0U                            /* No reload executed       */
#define HARDGFX_BSP_LCD_RELOAD_IMMEDIATE                    LTDC_RELOAD_IMMEDIATE         /* Immediate Reload         */
#define HARDGFX_BSP_LCD_RELOAD_VERTICAL_BLANKING            LTDC_RELOAD_VERTICAL_BLANKING /* Vertical Blanking Reload */

/* RGB565 colors definitions */
#define HARDGFX_BSP_LCD_COLOR_RGB565_BLUE                   0x001FU
#define HARDGFX_BSP_LCD_COLOR_RGB565_GREEN                  0x07E0U
#define HARDGFX_BSP_LCD_COLOR_RGB565_RED                    0xF800U
#define HARDGFX_BSP_LCD_COLOR_RGB565_CYAN                   0x07FFU
#define HARDGFX_BSP_LCD_COLOR_RGB565_MAGENTA                0xF81FU
#define HARDGFX_BSP_LCD_COLOR_RGB565_YELLOW                 0xFFE0U
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTBLUE              0x841FU
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTGREEN             0x87F0U
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTRED               0xFC10U
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTCYAN              0x87FFU
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTMAGENTA           0xFC1FU
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTYELLOW            0xFFF0U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKBLUE               0x0010U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKGREEN              0x0400U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKRED                0x8000U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKCYAN               0x0410U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKMAGENTA            0x8010U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKYELLOW             0x8400U
#define HARDGFX_BSP_LCD_COLOR_RGB565_WHITE                  0xFFFFU
#define HARDGFX_BSP_LCD_COLOR_RGB565_LIGHTGRAY              0xD69AU
#define HARDGFX_BSP_LCD_COLOR_RGB565_GRAY                   0x8410U
#define HARDGFX_BSP_LCD_COLOR_RGB565_DARKGRAY               0x4208U
#define HARDGFX_BSP_LCD_COLOR_RGB565_BLACK                  0x0000U
#define HARDGFX_BSP_LCD_COLOR_RGB565_BROWN                  0xA145U
#define HARDGFX_BSP_LCD_COLOR_RGB565_ORANGE                 0xFD20U

/* ARGB8888 colors definitions */
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_BLUE                 0xFF0000FFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_GREEN                0xFF00FF00UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_RED                  0xFFFF0000UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_CYAN                 0xFF00FFFFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_MAGENTA              0xFFFF00FFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_YELLOW               0xFFFFFF00UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTBLUE            0xFF8080FFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTGREEN           0xFF80FF80UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTRED             0xFFFF8080UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTCYAN            0xFF80FFFFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTMAGENTA         0xFFFF80FFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTYELLOW          0xFFFFFF80UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKBLUE             0xFF000080UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKGREEN            0xFF008000UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKRED              0xFF800000UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKCYAN             0xFF008080UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKMAGENTA          0xFF800080UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKYELLOW           0xFF808000UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_WHITE                0xFFFFFFFFUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_LIGHTGRAY            0xFFD3D3D3UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_GRAY                 0xFF808080UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_DARKGRAY             0xFF404040UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_BLACK                0xFF000000UL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_BROWN                0xFFA52A2AUL
#define HARDGFX_BSP_LCD_COLOR_ARGB8888_ORANGE               0xFFFFA500UL


typedef enum
{
    LCD_PORTRAIT,
    LCD_LANDSCAPE,
    LCD_MAX_ORIENTATION     // It always must be the last value
}lcdOrientation;

/* Initialize API */
int32_t HardGFXLcdInit(const lcdOrientation orientation, const HardGFX_Pixel_Format_t pixelFormat, const uint32_t width, const uint32_t heigth);

/* Layer control APIs (LCD specific) */
uint32_t HardGFX_BSP_LCD_Reload(const uint32_t reloadType);
void HardGFX_BSP_LCD_SetLayerVisible(const uint32_t layerIndex, const FunctionalState state);
uint32_t HardGFX_BSP_LCD_SetTransparency(const uint32_t layerIndex, const uint8_t transparency);
uint32_t HardGFX_BSP_LCD_SetLayerAddress(const uint32_t layerIndex, const uint32_t address);
uint32_t HardGFX_BSP_LCD_SetLayerWindow(const uint16_t layerIndex, const uint16_t xPos, const uint16_t yPos, const uint16_t width, const uint16_t height);
uint32_t HardGFX_BSP_LCD_SetColorKeying(const uint32_t layerIndex, const uint32_t color);
uint32_t HardGFX_BSP_LCD_ResetColorKeying(const  uint32_t layerIndex);

/* Display control APIs */
void HardGFX_BSP_LCD_DisplayOn(void);
void HardGFX_BSP_LCD_DisplayOff(void);
uint32_t HardGFX_BSP_LCD_SetBrightness(const uint32_t brightness);
uint32_t HardGFX_BSP_LCD_GetBrightness(void);
uint32_t HardGFX_BSP_LCD_GetXSize(void);
uint32_t HardGFX_BSP_LCD_GetYSize(void);
uint32_t HardGFX_BSP_LCD_GetAddressLayer(const uint32_t xPos, const uint32_t yPos);

/* Draw operations APIs */
void HardGFX_BSP_LCD_SetActiveLayer(const uint32_t layerIndex);
uint32_t HardGFX_BSP_LCD_GetPixelFormat(void);
bool HardGFX_BSP_LCD_DrawBitmap(const uint32_t xPos, const uint32_t yPos, uint8_t *bitmap);
bool HardGFX_BSP_LCD_DrawHLine(const uint32_t xPos, const uint32_t yPos, uint32_t length, const uint32_t color);
bool HardGFX_BSP_LCD_DrawVLine(const uint32_t xPos, const uint32_t yPos, uint32_t length, const uint32_t color);
bool HardGFX_BSP_LCD_FillRGBRect(const uint32_t xPos, const uint32_t yPos, uint8_t *data, const uint32_t width, const uint32_t height);
bool HardGFX_BSP_LCD_FillRect(const uint32_t xPos, const uint32_t yPos, const uint32_t width, const uint32_t height, const uint32_t color);
uint32_t HardGFX_BSP_LCD_ReadPixel(const uint32_t xPos, const uint32_t yPos);
void HardGFX_BSP_LCD_WritePixel(const uint32_t xPos, const uint32_t yPos, const uint32_t color);

#ifdef __cplusplus
}
#endif

#endif /* INC_HARDGFX_BLACK_BSP_LCD_H_ */
