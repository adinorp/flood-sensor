/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S2;
    PeriphClkInitStruct.I2s2ClockSelection = RCC_I2S2CLKSOURCE_HSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PB14     ------> SPI2_MISO
    PA10     ------> SPI2_MOSI
    PB13     ------> SPI2_SCK
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**SPI2 GPIO Configuration
    PB14     ------> SPI2_MISO
    PA10     ------> SPI2_MOSI
    PB13     ------> SPI2_SCK
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14|GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Spi1_AssertCs(void)
{
	//Assert SPI1_NSS pin
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);
}

void Spi1_DeassertCs(void)
{
	//Deassert SPI1_NSS pin
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);
}

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
    HAL_Delay(1);
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
    	HAL_Delay(1);
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

/* USER CODE END 1 */
