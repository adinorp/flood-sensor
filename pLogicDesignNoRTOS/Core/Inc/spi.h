/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */
#define SPI_1_BYTE	1
#define SPI_2_BYTE	2
#define SPI_TIMEOUT 100u

#define SPI_DATA_0      0
#define SPI_DATA_1      1
/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */
void Spi1_AssertCs(void);
void Spi1_DeassertCs(void);

bool Spi1_Transmit(uint8_t *buff, uint16_t size);
bool Spi1_Receive(uint8_t *buff, uint16_t size);
bool Spi1_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
bool SPI_WriteByte(SPI_HandleTypeDef *spiHandle, uint8_t value);
bool SPI_WriteByte_OneByteAddr(SPI_HandleTypeDef *spiHandle, uint8_t reg, uint8_t data);
uint8_t SPI_ReadByte(SPI_HandleTypeDef *spiHandle);
uint8_t SPI_ReadByte_OneByteAddr(SPI_HandleTypeDef *spiHandle, uint8_t reg);
bool SPI_ReadArray(SPI_HandleTypeDef *spiHandle, uint8_t *buff, uint16_t size);
bool SPI_WriteArray(SPI_HandleTypeDef *spiHandle, uint8_t *data, uint16_t size);
bool Spi_Transmit(SPI_HandleTypeDef *spiHandle, uint8_t *buff, uint16_t size);
bool Spi_Receive(SPI_HandleTypeDef *spiHandle, uint8_t *buff, uint16_t size);
void Error_Spi(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

