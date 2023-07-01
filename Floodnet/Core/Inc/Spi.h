/*
 * Spi.h
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"

#define SPI_1_BYTE	1
#define SPI_2_BYTE	2
#define SPI_TIMEOUT 100u

#define SPI_DATA_0      0
#define SPI_DATA_1      1

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

#endif /* SPI_H_ */
