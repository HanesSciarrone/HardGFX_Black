#include <string.h>

#include "main.h"
#include "hardgfx_rcc.h"
#include "hardgfx_black_sdram.h"

/* ------------------------- Private define ------------------------ */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) // HW semaphore 0
#endif
/* ----------------------------------------------------------------- */

/* ------------------------- Private macro ------------------------- */
#define BUFFER_SIZE            ((uint32_t)0x200)
#define BUFFER_SIZE_IN_BYTES   BUFFER_SIZE*4
#define WRITE_READ_ADDR        ((uint32_t)0x00000000)
/* ----------------------------------------------------------------- */

/* ----------------------- Private variables ----------------------- */
ALIGN_32BYTES(uint32_t txBuffer[BUFFER_SIZE]);
ALIGN_32BYTES(uint32_t rxBuffer[BUFFER_SIZE]);
/* ----------------------------------------------------------------- */

/* ------------------ Private function prototypes ------------------ */
static void MPU_Config(void);
static void HardGFX_CPU_Cache_Enable(void);
static void HardGFX_Fill_Buffer(uint32_t *buffer, uint32_t lenght, uint32_t offset);
static uint8_t HardGFX_Compare_Buffer(uint32_t* buffer1, uint32_t* buffer2, uint16_t length);
static uint32_t HardGFX_SDRAM_Demo(void);
static uint32_t HardGFX_SDRAM_DMA_Demo(void);
/* ----------------------------------------------------------------- */

int main(void)
{
    uint32_t errno = HAL_OK;
    int32_t timeout = 0xFFFF;

    // MPU Configuration
    MPU_Config();

    HardGFX_CPU_Cache_Enable();

    // Wait until CPU2 boots and enters in stop mode or timeout
    while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));

    if ( timeout < 0 )
    {
        Error_Handler();
    }
    // MCU Configuration

    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();

    // Configure Clock CPU
    HardGFX_SystemClock_Configure();

    /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of HSEM notification */

    // HW semaphore Clock enable
    __HAL_RCC_HSEM_CLK_ENABLE();
    // Take HSEM
    HAL_HSEM_FastTake(HSEM_ID_0);
    // Release HSEM in order to notify the CPU2(CM4)
    HAL_HSEM_Release(HSEM_ID_0,0);
    // wait until CPU2 wakes up from stop mode
    timeout = 0xFFFF;

    while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));

    if ( timeout < 0 )
    {
        Error_Handler();
    }

    /* Initialize all configured peripherals */
    HardGFX_RCC_GPIO_Init();

    if (HardGFX_SDRAM_Periphreal() != HARDGFX_NONE_ERROR)
    {
        Error_Handler();
    }

    /* Testing write/read SDRAM with and without DMA */
    errno = HardGFX_SDRAM_Demo();

    if (errno != HAL_OK)
    {
        Error_Handler();
    }

    memset(txBuffer, 0, sizeof(txBuffer));
    memset(rxBuffer, 0, sizeof(rxBuffer));

    errno = HardGFX_SDRAM_DMA_Demo();

    if (errno != HAL_OK)
    {
        Error_Handler();
    }

    while (1)
    {
    }

    return 0;
}

static void HardGFX_CPU_Cache_Enable(void)
{
    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();
}

/**
  * @brief  Fills buffer with user predefined data.
  *
  * @param  buffer Pointer on the buffer to fill
  * @param  lenght size of the buffer to fill
  * @param  offset First value to fill on the buffer
  */
static void HardGFX_Fill_Buffer(uint32_t *buffer, uint32_t lenght, uint32_t offset)
{
    uint32_t index = 0;

    /* Put in global buffer different values */
    for (index = 0; index < lenght; index++ )
    {
        buffer[index] = index + offset;
    }
}

/**
  * @brief  Compares two buffers.
  *
  * @param  buffer1, buffer2 Buffers to be compared.
  * @param  length: Buffer's length
  *
  * @retval 0: buffer1 identical to buffer2
  *         3: buffer1 differs from buffer2
  */
static uint8_t HardGFX_Compare_Buffer(uint32_t* buffer1, uint32_t* buffer2, uint16_t length)
{
    uint32_t index = 0;

    for (index = 0; index < length; index++)
    {
        if (buffer1[index] != buffer2[index])
        {
          return 3;
        }
    }

    return 0;
}


static uint32_t HardGFX_SDRAM_Demo(void)
{
    HAL_StatusTypeDef errno = HAL_OK;

    HardGFX_Fill_Buffer(txBuffer, BUFFER_SIZE, 0x0000);
    errno = HAL_SDRAM_Write_32b(&hsdram, (uint32_t *)(HARDGFX_SDRAM_ADDRESS + WRITE_READ_ADDR), txBuffer, BUFFER_SIZE);

    if (errno != HAL_OK)
    {
        return errno;
    }

    errno = HAL_SDRAM_Read_32b(&hsdram, (uint32_t *)(HARDGFX_SDRAM_ADDRESS + WRITE_READ_ADDR), rxBuffer, BUFFER_SIZE);

    if (errno != HAL_OK)
    {
        return errno;
    }

    return HardGFX_Compare_Buffer(txBuffer, rxBuffer, BUFFER_SIZE);
}

static uint32_t HardGFX_SDRAM_DMA_Demo(void)
{
    HAL_StatusTypeDef errno = HAL_OK;

    HardGFX_Fill_Buffer(txBuffer, BUFFER_SIZE, 0xFFFF);

    /* Clean Data Cache to update the content of the SRAM */
    SCB_CleanDCache_by_Addr(txBuffer, BUFFER_SIZE_IN_BYTES);
    errno = HAL_SDRAM_Write_DMA(&hsdram, (uint32_t *)(HARDGFX_SDRAM_ADDRESS + WRITE_READ_ADDR), txBuffer, BUFFER_SIZE);

    if (errno != HAL_OK)
    {
        return errno;
    }

    // Delay to avoid the busy state in the SDRAM interface when reading the data
    HAL_Delay(1);
    errno = HAL_SDRAM_Read_DMA(&hsdram, (uint32_t *)(HARDGFX_SDRAM_ADDRESS + WRITE_READ_ADDR), rxBuffer, BUFFER_SIZE);

    if (errno != HAL_OK)
    {
        return errno;
    }

    /* Invalidate Data Cache to get the updated content of the SRAM*/
    // Delay to obtain all data and avoid reading breakage.
    HAL_Delay(1);
    SCB_InvalidateDCache_by_Addr(rxBuffer, BUFFER_SIZE_IN_BYTES);

    return HardGFX_Compare_Buffer(txBuffer, rxBuffer, BUFFER_SIZE);
}

/* MPU Configuration */
void MPU_Config(void)
{
    MPU_Region_InitTypeDef mpuInit = {0};

    /* Disables the MPU */
    HAL_MPU_Disable();

    /* Initializes and configures the Region and the memory to be protected */
    mpuInit.Enable = MPU_REGION_ENABLE;
    mpuInit.Number = MPU_REGION_NUMBER0;
    mpuInit.BaseAddress = 0x0;
    mpuInit.Size = MPU_REGION_SIZE_4GB;
    mpuInit.SubRegionDisable = 0x87;
    mpuInit.TypeExtField = MPU_TEX_LEVEL0;
    mpuInit.AccessPermission = MPU_REGION_NO_ACCESS;
    mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpuInit.IsShareable = MPU_ACCESS_SHAREABLE;
    mpuInit.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpuInit.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&mpuInit);

    /* Initializes and configures the Region and the memory to be protected */
    mpuInit.Number = MPU_REGION_NUMBER1;
    mpuInit.BaseAddress = 0xD0000000;
    mpuInit.Size = MPU_REGION_SIZE_32MB;
    mpuInit.SubRegionDisable = 0x0;
    mpuInit.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpuInit.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpuInit.IsCacheable = MPU_ACCESS_CACHEABLE;

    HAL_MPU_ConfigRegion(&mpuInit);
    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
