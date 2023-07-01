/*
 * Spi.c
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#include "Spi.h"


bool Spi1_Transmit(uint8_t *buff, uint16_t size)
{
  bool status = false;
  if(HAL_SPI_Transmit(Get_SpiHandle(), buff, size, SPI_TIMEOUT) == HAL_OK)
  {
    status  = true;
  }
  return status;
}


bool Spi1_Receive(uint8_t *buff, uint16_t size)
{
  bool status = false;
  if(HAL_SPI_Receive(Get_SpiHandle(), buff, size, SPI_TIMEOUT) == HAL_OK)
  {
    status = true;
  }

  return status;
}

bool Spi1_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
	bool status = false;
	if(HAL_SPI_TransmitReceive (Get_SpiHandle(), pTxData, pRxData, Size, SPI_TIMEOUT) == HAL_OK)
	{
	   status = true;
	}
	return status;
}


bool SPI_WriteByte(SPI_HandleTypeDef *spiHandle, uint8_t command)
{
  bool writeComplete = false;

  if(HAL_SPI_Transmit(spiHandle, &command, SPI_1_BYTE, SPI_TIMEOUT) == HAL_OK)
  {
    writeComplete  = true;
  }
  else
  {
    Error_Spi();
  }
  return writeComplete;
}



bool SPI_WriteByte_OneByteAddr(SPI_HandleTypeDef *spiHandle, uint8_t reg, uint8_t data)
{
  bool writeComplete = false;
  uint8_t writeBuffer[SPI_2_BYTE] = {0,0};

  writeBuffer[SPI_DATA_0] = reg;
  writeBuffer[SPI_DATA_1] = data;

  if(HAL_SPI_Transmit(spiHandle, writeBuffer, SPI_2_BYTE, SPI_TIMEOUT) == HAL_OK)
  {
    writeComplete  = true;
  }
  else
  {
    Error_Spi();
  }
  return writeComplete;
}

/*
*/
uint8_t SPI_ReadByte(SPI_HandleTypeDef *spiHandle)
{
  uint8_t result = 0;

  if(HAL_SPI_Receive(spiHandle, &result, SPI_1_BYTE, SPI_TIMEOUT) == HAL_OK)
  {
    rTosDelay(1);
  }
  else
  {
    Error_Spi();
  }

  return result;
}

/*
*
*/
uint8_t SPI_ReadByte_OneByteAddr(SPI_HandleTypeDef *spiHandle, uint8_t reg)
{
  uint8_t result = 0;

  if(HAL_SPI_Transmit(spiHandle, &reg, SPI_1_BYTE, SPI_TIMEOUT) == HAL_OK)
  {
    if(HAL_SPI_Receive(spiHandle, &result, SPI_1_BYTE, SPI_TIMEOUT) == HAL_OK)
    {
      rTosDelay(1);
    }
  }
  else
  {
    Error_Spi();
  }

  return result;
}

bool SPI_WriteArray(SPI_HandleTypeDef *spiHandle, uint8_t *data, uint16_t size)
{
  bool writeComplete = false;

  if(HAL_SPI_Transmit(spiHandle, data, size, SPI_TIMEOUT) == HAL_OK)
  {
    writeComplete  = true;
  }
  else
  {
    Error_Spi();
  }
  return writeComplete;
}

bool SPI_ReadArray(SPI_HandleTypeDef *spiHandle, uint8_t *result, uint16_t size)
{
  bool readComplete = false;

  if(HAL_SPI_Receive(spiHandle, result, size, SPI_TIMEOUT) == HAL_OK)
  {
    readComplete  = true;
  }
  else
  {
    Error_Spi();
  }
  return readComplete;
}

void Error_Spi(void)
{

}
