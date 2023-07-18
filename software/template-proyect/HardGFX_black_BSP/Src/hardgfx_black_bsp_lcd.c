/*
 * hardgfx_black_bsp_lcd.c
 *
 *  Created on: Feb 25, 2023
 *      Author: hanes
 */

#include "hardgfx_black_bsp_lcd.h"
#include "hardgfx_black_bsp_ts.h"

struct HardGFX_BSP_LCD
{
    uint8_t     bppFactor;
    uint8_t     activeLayer;
    uint8_t     reloadEnable;
    uint8_t     brightness;
    uint32_t    pixelFormat;
    uint32_t    xSize;
    uint32_t    ySize;
}lcdObject;

/* --------------------------------------- Private macros definition --------------------------------------- */
#define CONVERT_RGB565_TO_ARGB8888(color)   ((((((((color) >> (11U)) & 0x1FU) * 527U) + 23U) >> (6U)) << (16U)) |\
                                            (((((((color) >> (5U)) & 0x3FU) * 259U) + 33U) >> (6U)) << (8U)) |\
                                            (((((color) & 0x1FU) * 527U) + 23U) >> (6U)) | (0xFF000000U))
/* --------------------------------------------------------------------------------------------------------- */



/* ------------------------------------- Private functions declaration ------------------------------------- */
static bool convertLineToRGB(uint32_t *bufferSource, uint32_t *bufferDestination, const uint32_t xSize, const uint32_t colorMode);
static bool fillBuffer(uint32_t *bufferDestination, uint32_t xSize, uint32_t ySize, uint32_t offLine, const uint32_t color);
/* --------------------------------------------------------------------------------------------------------- */

int32_t HardGFXLcdInit(const lcdOrientation orientation, const HardGFX_Pixel_Format_t pixelFormat, const uint32_t width, const uint32_t heigth)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    touchScreenInit touchscreen = { 0 };

    if (orientation > LCD_MAX_ORIENTATION)
    {
        retVal = HARDGFX_LCD_WRONG_ORIENTATION_PARAMETER;
    }
    else
    {
        lcdHandler.Instance = LTDC;
        dmagfxHandle.Instance = DMA2D;

        HardGFX_LDC_GPIO_Init(&lcdHandler);
        HardGFX_DMAGFX_GPIO_Init(&dmagfxHandle);

        touchscreen.width = width;
        touchscreen.height = heigth;
        touchscreen.orientation = TS_SWAP_XY;
        touchscreen.accuracy = HARDGFX_TOUCHSCREEN_ACCURACY;

        retVal = HardGFXTouchScreenInit(&touchscreen);

        if (retVal == HARDGFX_NONE_ERROR)
        {
            retVal = HardGFX_LCD_ClockConfig(&lcdHandler);
        }

        if (retVal == HARDGFX_NONE_ERROR)
        {
            retVal = HardGFX_LDC_Init(width, heigth);
        }
    }

    if (retVal == HARDGFX_NONE_ERROR)
    {
        retVal = HardGFX_SDRAM_Periphreal();
    }

    if (retVal == HARDGFX_NONE_ERROR)
    {
        HardGFX_LDC_LayerInit_t layerInit = { 0 };

        layerInit.startX = 0;
        layerInit.endX = width;
        layerInit.startY = 0;
        layerInit.endY = heigth;
        layerInit.pixelFormat = pixelFormat;
        layerInit.alpha = 255;
        layerInit.imageWidth = width;
        layerInit.imageHeight = heigth;
        layerInit.startAddress = HARDGFX_LCD_LAYER_0_ADDRESS;

        retVal = HardGFX_LCD_Layer_Init(&lcdHandler, &layerInit, 1);
    }

    if (retVal == HARDGFX_NONE_ERROR)
    {
        // Initialize the first configuration to back-light control.
        retVal = HardGFX_LCD_Backlight_Init();
    }

    lcdObject.pixelFormat  = pixelFormat;
    lcdObject.xSize        = width;
    lcdObject.ySize        = heigth;
    lcdObject.bppFactor    = (pixelFormat == HARDGFX_LCD_PIXEL_FORMAT_RGB565) ? 2U : 4U;
    lcdObject.reloadEnable = 1U;

    return retVal;
}

/**
  * @brief  Control the LCD reload.
  *
  * @param  reloadType Must be one of the following values:
  *         - HARDGFX_BSP_LCD_RELOAD_NONE
  *         - HARDGFX_BSP_LCD_RELOAD_IMMEDIATE
  *         - HARDGFX_BSP_LCD_RELOAD_VERTICAL_BLANKING
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_Reload(const uint32_t reloadType)
{
    uint32_t errno = HARDGFX_NONE_ERROR;

    if (reloadType == HARDGFX_BSP_LCD_RELOAD_NONE)
    {
        lcdObject.reloadEnable = 0U;
    }
    else if (HAL_LTDC_Reload(&lcdHandler, reloadType) != HAL_OK)
    {
        errno = HARDGFX_PERIPHERAL_ERROR;
    }
    else
    {
        lcdObject.reloadEnable = 1U;
    }

    return errno;
}

/**
  * @brief  Configure the LCD layer visible
  *
  * @param  layerIndex  Visible layer.
  * @param  state  New state of the specified layer, It must be one of the following values:
  *
  *            @arg  ENABLE
  *            @arg  DISABLE
  */
void HardGFX_BSP_LCD_SetLayerVisible(const uint32_t layerIndex, const FunctionalState state)
{
    if(state == ENABLE)
    {
        __HAL_LTDC_LAYER_ENABLE(&lcdHandler, layerIndex);
    }
    else
    {
        __HAL_LTDC_LAYER_DISABLE(&lcdHandler, layerIndex);
    }

    if(lcdObject.reloadEnable)
    {
        __HAL_LTDC_RELOAD_IMMEDIATE_CONFIG(&lcdHandler);
    }
}

/**
  * @brief  Configures the transparency.
  *
  * @param  layerIndex    Layer foreground or background.
  * @param  Transparency  Transparency, it must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_SetTransparency(const uint32_t layerIndex, const uint8_t transparency)
{
    HAL_StatusTypeDef errno = HAL_OK;

    if(lcdObject.reloadEnable)
    {
        errno = HAL_LTDC_SetAlpha(&lcdHandler, transparency, layerIndex);
    }
    else
    {
        errno = HAL_LTDC_SetAlpha_NoReload(&lcdHandler, transparency, layerIndex);
    }

    return (errno == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_PERIPHERAL_ERROR;

}

/**
  * @brief  Configure the framebuffer address of the LCD.
  *
  * @param  layerIndex  Layer foreground or background
  * @param  address     New LCD's framebuffer address
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_SetLayerAddress(const uint32_t layerIndex, const uint32_t address)
{
    HAL_StatusTypeDef errno = HAL_OK;

    if(lcdObject.reloadEnable)
    {
        errno = HAL_LTDC_SetAddress(&lcdHandler, address, layerIndex);
    }
    else
    {
        errno = HAL_LTDC_SetAddress_NoReload(&lcdHandler, address, layerIndex);
    }

    return (errno == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_PERIPHERAL_ERROR;

}

/**
  * @brief  Configure display window.
  *
  * @param  layerIndex  Layer index.
  * @param  xPos   LCD X position.
  * @param  yPos   LCD Y position.
  * @param  width  LCD window width.
  * @param  height LCD window height.
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_SetLayerWindow(const uint16_t layerIndex, const uint16_t xPos, const uint16_t yPos, const uint16_t width, const uint16_t height)
{
    HAL_StatusTypeDef errno1 = HAL_OK;
    HAL_StatusTypeDef errno2 = HAL_OK;

    if(lcdObject.reloadEnable)
    {
        /* Reconfigure the layer size  and position */
        errno1 = HAL_LTDC_SetWindowSize(&lcdHandler, width, height, layerIndex);
        errno2 = HAL_LTDC_SetWindowPosition(&lcdHandler, xPos, yPos, layerIndex);
    }
    else
    {
        /* Reconfigure the layer size and position */
        errno1 = HAL_LTDC_SetWindowSize_NoReload(&lcdHandler, width, height, layerIndex);
        errno2 = HAL_LTDC_SetWindowPosition_NoReload(&lcdHandler, xPos, yPos, layerIndex);
    }

    if (errno1 == HAL_OK && errno2 == HAL_OK)
    {
        lcdObject.xSize = width;
        lcdObject.ySize = height;
    }

    return (errno1 == HAL_OK && errno2 == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_PERIPHERAL_ERROR;
}

/**
  * @brief  Configures and sets the color keying.
  *
  * @param  layerIndex  Layer foreground or background.
  * @param  color       Color reference.
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_SetColorKeying(const uint32_t layerIndex, const uint32_t color)
{
    HAL_StatusTypeDef errno1 = HAL_OK;
    HAL_StatusTypeDef errno2 = HAL_OK;

    if(lcdObject.reloadEnable)
    {
        // Configure and Enable the color Keying for LCD Layer
        errno1 = HAL_LTDC_ConfigColorKeying(&lcdHandler, color, layerIndex);
        errno2 = HAL_LTDC_EnableColorKeying(&lcdHandler, layerIndex);
    }
    else
    {
        // Configure and Enable the color Keying for LCD Layer
        errno1 = HAL_LTDC_ConfigColorKeying_NoReload(&lcdHandler, color, layerIndex);
        errno2 = HAL_LTDC_EnableColorKeying_NoReload(&lcdHandler, layerIndex);
    }

    return (errno1 == HAL_OK && errno2 == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_PERIPHERAL_ERROR;
}

/**
  * @brief  Disables the color keying.
  *
  * @param  LayerIndex Layer foreground or background.
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_ResetColorKeying(const  uint32_t layerIndex)
{
    HAL_StatusTypeDef errno = HAL_OK;

    if(lcdObject.reloadEnable)
    {
        // Disable the color Keying for LCD Layer
        errno = HAL_LTDC_DisableColorKeying(&lcdHandler, layerIndex);
    }
    else
    {
        // Disable the color Keying for LCD Layer
        errno = HAL_LTDC_DisableColorKeying_NoReload(&lcdHandler, layerIndex);
    }

    return (errno == HAL_OK) ? HARDGFX_NONE_ERROR : HARDGFX_PERIPHERAL_ERROR;
}

/**
  * @brief  Switch On the display.
  */
void HardGFX_BSP_LCD_DisplayOn(void)
{
    __HAL_LTDC_ENABLE(&lcdHandler);

    // Power-on LCD_DISP pin
    HAL_GPIO_WritePin(LCD_EN_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET);
}

/**
  * @brief  Switch Off the display.
  */
void HardGFX_BSP_LCD_DisplayOff(void)
{
    __HAL_LTDC_DISABLE(&lcdHandler);
    HAL_GPIO_WritePin(LCD_EN_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_PIN, GPIO_PIN_RESET);
}

/**
  * @brief  Configure the brightness value
  *
  * @param  brightness Value between 00 (Min) and 100 (Max).
  *
  * @retval status operation.
  */
uint32_t HardGFX_BSP_LCD_SetBrightness(const uint32_t brightness)
{
    uint32_t errno = HARDGFX_NONE_ERROR;
    TIM_OC_InitTypeDef configureOC;

    if (HAL_TIM_PWM_Stop(&timHandler, LCD_TIMx_CHANNEL) == HAL_OK)
    {
        configureOC.OCMode = TIM_OCMODE_PWM1;
        configureOC.Pulse = (LCD_TIMX_PERIOD_VALUE * brightness) / 100U;
        configureOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        configureOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        configureOC.OCFastMode = TIM_OCFAST_DISABLE;
        configureOC.OCIdleState = TIM_OCIDLESTATE_RESET;
        configureOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

        if (HAL_TIM_PWM_ConfigChannel(&timHandler, &configureOC, LCD_TIMx_CHANNEL) == HAL_OK)
        {
            if (HAL_TIM_PWM_Start(&timHandler, LCD_TIMx_CHANNEL) == HAL_OK)
            {
                lcdObject.brightness = brightness;
            }
            else
            {
                errno = HARDGFX_BLACKLIGHT_ERROR;
            }
        }
        else
        {
            errno = HARDGFX_BLACKLIGHT_ERROR;
        }
    }
    else
    {
        errno = HARDGFX_BLACKLIGHT_ERROR;
    }

    return errno;
}

/**
  * @brief  Get the brightness value
  *
  * @retval Brightness value.
  */
uint32_t HardGFX_BSP_LCD_GetBrightness(void)
{
    return lcdObject.brightness;
}

/**
  * @brief  Get the LCD X side
  *
  * @retval X side.
  */
uint32_t HardGFX_BSP_LCD_GetXSize(void)
{
    return lcdObject.xSize;
}

/**
  * @brief  Get the LCD Y side
  *
  * @retval Y side.
  */
uint32_t HardGFX_BSP_LCD_GetYSize(void)
{
    return lcdObject.ySize;
}

/**
  * @brief  Set the LCD active layer.
  *
  * @param  layerIndex Index of the active layer..
  */
void HardGFX_BSP_LCD_SetActiveLayer(const uint32_t layerIndex)
{
    lcdObject.activeLayer = layerIndex;
}

/**
  * @brief  Gets the pixel format used in the LCD.
  *
  * @retval Return the pixel format.
  */
uint32_t HardGFX_BSP_LCD_GetPixelFormat(void)
{
    return lcdObject.pixelFormat;
}

/**
  * @brief  Draws a bitmap picture loaded in the internal Flash in currently active layer.
  *
  * @param  xPos Bitmap X position in the screen
  * @param  yPos Bitmap Y position in the screen
  * @param  bitmap Pointer to bitmap picture address in the internal Flash.
  *
  * @retval Return true if an error happen in otherwise false.
  */
bool HardGFX_BSP_LCD_DrawBitmap(const uint32_t xPos, const uint32_t yPos, uint8_t *bitmap)
{
    uint32_t index, width, height, bitPerPixel = 0;
    uint32_t address = 0;
    uint32_t inputColorMode = 0;
    uint8_t *pbitmap = NULL;
    bool error = false;

    // Get bitmap data address offset
    index = (uint32_t)bitmap[10] + ((uint32_t)bitmap[11] << 8) + ((uint32_t)bitmap[12] << 16)  + ((uint32_t)bitmap[13] << 24);

    // Read bitmap width
    width = (uint32_t)bitmap[18] + ((uint32_t)bitmap[19] << 8) + ((uint32_t)bitmap[20] << 16)  + ((uint32_t)bitmap[21] << 24);

    // Read bitmap height
    height = (uint32_t)bitmap[22] + ((uint32_t)bitmap[23] << 8) + ((uint32_t)bitmap[24] << 16)  + ((uint32_t)bitmap[25] << 24);

    // Read bit per pixel
    bitPerPixel = (uint32_t)bitmap[28] + ((uint32_t)bitmap[29] << 8);

    // Set the address
    address = lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + (((lcdObject.xSize * yPos) + xPos) * lcdObject.bppFactor);

    // Get the layer pixel format
    if ((bitPerPixel/8U) == 4U)
    {
        inputColorMode = DMAGFX_INPUT_ARGB8888;
    }
    else if ((bitPerPixel/8U) == 2U)
    {
        inputColorMode = DMA2D_INPUT_RGB565;
    }
    else
    {
        inputColorMode = DMA2D_INPUT_RGB888;
    }

    // Bypass the bitmap header
    pbitmap = bitmap + (index + (width * (height - 1U) * (bitPerPixel/8U)));

    /* Convert picture to ARGB8888 pixel format */
    for(index=0; index < height; index++)
    {
        // Pixel format conversion
        if (convertLineToRGB((uint32_t *)pbitmap, (uint32_t *)address, width, inputColorMode))
        {
            error = true;
            break;
        }

        // Increment the source and destination buffers
        address +=  (lcdObject.xSize * lcdObject.bppFactor);
        pbitmap -= width*(bitPerPixel/8U);
    }

    return error;
}

/**
  * @brief  Draws a horizontal line in currently active layer.
  *
  * @param  xPos    X position
  * @param  yPos    Y position
  * @param  length  Line length
  * @param  color   RGB color
  *
  * @retval Return true if an error happen in otherwise false.
  */
bool HardGFX_BSP_LCD_DrawHLine(const uint32_t xPos, const uint32_t yPos, uint32_t length, const uint32_t color)
{
    uint32_t  address;

    // Get the line address
    address = lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + (((lcdObject.xSize * yPos) + xPos) * lcdObject.bppFactor);

    // Write line
    if((xPos + length) > lcdObject.xSize)
    {
        length = lcdObject.xSize - xPos;
    }

    return fillBuffer((uint32_t *)address, length, 1, 0, color);
}


/**
  * @brief  Draws a vertical line in currently active layer.
  *
  * @param  xPos    X position
  * @param  yPos    Y position
  * @param  length  Line length
  * @param  color   RGB color
  *
  * @retval Return true if an error happen in otherwise false.
  */
bool HardGFX_BSP_LCD_DrawVLine(const uint32_t xPos, const uint32_t yPos, uint32_t length, const uint32_t color)
{
    uint32_t  address;

    // Get the line address
    address = lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + (((lcdObject.xSize * yPos) + xPos) * lcdObject.bppFactor);

    // Write line
    if((yPos + length) > lcdObject.ySize)
    {
        length = lcdObject.ySize - yPos;
    }

    return fillBuffer((uint32_t *)address, 1, length, (lcdObject.xSize - 1U), color);
}

/**
  * @brief  Draw a rectangle on LCD.
  *
  * @param  xPos    X position.
  * @param  yPos    Y position.
  * @param  data    Pointer to RGB line data
  * @param  width   Rectangle width.
  * @param  height  Rectangle Height.
  *
  * @retval Return true if an error happen in otherwise false.
  */
bool HardGFX_BSP_LCD_FillRGBRect(const uint32_t xPos, const uint32_t yPos, uint8_t *data, const uint32_t width, const uint32_t height)
{
    uint32_t yIndex;
    uint8_t *pData = data;
    bool error = false;

#if (USE_DMA2D_TO_FILL_RGB_RECT == 1)
    uint32_t  address;

    for(yIndex = 0; yIndex < height; yIndex++)
    {
        // Get the line address
        address = lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + (((lcdObject.xSize*(yPos + yIndex)) + xPos) * lcdObject.bppFactor);

#if (USE_BSP_CPU_CACHE_MAINTENANCE == 1)
        SCB_CleanDCache_by_Addr((uint32_t *)pData, lcdObject.bppFactor*lcdObject.xSize);
#endif /* USE_BSP_CPU_CACHE_MAINTENANCE */

        // Write line
        if(lcdObject.pixelFormat == HARDGFX_LCD_PIXEL_FORMAT_RGB565)
        {
            if (convertLineToRGB((uint32_t *)pData, (uint32_t *)address, width, DMAGFX_INPUT_RGB565))
            {
                error = true;
                break;
            }
        }
        else
        {
            if(convertLineToRGB((uint32_t *)pData, (uint32_t *)address, width, DMAGFX_INPUT_ARGB8888))
            {
                error = true;
                break;
            }
        }

        pData += lcdObject.bppFactor * width;
    }
#else
    uint32_t color, xIndex;

    for(yIndex = 0; yIndex < height; yIndex++)
    {
        for(xIndex = 0; xIndex < width; xIndex++)
        {
            color = (uint32_t)((uint32_t)*pData | ((uint32_t)(*(pData + 1U)) << 8U) | ((uint32_t)(*(pData + 2U)) << 16U) | ((uint32_t)(*(pData + 3U)) << 24U));
            HardGFX_BSP_LCD_WritePixel(xPos + xIndex, yPos + yIndex, color);
            pData += lcdObject.bppFactor;
        }
    }
#endif

    return error;
}

/**
  * @brief  Draws a full rectangle on LCD.
  *
  * @param  xPos    X position.
  * @param  yPos    Y position.
  * @param  width   Rectangle width.
  * @param  height  Rectangle height.
  * @param  color   RGB color.
  *
  * @retval @retval Return true if an error happen in otherwise false.
  */

bool HardGFX_BSP_LCD_FillRect(const uint32_t xPos, const uint32_t yPos, const uint32_t width, const uint32_t height, const uint32_t color)
{
    uint32_t address = 0;

    address = lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + ((yPos * lcdObject.xSize) + xPos) * lcdObject.bppFactor;
    return fillBuffer((uint32_t *)address, width, height, (lcdObject.xSize - width), color);
}

/**
  * @brief  Reads a LCD pixel.
  *
  * @param  xPos    X position
  * @param  yPos    Y position
  *
  * @retval Return the pixel color of position.
  */

uint32_t HardGFX_BSP_LCD_ReadPixel(const uint32_t xPos, const uint32_t yPos)
{
    uint32_t retVal;
    // Read data from SDRAM memory.
    if (lcdHandler.LayerCfg[lcdObject.activeLayer].PixelFormat == HARDGFX_LCD_PIXEL_FORMAT_ARGB8888)
    {
        retVal = *(__IO uint32_t *)(lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + ((yPos * lcdObject.xSize) + xPos) * 4U);
    }
    else
    {
        retVal = *(__IO uint16_t *)(lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + ((yPos * lcdObject.xSize) + xPos) * 2U);
    }

    return retVal;
}

/**
  * @brief  Draws a pixel on LCD.
  *
  * @param  xPos    X position.
  * @param  yPos    Y position.
  * @param  color   Pixel color.
  */
void HardGFX_BSP_LCD_WritePixel(const uint32_t xPos, const uint32_t yPos, const uint32_t color)
{
    // Write data to SDRAM memory.
    if (lcdHandler.LayerCfg[lcdObject.activeLayer].PixelFormat == HARDGFX_LCD_PIXEL_FORMAT_ARGB8888)
    {
        *(__IO uint32_t *)(lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + ((yPos * lcdObject.xSize) + xPos) * 4U) = color;
    }
    else
    {
        *(__IO uint16_t *)(lcdHandler.LayerCfg[lcdObject.activeLayer].FBStartAdress + ((yPos * lcdObject.xSize) + xPos) * 2U) = (uint16_t)color;
    }
}



/* ------------------------------------ Private functions implementation ----------------------------------- */

/**
  * @brief  Converts a line to an RGB pixel format.
  *
  * @param  bufferSource        Pointer to source buffer.
  * @param  bufferDestination   Output color.
  * @param  xSize               Buffer width.
  * @param  colorMode           Input color mode.
  *
  * @retval Return true if an error happen in otherwise false.
  */
static bool convertLineToRGB(uint32_t *bufferSource, uint32_t *bufferDestination, const uint32_t xSize, const uint32_t colorMode)
{
    HardGFX_DMAGFX_Parameters_t gfxdmaParameter = {0};
    uint32_t outputColorMode;
    bool error = true;

    switch(lcdObject.pixelFormat)
    {
        case HARDGFX_LCD_PIXEL_FORMAT_RGB565:
        {
            outputColorMode = DMAGFX_OUTPUT_RGB565;
            break;
        }
        case HARDGFX_LCD_PIXEL_FORMAT_RGB888:
        default:
        {
            outputColorMode = DMAGFX_OUTPUT_ARGB8888;
            break;
        }
    }

    // Configure the DMA2D Mode, color Mode and output offset
    gfxdmaParameter.mode            = DMAGFX_M2M_PFC;
    gfxdmaParameter.outputColor     = outputColorMode;
    gfxdmaParameter.outputOffset    = 0;

    // Foreground Configuration
    gfxdmaParameter.inputOffset[HARDGFX_DMAGFX_FOREGROUND_LAYER]    = 0x00000000;
    gfxdmaParameter.inputColor[HARDGFX_DMAGFX_FOREGROUND_LAYER]     = colorMode;
    gfxdmaParameter.alphaMode[HARDGFX_DMAGFX_FOREGROUND_LAYER]      = DMAGFX_NO_MODIF_ALPHA;
    gfxdmaParameter.inputAlpha[HARDGFX_DMAGFX_FOREGROUND_LAYER]     = 0xFF;
    gfxdmaParameter.alphaInverted[HARDGFX_DMAGFX_FOREGROUND_LAYER]  = DMAGFX_REGULAR_ALPHA;
    gfxdmaParameter.redBlueSwap[HARDGFX_DMAGFX_FOREGROUND_LAYER]    = DMAGFX_RB_REGULAR;
    gfxdmaParameter.chromaSubSampling                               = DMAGFX_NO_CSS;

    // DMA2D Initialization
    if(HardGFX_DMAGFX_Init(&gfxdmaParameter) == HARDGFX_NONE_ERROR)
    {
        if(HAL_DMA2D_ConfigLayer(&dmagfxHandle, HARDGFX_DMAGFX_FOREGROUND_LAYER) == HAL_OK)
        {
            if (HAL_DMA2D_Start(&dmagfxHandle, (uint32_t)bufferSource, (uint32_t)bufferDestination, xSize, 1) == HAL_OK)
            {
                // Polling For DMA transfer
                if (HAL_DMA2D_PollForTransfer(&dmagfxHandle, 50) == HAL_OK)
                {
                    error = false;
                }
            }
        }
    }

    return error;
}

/**
  * @brief  Fills a buffer.
  *
  * @param  bufferDestination   Pointer to destination buffer.
  * @param  xSize               Buffer width.
  * @param  ySize               Buffer height.
  * @param  offLine             Offset in the line.
  * @param  Color               Color index.
  *
  * @retval Return true if an error happen in otherwise false.
  */
static bool fillBuffer(uint32_t *bufferDestination, uint32_t xSize, uint32_t ySize, uint32_t offLine, const uint32_t color)
{
    HardGFX_DMAGFX_Parameters_t gfxdmaParameter = {0};
    uint32_t outputColorMode = 0, inputColor = color;
    bool error = true;

    switch(lcdObject.pixelFormat)
    {
        case HARDGFX_LCD_PIXEL_FORMAT_RGB565:
        {
            outputColorMode = DMAGFX_OUTPUT_RGB565;
            inputColor = CONVERT_RGB565_TO_ARGB8888(color);
            break;
        }
        case HARDGFX_LCD_PIXEL_FORMAT_RGB888:
        default:
        {
            outputColorMode = DMAGFX_OUTPUT_ARGB8888;
            break;
        }
    }

    // Register to memory mode with ARGB8888 as color Mode
    gfxdmaParameter.mode            = DMAGFX_R2M;
    gfxdmaParameter.outputColor     = outputColorMode;
    gfxdmaParameter.outputOffset    = offLine;


    if (HardGFX_DMAGFX_Init(&gfxdmaParameter) == HARDGFX_NONE_ERROR)
    {
        if (HAL_DMA2D_Start(&dmagfxHandle, inputColor, (uint32_t)bufferDestination, xSize, ySize) == HAL_OK)
        {
            // Polling For DMA transfer
            if (HAL_DMA2D_PollForTransfer(&dmagfxHandle, 50) == HAL_OK)
            {
                error = false;
            }
        }
    }

    return error;
}
/* --------------------------------------------------------------------------------------------------------- */
