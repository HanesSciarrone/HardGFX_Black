#include "display.h"

#include "hardgfx_black_bsp_lcd.h"
#include "lvgl.h"

/* ------------------------- Private define ------------------------ */
#define DISPLAY_BUFFER_1        0xD0280000U
#define DISPLAY_BUFFER_2        0xD0300000U
#define DISPLAY_BUFFER_SIZE     DISPLAY_WIDTH * DISPLAY_HEIGHT
/* ----------------------------------------------------------------- */

/* ----------------------- Private variables ----------------------- */
static lv_disp_draw_buf_t drawBuffer = { 0 };    /* Global variable to store the buffers */
static lv_color_t* buffer1 = (lv_color_t* )DISPLAY_BUFFER_1;      /* Global buffer 1 */
static lv_color_t* buffer2 = (lv_color_t* )DISPLAY_BUFFER_2;      /* Global buffer 2 */
static lv_disp_drv_t displayDriver;
static lv_disp_t* display = NULL;
/* ----------------------------------------------------------------- */

/* ------------------ Private function prototypes ------------------ */
static void CleanDCacheCallback(lv_disp_drv_t* driver);
static void flushCallback(lv_disp_drv_t* driver, const lv_area_t* area, lv_color_t* color);
static int32_t transferImageToLcdBuffer(void* source, void* destine, uint32_t xSize, uint32_t ySize);
/* ----------------------------------------------------------------- */

int32_t displayInit(void)
{
    int32_t retVal = DISPLAY_ALREADY_INIT;

    if (NULL == display)
    {
        retVal = HardGFXLcdInit(LCD_LANDSCAPE, HARDGFX_LCD_PIXEL_FORMAT_ARGB8888, DISPLAY_WIDTH, DISPLAY_HEIGHT);

        if (HARDGFX_NONE_ERROR == retVal)
        {
            retVal = HardGFX_BSP_LCD_SetBrightness(100);

            if (HARDGFX_NONE_ERROR == retVal)
            {
                HardGFX_BSP_LCD_DisplayOn();
                lv_disp_draw_buf_init(&drawBuffer, buffer1, buffer2, DISPLAY_BUFFER_SIZE);
                lv_disp_drv_init(&displayDriver);

                displayDriver.draw_buf          = &drawBuffer;
                displayDriver.hor_res           = DISPLAY_WIDTH;
                displayDriver.ver_res           = DISPLAY_HEIGHT;
                displayDriver.clean_dcache_cb   = CleanDCacheCallback;
                displayDriver.flush_cb          = flushCallback;

                display = lv_disp_drv_register(&displayDriver);

                if (NULL == display)
                {
                    retVal = DISPLAY_INIT_ERROR;
                }
            }
        }
    }

    return retVal;
}

static void CleanDCacheCallback(lv_disp_drv_t* driver)
{
    // Example for Cortex-M (CMSIS)
    SCB_CleanInvalidateDCache();
}

static void flushCallback(lv_disp_drv_t* driver, const lv_area_t* area, lv_color_t* color)
{
    if (area->x1 >= 0 && area->y1 >= 0 && area->x2 < HardGFX_BSP_LCD_GetXSize() && area->y2 < HardGFX_BSP_LCD_GetYSize())
    {
        SCB_CleanInvalidateDCache();
        SCB_InvalidateICache();

        uint32_t address = HardGFX_BSP_LCD_GetAddressLayer(area->x1, area->y1);

        if (HARDGFX_NONE_ERROR == transferImageToLcdBuffer((void*)color, (void*)address, lv_area_get_width(area), lv_area_get_height(area)))
        {
            lv_disp_flush_ready(driver);
        }
    }
}

/**
 * @brief  Transfer the LVGL display buffer to the LCD frame buffer
 *  with the conversion image configuration.
 *
 * @param[in]  source   Pointer to source buffer.
 * @param[in]  destine  Pointer to destination buffer LCD frame buffer.
 * @param[in]  xSize    Source buffer width.
 * @param[in]  ySize    Source buffer height.
 *
 * @retval Return HARDGFX_NONE_ERROR on success or the code error on otherwise.
 */
static int32_t transferImageToLcdBuffer(void* source, void* destine, uint32_t xSize, uint32_t ySize)
{
    int32_t retVal = HARDGFX_NONE_ERROR;
    HardGFX_DMAGFX_Parameters_t parameters = { 0 };

    parameters.mode                                             = DMAGFX_M2M_PFC;
    parameters.outputColor                                      = (16 == LV_COLOR_DEPTH) ? DMAGFX_OUTPUT_RGB565 : DMAGFX_OUTPUT_ARGB8888;
    parameters.inputOffset[HARDGFX_DMAGFX_FOREGROUND_LAYER]     = 0x00;
    parameters.inputColor[HARDGFX_DMAGFX_FOREGROUND_LAYER]      = DMAGFX_INPUT_ARGB8888;
    parameters.inputAlpha[HARDGFX_DMAGFX_FOREGROUND_LAYER]      = 0xFF;
    parameters.alphaInverted[HARDGFX_DMAGFX_FOREGROUND_LAYER]   = DMAGFX_REGULAR_ALPHA;
    parameters.redBlueSwap[HARDGFX_DMAGFX_FOREGROUND_LAYER]     = DMAGFX_RB_REGULAR;
    parameters.chromaSubSampling                                = DMAGFX_NO_CSS;

    /**
     * Output offset in pixels == number of pixels to be added at end of line to come
     * to the first pixel of the next line : on the output side of the DMA2D computation.
     */
    parameters.outputOffset = HardGFX_BSP_LCD_GetXSize() - xSize;


    retVal = HardGFX_DMAGFX_Init(&parameters);

    if (HARDGFX_NONE_ERROR == retVal)
    {
        HAL_DMA2D_ConfigLayer(&dmagfxHandle, HARDGFX_DMAGFX_FOREGROUND_LAYER);
        HAL_DMA2D_Start(&dmagfxHandle, (uint32_t)source, (uint32_t)destine, xSize, ySize);

        if (HAL_DMA2D_PollForTransfer(&dmagfxHandle, 20) != HAL_OK)
        {
            retVal = DISPLAY_TRANSFER_BUFFER_ERROR;
        }
    }

    return retVal;
}
