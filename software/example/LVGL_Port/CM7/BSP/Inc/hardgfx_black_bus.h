/*
 * hardgfx_black_bus.h
 *
 *  Created on: May 30, 2023
 *      Author: hanes
 */

#ifndef INC_HARDGFX_BLACK_BUS_H_
#define INC_HARDGFX_BLACK_BUS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hardgfx_black_conf.h"
#include "hardgfx_black_errno.h"

#define BUS_I2C                                 I2C4
#define BUS_I2C_CLK_ENABLE()                    __HAL_RCC_I2C4_CLK_ENABLE()
#define BUS_I2C_CLK_DISABLE()                   __HAL_RCC_I2C4_CLK_DISABLE()
#define BUS_I2C_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()

#define BUS_I2C_SCL_PIN                         GPIO_PIN_12
#define BUS_I2C_SDA_PIN                         GPIO_PIN_13
#define BUS_I2C_SCL_GPIO_PORT                   GPIOD
#define BUS_I2C_SDA_GPIO_PORT                   GPIOD

#define BUS_I2C_FREQUENCY                       100000U // I2C frequency of touch screen in Hz (To be edited according to the desired frequency)
#define BUS_I2C_TIME_RISE                       250U /* ns */
#define BUS_I2C_TIME_FALL                       100U /* ns */
#define BUS_I2C_DIGITAL_FILTER_COEFICIENTE      0U

typedef I2C_HandleTypeDef  HardGFXBusHandlerTypeDef;

int32_t HardGFXBusInit(void);
int32_t HardGFXBusDeInit(void);
int32_t HardGFXBusWriteRegister(const uint16_t deviceAddress, const uint16_t registerAddress, const uint8_t *data, const uint16_t length);
int32_t HardGFXBusReadRegister(const uint16_t deviceAddress, const uint16_t registerAddress, uint8_t *data, const uint16_t length);
uint32_t HardGFXBusGetTick(void);
int32_t HardGFXBusIsReady(const uint16_t deviceAddress, uint32_t retries);

#ifdef __cplusplus
}
#endif

#endif /* INC_HARDGFX_BLACK_BUS_H_ */
