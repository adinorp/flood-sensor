/*
 * Ic2.c
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#include "Ic2.h"

bool I2C_waiter()
{
  int32_t i;

  i = 1000;
  while (HAL_I2C_GetState(Get_I2cHandle()) != HAL_I2C_STATE_READY)
  {
	 //TODO Add micro second timer delays
    //DWT_Delay_us(I2C_WAIT_READY_TIMEOUT_uS);
    if (i-- == 0)
    {
      return false;
    }
  }

  return true;
}



bool I2C_Write(I2C_HandleTypeDef *i2cBus, uint8_t dev_address, uint8_t *data,
               uint16_t size)
{
  HAL_StatusTypeDef status;

  status  = HAL_I2C_Master_Transmit(Get_I2cHandle(), dev_address, data,
                                    size, I2C_TIMEOUT);
  if (status == HAL_OK)
  {
    //return WAIT_condition(I2C_state_checker, NULL, true, I2C_WAIIT_READY_TIMEOUT);
    return I2C_waiter();
  }
  else
  {
    return false;
  }
}

bool I2C_Read(I2C_HandleTypeDef *i2cBus, uint8_t dev_address, uint8_t *data,
              uint16_t size)
{
  HAL_StatusTypeDef status;
  status  = HAL_I2C_Master_Receive(Get_I2cHandle(), dev_address, data,
                                   size, I2C_TIMEOUT);
  if (status == HAL_OK)
  {
    return I2C_waiter();
  }
  else
  {
    return false;
  }
}

bool I2C_Mem_WriteReg(uint8_t dev_address, uint8_t reg_address, uint8_t *data,
                      uint16_t size)
{
  HAL_StatusTypeDef status;

  status  = HAL_I2C_Mem_Write(Get_I2cHandle(), dev_address, reg_address, 1, data,
                              size, I2C_TIMEOUT);
  if (status == HAL_OK)
  {
    //return WAIT_condition(I2C_state_checker, NULL, true, I2C_WAIIT_READY_TIMEOUT);
    return I2C_waiter();
  }
  else
  {
    return false;
  }
}

bool I2C_Mem_ReadReg(uint8_t dev_address, uint8_t reg_address, uint8_t *data, uint16_t size)
{
  HAL_StatusTypeDef status;

  status  = HAL_I2C_Mem_Read(Get_I2cHandle(), dev_address, reg_address, 1, data,
                             size, I2C_TIMEOUT);
  if (status == HAL_OK)
  {
    //return WAIT_condition(I2C_state_checker, NULL, true, I2C_WAIIT_READY_TIMEOUT);
    return I2C_waiter();
  }
  else
  {
    return false;
  }
}

void I2C_ReverseWord(uint8_t* word)
{
  uint8_t temp = word[0];
  word[0] = word[1];
  word[1] = temp;
}

bool I2C_PresenceCheck_OneByteRegAddr(I2C_HandleTypeDef *i2cBus, uint8_t dev_address)
{
    bool devicePresent = false;

    if (HAL_I2C_IsDeviceReady(Get_I2cHandle(), dev_address,
                              I2C_PRESENCE_TRIALS, I2C_TIMEOUT) == HAL_OK)
    {
        devicePresent = true;
    }

    return devicePresent;
}
