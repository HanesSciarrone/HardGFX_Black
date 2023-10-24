/*
 * mt48lc4m32b2.h
 *
 *  Created on: Feb 17, 2023
 *      Author: hanes
 */

#ifndef COMPONENTS_INC_MT48LC4M32B2_H_
#define COMPONENTS_INC_MT48LC4M32B2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"


#define SDRAM_OK                            0
#define SDRAM_ERROR                         -1



/*  Refresh Count is calculate how:
 *
 *                       tREF (SDRAM datasheet)
 * Refresh count = ( ------------------------------ * (Clk SDRAM) ) - 20
 *                    Row number (SDRAM datasheet)
 *
 *  For this case:
 *
 *                    64ms
 *  Refresh count = -------- * 100Mhz - 20 = 1542
 *                    4096
 */
#define SDRAM_REFRESH_COUNT                 (uint32_t)0x0606
#define SDRAM_TIMEOUT                       (uint32_t)0xFFFF

/*  Register mode -------------------------- */
#define SDRAM_BURST_LENGTH_1                0x00000000U
#define SDRAM_BURST_LENGTH_2                0x00000001U
#define SDRAM_BURST_LENGTH_4                0x00000002U
#define SDRAM_BURST_LENGTH_8                0x00000004U

#define SDRAM_BURST_TYPE_SEQUENTIAL         0x00000000U
#define SDRAM_BURST_TYPE_INTERLEAVED        0x00000008U

#define SDRAM_CAS_LATENCY_2                 0x00000020U
#define SDRAM_CAS_LATENCY_3                 0x00000030U

#define SDRAM_OPERATING_MODE_STANDARD       0x00000000U

#define SDRAM_WRITEBURST_MODE_PROGRAMMED    0x00000000U
#define SDRAM_WRITEBURST_MODE_SINGLE        0x00000200U
/* ------------------------------------------------------------------- */

/* -------------------------- Command Mode --------------------------- */
// See Reference Manual 0399 page 919/920
#define SDRAM_NORMAL_MODE_CMD               0x00000000U
#define SDRAM_CLK_ENABLE_CMD                0x00000001U
#define SDRAM_PALL_CMD                      0x00000002U
#define SDRAM_AUTOREFRESH_MODE_CMD          0x00000003U
#define SDRAM_LOAD_MODE_CMD                 0x00000004U
#define SDRAM_SELFREFRESH_MODE_CMD          0x00000005U
#define SDRAM_POWERDOWN_MODE_CMD            0x00000006U
/* ------------------------------------------------------------------- */


typedef struct
{
    uint32_t targetBank;           // Target Bank
    uint32_t refreshMode;          // Refresh Mode
    uint32_t refreshRate;          // Refresh Rate
    uint32_t burstLength;          // Burst Length
    uint32_t burstType;            // Burst Type
    uint32_t casLatency;           // CAS Latency
    uint32_t operationMode;        // Operation Mode
    uint32_t writeBurstMode;       // Write Burst Mode
}SDRAM_Context_t;


int32_t SDRAM_Init(SDRAM_HandleTypeDef *hsdram, SDRAM_Context_t *regMode);
int32_t SDRAM_ClockEnable(SDRAM_HandleTypeDef *hsdram, uint32_t interface);
int32_t SDRAM_Precharge(SDRAM_HandleTypeDef *hsdram, uint32_t interface);
int32_t SDRAM_ModeRegConfig(SDRAM_HandleTypeDef *hsdram, SDRAM_Context_t *regMode);
int32_t SDRAM_TimingConfig(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_TimingTypeDef *timing);
int32_t SDRAM_RefreshMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface, uint32_t refreshMode);
int32_t SDRAM_RefreshRate(SDRAM_HandleTypeDef *hsdram, uint32_t refreshCount);
int32_t SDRAM_EnterPowerMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface);
int32_t SDRAM_ExitPowerMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface);
int32_t SDRAM_Sendcmd(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *sdramCommand);

#ifdef __cplusplus
}
#endif

#endif /* COMPONENTS_INC_MT48LC4M32B2_H_ */
