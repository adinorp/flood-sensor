/*
 * Ic2.h
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#ifndef IC2_H_
#define IC2_H_

#include "main.h"
#include <stdbool.h>

#define I2C_WAIT_READY_TIMEOUT_uS 10 /* in microseconds */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define I2C_TIMEOUT 			100
#define I2C_PRESENCE_TRIALS	        3

#define I2C_1_BYTE	1
#define I2C_2_BYTE	2
#define I2C_3_BYTE      3

#define I2C_DATA_POS_0	0
#define I2C_DATA_POS_1	1
#define I2C_DATA_POS_2	2

#define BIT_SHIFT_7     7
#define BIT_SHIFT_8     8


bool I2C_waiter();
bool I2C_Write(I2C_HandleTypeDef *i2cBus, uint8_t dev_address, uint8_t *data,
               uint16_t size);
bool I2C_Read(I2C_HandleTypeDef *i2cBus, uint8_t dev_address, uint8_t *data,
              uint16_t size);
bool I2C_Mem_WriteReg(uint8_t dev_address, uint8_t reg_address, uint8_t *data,
                      uint16_t size);
bool I2C_Mem_ReadReg(uint8_t dev_address, uint8_t reg_address, uint8_t *data,
                     uint16_t size);
void I2C_ReverseWord(uint8_t* word);
bool I2C_PresenceCheck_OneByteRegAddr(I2C_HandleTypeDef *i2cBus, uint8_t dev_address);

#endif /* IC2_H_ */
