/*
 * hardgfx_black_sdram.h
 *
 *  Created on: Feb 17, 2023
 *      Author: hanes
 */

#ifndef INC_HARDGFX_BLACK_SDRAM_H_
#define INC_HARDGFX_BLACK_SDRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hardgfx_black_conf.h"
#include "hardgfx_black_errno.h"
#include "mt48lc4m32b2.h"

#define HARDGFX_SDRAM_ADDRESS       0xD0000000U
#define HARDGFX_SDRAM_DEVICE_SIZE   0x00200000U

#define HARDGFX_MDMAx_CHANNEL       MDMA_Channel0
#define HARDGFX_MDMDx_IRQn          MDMA_IRQn

typedef SDRAM_HandleTypeDef HardGFX_SDRAM_HandleTypeDef;

extern HardGFX_SDRAM_HandleTypeDef hsdram;

/* -------------------------------------- Public functions declaration ------------------------------------- */
int32_t HardGFX_SDRAM_Periphreal(void);
int32_t HardGFX_SDRAM_Init(void);
int32_t HardGFX_SDRAM_DeInit(void);
int32_t HardGFX_SDRAM_GPIO_Init(void);
void HardGFX_SDRAM_GPIO_DeInit(void);
void HardGFX_MDMA_IRQHandler(void);
/* --------------------------------------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* INC_HARDGFX_BLACK_SDRAM_H_ */
