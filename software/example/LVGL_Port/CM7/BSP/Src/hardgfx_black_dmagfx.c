#include "hardgfx_black_dmagfx.h"

/* --------------------------------------------- Private macros -------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------- Private variables ------------------------------------------- */
HardGFX_DMAGFX_HandleTypeDef dmagfxHandle = { 0 };
/* --------------------------------------------------------------------------------------------------------- */

/* ------------------------------------ Public functions implementation ------------------------------------ */
void HardGFX_DMAGFX_GPIO_Init(HardGFX_DMAGFX_HandleTypeDef* dmagfxHandle)
{
    if (dmagfxHandle->Instance == DMA2D)
    {
        /** Enable the DMA2D clock */
        __HAL_RCC_DMA2D_CLK_ENABLE();

        /** Toggle Sw reset of DMA2D IP */
        __HAL_RCC_DMA2D_FORCE_RESET();
        __HAL_RCC_DMA2D_RELEASE_RESET();
    }
}

void HardGFX_DMAGFX_GPIO_DeInit(HardGFX_DMAGFX_HandleTypeDef* dmagfxHandle)
{
    if (dmagfxHandle->Instance == DMA2D)
    {
        /** Disable IRQ of DMA2D IP */
        HAL_NVIC_DisableIRQ(DMA2D_IRQn);

        /** Force and let in reset state DMA2D */
        __HAL_RCC_DMA2D_FORCE_RESET();

        /** Disable the DMA2D */
        __HAL_RCC_DMA2D_CLK_DISABLE();
    }
}

int32_t HardGFX_DMAGFX_Init(const HardGFX_DMAGFX_Parameters_t* parameters)
{
    int32_t retVal = HARDGFX_NONE_ERROR;

    dmagfxHandle.Instance = DMA2D;
    dmagfxHandle.Init.Mode = parameters->mode;
    dmagfxHandle.Init.ColorMode = parameters->outputColor;
    dmagfxHandle.Init.OutputOffset = parameters->outputOffset;

    switch (parameters->mode)
    {
        case DMAGFX_M2M:
        case DMAGFX_M2M_PFC:
        {
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputOffset = parameters->inputOffset[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputColorMode = parameters->inputColor[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaMode = parameters->alphaMode[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputAlpha = parameters->inputAlpha[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaInverted = parameters->alphaInverted[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].RedBlueSwap = parameters->redBlueSwap[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].ChromaSubSampling = parameters->chromaSubSampling;
        }
        break;

        case DMAGFX_M2M_BLEND:
        {
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputOffset = parameters->inputOffset[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputColorMode = parameters->inputColor[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].AlphaMode = parameters->alphaMode[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputAlpha = parameters->inputAlpha[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].AlphaInverted = parameters->alphaInverted[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].RedBlueSwap = parameters->redBlueSwap[HARDGFX_DMAGFX_BACKGROUND_LAYER];

            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputOffset = parameters->inputOffset[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputColorMode = parameters->inputColor[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaMode = parameters->alphaMode[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputAlpha = parameters->inputAlpha[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaInverted = parameters->alphaInverted[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].RedBlueSwap = parameters->redBlueSwap[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].ChromaSubSampling = parameters->chromaSubSampling;
        }
        break;

        case DMAGFX_M2M_BLEND_FG:
        case DMAGFX_M2M_BLEND_BG:
        {
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputOffset = parameters->inputOffset[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputColorMode = parameters->inputColor[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].AlphaMode = parameters->alphaMode[HARDGFX_DMAGFX_BACKGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_BACKGROUND_LAYER].InputAlpha = parameters->inputAlpha[HARDGFX_DMAGFX_BACKGROUND_LAYER];

            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputOffset = parameters->inputOffset[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputColorMode = parameters->inputColor[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaMode = parameters->alphaMode[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].InputAlpha = parameters->inputAlpha[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].AlphaInverted = parameters->alphaInverted[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].RedBlueSwap = parameters->redBlueSwap[HARDGFX_DMAGFX_FOREGROUND_LAYER];
            dmagfxHandle.LayerCfg[HARDGFX_DMAGFX_FOREGROUND_LAYER].ChromaSubSampling = parameters->chromaSubSampling;
        }
        break;

        default:
        {
        }

    }

    if (HAL_DMA2D_Init(&dmagfxHandle) != HAL_OK)
    {
        retVal = HARDGFX_DMAGFX_INITIALIZATION_FAIL;
    }

    return retVal;
}
/* --------------------------------------------------------------------------------------------------------- */
