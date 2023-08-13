/*
 * hardgfx_black_dmagfx.h
 *
 *  Created on: Feb 15, 2023
 *      Author: hanes
 */

#ifndef INC_HARDGFX_BLACK_DMAGFX_H_
#define INC_HARDGFX_BLACK_DMAGFX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hardgfx_black_conf.h"
#include "hardgfx_black_errno.h"

/**
  * @defgroup DMAGFX_Mode DMAGFX Mode
*/

#define DMAGFX_M2M              DMA2D_M2M               /*!< DMAGFX memory to memory transfer mode */
#define DMAGFX_M2M_PFC          DMA2D_M2M_PFC           /*!< DMAGFX memory to memory with pixel format conversion transfer mode */
#define DMAGFX_M2M_BLEND        DMA2D_M2M_BLEND         /*!< DMAGFX memory to memory with blending transfer mode */
#define DMAGFX_R2M              DMA2D_R2M               /*!< DMAGFX register to memory transfer mode */
#define DMAGFX_M2M_BLEND_FG     DMA2D_M2M_BLEND_FG      /*!< DMAGFX memory to memory with blending transfer mode and fixed color FG */
#define DMAGFX_M2M_BLEND_BG     DMA2D_M2M_BLEND_BG      /*!< DMAGFX memory to memory with blending transfer mode and fixed color BG */

/**
  * @}
  */

/**
  * @defgroup DMAGFX_Output_Color_Mode  DMAGFX output color mode
  * @{
  */

#define DMAGFX_OUTPUT_ARGB8888  DMA2D_OUTPUT_ARGB8888   /*!< ARGB8888 DMAGFX color mode */
#define DMAGFX_OUTPUT_RGB888    DMA2D_OUTPUT_RGB888     /*!< RGB888 DMAGFX color mode   */
#define DMAGFX_OUTPUT_RGB565    DMA2D_OUTPUT_RGB565     /*!< RGB565 DMAGFX color mode   */
#define DMAGFX_OUTPUT_ARGB1555  DMA2D_OUTPUT_ARGB1555   /*!< ARGB1555 DMAGFX color mode */
#define DMAGFX_OUTPUT_ARGB4444  DMA2D_OUTPUT_ARGB4444   /*!< ARGB4444 DMAGFX color mode */

/**
  * @}
  */

/** @defgroup DMAGFX_Input_Color_Mode DMAGFX Input Color Mode
  * @{
  */

#define DMAGFX_INPUT_ARGB8888   DMA2D_INPUT_ARGB8888    /*!< ARGB8888 color mode */
#define DMAGFX_INPUT_RGB888     DMA2D_INPUT_RGB888      /*!< RGB888 color mode   */
#define DMAGFX_INPUT_RGB565     DMA2D_INPUT_RGB565      /*!< RGB565 color mode   */
#define DMAGFX_INPUT_ARGB1555   DMA2D_INPUT_ARGB1555    /*!< ARGB1555 color mode */
#define DMAGFX_INPUT_ARGB4444   DMA2D_INPUT_ARGB4444    /*!< ARGB4444 color mode */
#define DMAGFX_INPUT_L8         DMA2D_INPUT_L8          /*!< L8 color mode       */
#define DMAGFX_INPUT_AL44       DMA2D_INPUT_AL44        /*!< AL44 color mode     */
#define DMAGFX_INPUT_AL88       DMA2D_INPUT_AL88        /*!< AL88 color mode     */
#define DMAGFX_INPUT_L4         DMA2D_INPUT_L4          /*!< L4 color mode       */
#define DMAGFX_INPUT_A8         DMA2D_INPUT_A8          /*!< A8 color mode       */
#define DMAGFX_INPUT_A4         DMA2D_INPUT_A4          /*!< A4 color mode       */
#define DMAGFX_INPUT_YCBCR      DMA2D_INPUT_YCBCR       /*!< YCbCr color mode */

/**
  * @}
  */

/** @defgroup DMAGFX_Alpha_Mode DMAGFX Alpha Mode
  * @{
  */

#define DMAGFX_NO_MODIF_ALPHA   DMA2D_NO_MODIF_ALPHA   /*!< No modification of the alpha channel value */
#define DMAGFX_REPLACE_ALPHA    DMA2D_REPLACE_ALPHA    /*!< Replace original alpha channel value by programmed alpha value */
#define DMAGFX_COMBINE_ALPHA    DMA2D_COMBINE_ALPHA    /*!< Replace original alpha channel value by programmed alpha value with original alpha channel value */

/**
  * @}
  */

/** @defgroup DMAGFX_Alpha_Inverted DMAGFX Alpha Inversion
  * @{
  */

#define DMAGFX_REGULAR_ALPHA    DMA2D_REGULAR_ALPHA     /*!< No modification of the alpha channel value */
#define DMAGFX_INVERTED_ALPHA   DMA2D_INVERTED_ALPHA    /*!< Invert the alpha channel value */

/**
  * @}
  */

/** @defgroup DMAGFX_RB_Swap DMAGFX Red and Blue Swap
  * @{
  */

#define DMAGFX_RB_REGULAR       DMA2D_RB_REGULAR        /*!< Select regular mode (RGB or ARGB) */
#define DMAGFX_RB_SWAP          DMA2D_RB_SWAP           /*!< Select swap mode (BGR or ABGR) */

/**
  * @}
  */

/** @defgroup DMAGFX_Chroma_Sub_Sampling DMAGFX Chroma Sub Sampling
  * @{
  */

#define DMAGFX_NO_CSS           DMA2D_NO_CSS            /*!< No chroma sub-sampling 4:4:4 */
#define DMAGFX_CSS_422          DMA2D_CSS_422           /*!< chroma sub-sampling 4:2:2 */
#define DMAGFX_CSS_420          DMA2D_CSS_420           /*!< chroma sub-sampling 4:2:0 */

/**
  * @}
  */

#define HARDGFX_DMAGFX_FOREGROUND_LAYER     1UL
#define HARDGFX_DMAGFX_BACKGROUND_LAYER     0UL

typedef struct {
    uint32_t mode;
    uint32_t outputColor;
    uint32_t outputOffset;
    uint32_t inputColor[2];
    uint8_t  alphaMode[2];
    uint8_t  inputAlpha[2];
    uint32_t inputOffset[2];
    uint32_t alphaInverted[2];
    uint32_t redBlueSwap[2];
    uint32_t chromaSubSampling;
}HardGFX_DMAGFX_Parameters_t;

typedef DMA2D_HandleTypeDef HardGFX_DMAGFX_HandleTypeDef;

extern HardGFX_DMAGFX_HandleTypeDef dmagfxHandle;

/* API used to configure the DMA graphic peripheral */
void HardGFX_DMAGFX_GPIO_Init(HardGFX_DMAGFX_HandleTypeDef* dmagfxHandle);
void HardGFX_DMAGFX_GPIO_DeInit(HardGFX_DMAGFX_HandleTypeDef* dmagfxHandle);
int32_t HardGFX_DMAGFX_Init(const HardGFX_DMAGFX_Parameters_t* parameters);

#ifdef __cplusplus
}
#endif

#endif /* INC_HARDGFX_BLACK_DMAGFX_H_ */
