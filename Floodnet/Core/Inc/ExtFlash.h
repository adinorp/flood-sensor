/*
 * ExtFlash.h
 *
 *  Created on: May 8, 2023
 *      Author: adinor
 */

#ifndef EXTFLASH_H_
#define EXTFLASH_H_

#include <stdint.h>
#include "stdbool.h"
#include "Spi.h"


#define CMD_WREN                0x06
#define CMD_WR_DISABLE          0x04
#define CMD_RDSR1               0x05
#define CMD_RDSR2               0x35
#define CMD_WRSR1               0x01  //write status register
#define CMD_PAGEPROG            0x02

#define CMD_ERASE_SECTOR        0x20
#define CMD_ERASE_BLOCK32       0x52
#define CMD_ERASE_BLOCK64       0xD8
#define CMD_ERASE_CHIP          0x60

#define CMD_PROG_SUSPEND        0x75
#define CMD_PROG_RESUME         0x7A
#define CMD_PWR_DOWN            0xB9

#define CMD_READ_DATA           0x03
#define CMD_READ_HS             0x0B

#define CMD_MANU_ID             0x90
#define CMD_JEDEC_ID            0x9F        // Read Manufacturer and JDEC Device ID
#define CMD_UNIQUE_ID           0x4B


#define CMD_ERASE_SEC_REG       0x44
#define CMD_PROG_SEC_REG        0x42
#define CMD_READ_SEC_REG        0x48
#define CMD_ENABLE_RES          0x66
#define CMD_RESET               0x99
#define CMD_POWERDOWN           0xAB

#define DUMMY                   0xff // Dummy byte which can be changed to any value


// Read Status Register
// bit 0 BUSY 1=Write in progress
// bit 1 WEL  1=Write Enabled
// bit 2 BP0  block write protection
// bit 3 BP1  block write protection
// bit 4 BP2  block write protection
// bit 5 BP3  block write protection
// bit 6 SEC  1=Security ID space locked
// bit 7 BPL  1=BP0..BP3 are read-only, 0=r/w

void Flash__SpiWrite (unsigned char data);
unsigned char Flash__SpiRead (void);
void Flash__GetManufacturerId(uint8_t rx_buffer[]);
void Flash__WriteEnable(void);
void Flash__WriteDisable(void);
uint8_t Flash__ReadDeviceStatus(void);
uint8_t Flash__ReadByte(uint32_t addr);
bool Flash__ReadBuffer(uint32_t addr, uint8_t* pBuffer, uint32_t length);
void Flash__PageProgram(uint32_t addr, uint8_t* write_buffer, uint16_t len);
void Flash__SectorErase4k(uint32_t addr);
void Flash__BlockErase32k(uint32_t addr);
void Flash__BlockErase64k(uint32_t addr);
void Flash__ChipErase(void);
void Flash__PowerDown(void);
void Flash__WakeUp(void);
bool Flash__isBusAvailable(void);

#endif /* EXTFLASH_H_ */
