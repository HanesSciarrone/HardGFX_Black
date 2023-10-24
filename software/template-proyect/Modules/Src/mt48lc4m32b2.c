/*
 * mt48lc4m32b2.c
 *
 *  Created on: Feb 17, 2023
 *      Author: hanes
 */

#include "mt48lc4m32b2.h"


static FMC_SDRAM_CommandTypeDef command;

/* ------------------------------------- Private functions declaration ------------------------------------- */
static int32_t SDRAM_Delay(uint32_t delay);
/* --------------------------------------------------------------------------------------------------------- */


/* ------------------------------------ Public functions implementation ------------------------------------ */
/**
  * @brief  Initializes the SDRAM memory.
  *
  * @param  hsdram Component object pointer
  * @param  regMode Pointer to register mode structure
  *
  * @retval error status
  */
int32_t SDRAM_Init(SDRAM_HandleTypeDef *hsdram, SDRAM_Context_t *regMode)
{
    int32_t errno = SDRAM_ERROR;

    /* Step 1: Configure a clock configuration enable command */
    if(SDRAM_ClockEnable(hsdram, regMode->targetBank) == SDRAM_OK)
    {
        /* Step 2: Insert 100us minimum delay,
         * Inserted delay is equal to 1 ms due to systick time base unit (ms)
         */
        SDRAM_Delay(1);

        /* Step 3: Configure precharge all command */
        if(SDRAM_Precharge(hsdram, regMode->targetBank) == SDRAM_OK)
        {
            /* Step 4: Configure a refresh command */
            if(SDRAM_RefreshMode(hsdram, regMode->targetBank, regMode->refreshMode) == SDRAM_OK)
            {
                /* Step 5: Program the external memory mode register */
                if(SDRAM_ModeRegConfig(hsdram, regMode) == SDRAM_OK)
                {
                    /* Step 6: Set the refresh rate counter */
                    if(SDRAM_RefreshRate(hsdram, regMode->refreshRate) == SDRAM_OK)
                    {
                        errno = SDRAM_OK;
                    }
                }
            }
        }
    }

    return errno;
}

/**
  * @brief  Enable SDRAM clock
  *
  * @param  hsdram Component object pointer
  * @param  interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  *
  * @retval error status
  */
int32_t SDRAM_ClockEnable(SDRAM_HandleTypeDef *hsdram, uint32_t interface)
{
    command.CommandMode            = SDRAM_CLK_ENABLE_CMD;
    command.CommandTarget          = interface;
    command.AutoRefreshNumber      = 1;
    command.ModeRegisterDefinition = 0;

    /* Send the command */
    if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
    {
        return SDRAM_ERROR;
    }
    else
    {
        return SDRAM_OK;
    }
}

/**
  * @brief  Precharge all sdram banks
  *
  * @param  hsdram Component object pointer
  * @param  interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  *
  * @retval error status
  */
int32_t SDRAM_Precharge(SDRAM_HandleTypeDef *hsdram, uint32_t interface)
{
    command.CommandMode            = SDRAM_PALL_CMD;
    command.CommandTarget          = interface;
    command.AutoRefreshNumber      = 1;
    command.ModeRegisterDefinition = 0;

    /* Send the command */
    if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
    {
        return SDRAM_ERROR;
    }
    else
    {
        return SDRAM_OK;
    }
}

/**
  * @brief  Program the external memory mode register
  *
  * @param  hsdram Component object pointer
  * @param  regMode Pointer to Register Mode stucture
  *
  * @retval error status
  */
int32_t SDRAM_ModeRegConfig(SDRAM_HandleTypeDef *hsdram, SDRAM_Context_t *regMode)
{
    uint32_t tmpmrd;

    /* Program the external memory mode register */
    tmpmrd = (uint32_t)regMode->burstLength | regMode->burstType | regMode->casLatency | regMode->operationMode | regMode->writeBurstMode;

    command.CommandMode            = SDRAM_LOAD_MODE_CMD;
    command.CommandTarget          = regMode->targetBank;
    command.AutoRefreshNumber      = 1;
    command.ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
    {
        return SDRAM_ERROR;
    }
    else
    {
        return SDRAM_OK;
    }
}

/**
  * @brief  Program the SDRAM timing
  *
  * @param  hsdram Component object pointer
  * @param  timing Pointer to SDRAM timing configuration structure
  *
  * @retval error status
  */
int32_t SDRAM_TimingConfig(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_TimingTypeDef *timing)
{
    /* Program the SDRAM timing */
    if(HAL_SDRAM_Init(hsdram, timing) != HAL_OK)
    {
        return SDRAM_ERROR;
    }
    else
    {
        return SDRAM_OK;
    }
}

/**
  * @brief  Configure Refresh mode
  *
  * @param  hsdram Component object pointer
  * @param  interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  * @param  refreshMode Could be SDRAM_CMD_AUTOREFRESH_MODE or
  *                      SDRAM_CMD_SELFREFRESH_MODE
  *
  * @retval error status
  */
int32_t SDRAM_RefreshMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface, uint32_t refreshMode)
{
  command.CommandMode            = refreshMode;
  command.CommandTarget          = interface;
  command.AutoRefreshNumber      = 8;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Set the device refresh rate
  *
  * @param  hsdram Component object pointer
  * @param  refreshCount The refresh rate to be programmed
  *
  * @retval error status
  */
int32_t SDRAM_RefreshRate(SDRAM_HandleTypeDef *hsdram, uint32_t refreshCount)
{
  /* Set the device refresh rate */
  if(HAL_SDRAM_ProgramRefreshRate(hsdram, refreshCount) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Enter Power mode
  *
  * @param  hsdram Component object pointer
  * @param  interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  *
  * @retval error status
  */
int32_t SDRAM_EnterPowerMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface)
{
  command.CommandMode            = SDRAM_POWERDOWN_MODE_CMD;
  command.CommandTarget          = interface;
  command.AutoRefreshNumber      = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Exit Power mode
  *
  * @param  hsdram Component object pointer
  * @param  interface Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  *
  * @retval error status
  */
int32_t SDRAM_ExitPowerMode(SDRAM_HandleTypeDef *hsdram, uint32_t interface)
{
  command.CommandMode            = SDRAM_NORMAL_MODE_CMD;
  command.CommandTarget          = interface;
  command.AutoRefreshNumber      = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}

/**
  * @brief  Sends command to the SDRAM bank.
  *
  * @param  hsdram Component object pointer
  * @param  sdramCommand Pointer to SDRAM command structure.
  *
  * @retval SDRAM status
  */
int32_t SDRAM_Sendcmd(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *sdramCommand)
{
  if(HAL_SDRAM_SendCommand(hsdram, sdramCommand, SDRAM_TIMEOUT) != HAL_OK)
  {
    return SDRAM_ERROR;
  }
  else
  {
    return SDRAM_OK;
  }
}
/* --------------------------------------------------------------------------------------------------------- */


/**
  * @brief Provides accurate delay in milliseconds
  *
  * @param delay Specifies the delay in milliseconds
  *
  * @retval SDRAM_OK
  */
static int32_t SDRAM_Delay(uint32_t Delay)
{
  uint32_t tickstart;

  tickstart = HAL_GetTick();

  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
  return SDRAM_OK;
}

