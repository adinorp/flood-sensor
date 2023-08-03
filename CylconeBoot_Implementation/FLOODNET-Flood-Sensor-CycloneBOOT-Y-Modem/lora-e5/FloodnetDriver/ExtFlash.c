/*
 * ExtFlash.c
 *
 *  Created on: May 8, 2023
 *      Author: adinor
 *
 */

#include "ExtFlash.h"

#define MAX_TIMEOUT 100
#define SPI_DELAY 1
#define SPI_FLASH_PERWRITEPAGESIZE      (256U)
#define SPI_PACKET_SIZE (1024U)

#ifndef MIN
#define MIN(x,y) ((x <= y)? x : y)
#endif

//Set to 1 to use "Fast Read" command instead of "Read Data" command
#define WINBOND_USE_FAST_READ 1

#define WINBOND_JEDEC_MANUFACTURER_ID 	0xEF
#define WINBOND_JEDEC_MEMORY_TYPE		0x40
#define WINBOND_JEDEC_CAPACITY			0x14
#define WINBOND_JEDEC_ID				((WINBOND_JEDEC_MANUFACTURER_ID << 16) | (WINBOND_JEDEC_MEMORY_TYPE << 8) | WINBOND_JEDEC_CAPACITY)

#define WINBOND_FLASH_SIZE             	0x100000  // 8 Mbits -> 1MB

//Power
#define WINBOND_POWER_DOWN				0xB9	// put flash in deep power down mode
#define WINBOND_REL_POWER_DOWN			0xAB	// resume from deep power down mode

//Read commands
#define WINBOND_READ_DATA           	0X03    // Read Data from Flash
#define WINBOND_READ_FAST           	0X0B    // Read Data from Flash

#define WINBOND_FLASH_ADDR_SIZE		   	3

#define CONVERT_FLASH_ADDR_TO_UINT(addr, addr_uint32) (addr_uint32) = ((addr)[0] << 16) | ((addr)[1] << 8) | (addr)[2];
typedef uint8_t flash_addr[3];


/**
 * @brief Flash Init routine
 **/

bool Flash__Init(void)
{
	uint32_t jedecId;

	HAL_Delay(100);
	//Assert Spi CS pin
	Spi1_AssertCs();
	HAL_Delay(100);

	Flash__GetJEDEC_ID(&jedecId);

	if(jedecId != WINBOND_JEDEC_ID)
	{
		return false;
	}
	else
	{
		return true;
	}
}


/**
 * @brief Flash Spi write routine
 **/

void Flash__SpiWrite(unsigned char data)
{
	Spi1_Transmit(&data, sizeof(data));
}


/**
 * @brief Flash Spi read routine
 **/

unsigned char Flash__SpiRead(void)
{
	unsigned char ret = 0x00;
	Spi1_Receive(&ret, sizeof(ret));
	return ret;
}


/**
 * @brief Flash Write Enable routine
 **/

void Flash__WriteEnable(void)
{
	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Write Enable Command
	Flash__SpiWrite(CMD_WREN);
	//Assert Spi CS pin
	Spi1_AssertCs();
}


/**
 * @brief Flash Read JEDEC ID
 * JEDEC ID is a 24bits long ID organized as follow:
 *
 *  	Byte 2						Byte 1					Byte 0
 * 	Manufacturer ID (8bits)		Memory Type (8bits)		Capacity (8bits)
 *
 * @param[out] jdecId Flash JEDEC id to be read
 **/

void Flash__GetJEDEC_ID(uint32_t *jdecId)
{
	uint8_t read_buff[3];

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Read JEDEC ID Command
	Flash__SpiWrite(CMD_JEDEC_ID);
	read_buff[0] = Flash__SpiRead();
	read_buff[1] = Flash__SpiRead();
	read_buff[2] = Flash__SpiRead();
	//Assert Spi CS pin
	Spi1_AssertCs();

	//Format JEDEC ID
	*jdecId = (read_buff[0] << 16) | (read_buff[1] << 8) | read_buff[2];
}


/**
 * @brief Flash read device status register 1 routine
 **/

uint8_t Flash__ReadDeviceStatus1(void)
{
	uint8_t data = 0;

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Read Status Register 1 Command
	Flash__SpiWrite(CMD_RDSR1);
	data = Flash__SpiRead();                     // dummy
	//Assert Spi CS pin
	Spi1_AssertCs();

	return (data);
}


/**
 * @brief Flash read device status register 2 routine
 **/

uint8_t Flash__ReadDeviceStatus2(void)
{
	uint8_t data = 0;

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Read Status Register 2 Command
	Flash__SpiWrite(CMD_RDSR2);
	data = Flash__SpiRead();                     // dummy
	//Assert Spi CS pin
	Spi1_AssertCs();

	return (data);
}


/**
 * @brief Flash read device status routine
 **/

uint16_t Flash__ReadDeviceStatus(void)
{
	uint16_t data = 0;

	data = Flash__ReadDeviceStatus2();
	data = (data << 8) | Flash__ReadDeviceStatus1();

	return (data);
}


/**
 * @brief Flash Read Byte routine
 * @param[in] addr Flash's internal address to read from
 **/

uint8_t Flash__ReadByte(uint32_t addr)          // Single Byte Read
{
	uint8_t data;

	//Deassert Spi CS pin
	Spi1_DeassertCs();
#if WINBOND_USE_FAST_READ
	//Send Fast Read Command
	Flash__SpiWrite(CMD_READ_HS);               // send 0Bh
	Flash__SpiWrite((addr >> 16) & 0xFF);       // Send ReadAddr high nibble
	Flash__SpiWrite((addr >> 8) & 0xFF); 		// Send ReadAddr middle nibble address byte to read from
	Flash__SpiWrite(addr & 0xFF); 				// Send ReadAddr low nibble address byte to read from
	Flash__SpiWrite(DUMMY);						// Dummy eight clocks
#else
	//Send Read Data Command
	Flash__SpiWrite(CMD_READ_DATA);             // send 03h
	Flash__SpiWrite((addr >> 16) & 0xFF);       // Send ReadAddr high nibble
	Flash__SpiWrite((addr >> 8) & 0xFF); 		// Send ReadAddr middle nibble address byte to read from
	Flash__SpiWrite(addr & 0xFF); 				// Send ReadAddr low nibble address byte to read from
#endif
	//Read single byte
	data = Flash__SpiRead();
	//Assert Spi CS pin
	Spi1_AssertCs();

	return (data);                              // return 1 byte
}

/**
 * @brief Flash Reads data routine
 * @param[in] addr Flash's internal address to read from
 * @param[in] pBuffer Pointer to the buffer that receives the data read
 * @param[in] Length Number of bytes to read
 **/

bool Flash__ReadBuffer(uint32_t addr, uint8_t *pBuffer, uint32_t length)
{
	//Deassert Spi CS pin
	Spi1_DeassertCs();
#if WINBOND_USE_FAST_READ
	//Send Fast Read Command
	Flash__SpiWrite(CMD_READ_HS);               // send 0Bh
	Flash__SpiWrite((addr >> 16) & 0xFF);       // Send ReadAddr high nibble
	Flash__SpiWrite((addr >> 8) & 0xFF); 		// Send ReadAddr middle nibble address byte to read from
	Flash__SpiWrite(addr & 0xFF); 				// Send ReadAddr low nibble address byte to read from
	Flash__SpiWrite(DUMMY);						// Dummy eight clocks
#else
	//Send Read Data Command
	Flash__SpiWrite(CMD_READ_DATA);             // send 03h
	Flash__SpiWrite((addr >> 16) & 0xFF);       // Send ReadAddr high nibble
	Flash__SpiWrite((addr >> 8) & 0xFF); 		// Send ReadAddr middle nibble address byte to read from
	Flash__SpiWrite(addr & 0xFF); 				// Send ReadAddr low nibble address byte to read from
#endif
	//Read bytes
	for (uint32_t i = 0; i < length; ++i) {
		pBuffer[i] = Flash__SpiRead();
	}
	//Assert Spi CS pin
	Spi1_AssertCs();

	return true;
}


/**
 * @brief Flash wait while busy
 * Polls the status of the write in progress (WIP) bit of the status register
 * until the write operation is completed
 **/

void flashWaitWhileBusy(void)
{
	uint8_t flash_status = 0;

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Read Status Register 1 Command
	Flash__SpiWrite(CMD_RDSR1);   //Send RDSR command
	/*Loop whiles memory is busy with a write cycle */
	do { /* Send dummy bytes to clock out data from flash */
		flash_status = Flash__SpiRead();
	} while (flash_status & 0x01); /* Write in progress */
	//Assert Spi CS pin
	Spi1_AssertCs();
}


/**
 * @brief Flash Page Program routine
 * Writes more than one byte to the flash with a single write cycle (Page Write Sequence)
 * The number of bytes cannot exceed the flash page size !!!
 * @param[in] addr Write page address
 * @param[in] write_buffer Pointer to buffer containing the date to be written to flash
 * @param[in] length Number of bytes to be written
 **/

void Flash__PageProgram(uint32_t addr, uint8_t *write_buffer, uint16_t length)
{
	//Wait for last operation to end
	flashWaitWhileBusy();
	//Enable write operation
	Flash__WriteEnable();

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	// Send Page Program Command
	Flash__SpiWrite(CMD_PAGEPROG);
	Flash__SpiWrite((uint8_t) (addr >> 16));
	Flash__SpiWrite((uint8_t) (addr >> 8));
	Flash__SpiWrite((uint8_t) addr);


	// Check if the address match the beginning of a page
	if(addr & 0xFF)
	{
		length = MIN(length, SPI_FLASH_PERWRITEPAGESIZE - (addr % SPI_FLASH_PERWRITEPAGESIZE));
	}
	else
	{
		length = MIN(length, SPI_FLASH_PERWRITEPAGESIZE);
	}

	/* while there is data to be written on the FLASH */
	while (length--) {
		/* Send the current byte */
		Flash__SpiWrite(*write_buffer);
		/* Point on the next byte to be written */
		write_buffer++;
	}
	//Assert Spi CS pin
	Spi1_AssertCs();

	// Wait for page program operation to end
	flashWaitWhileBusy();
}


/**
 * @brief Flash 4kB Sector Erase routine
 * @param[in] addr Address of the sector to be erased
 **/

void Flash__SectorErase4k(uint32_t addr)
{
	// Wait for last operation to end
	flashWaitWhileBusy();
	// Enable write operation
	Flash__WriteEnable();

	//Make sure it is a 4k sector address
	if(addr & 0xFFF)
	{
		addr = addr & 0x00FFF000;
	}

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Sector Erase Command
	Flash__SpiWrite(CMD_ERASE_SECTOR);
	Flash__SpiWrite((uint8_t) (addr >> 16));
	Flash__SpiWrite((uint8_t) (addr >> 8));
	Flash__SpiWrite((uint8_t) addr);
	//Assert Spi CS pin
	Spi1_AssertCs();

	// Wait for sector erase 4k operation to end
	flashWaitWhileBusy();
}


/**
 * @brief Flash 32kB Block Erase routine
 * @param[in] addr Address of the block to be erased
 **/

void Flash__BlockErase32k(uint32_t addr)
{
	// Wait for last operation to end
	flashWaitWhileBusy();
	// Enable write operation
	Flash__WriteEnable();

	//Make sure it is a 32k block address
	if(addr % 0x8000)
	{
		addr = addr - (addr % 0x8000);
	}

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Block Erase (32kB) Command
	Flash__SpiWrite(CMD_ERASE_BLOCK32);
	Flash__SpiWrite((uint8_t) (addr >> 16));
	Flash__SpiWrite((uint8_t) (addr >> 8));
	Flash__SpiWrite((uint8_t) addr);
	//Assert Spi CS pin
	Spi1_AssertCs();

	// Wait for block erase 32k operation to end
	flashWaitWhileBusy();
}


/**
 * @brief Flash 64kB Block Erase routine
 * @param[in] addr Address of the block to be erased
 **/

void Flash__BlockErase64k(uint32_t addr)
{
	// Wait for last operation to end
	flashWaitWhileBusy();
	// Enable write operation
	Flash__WriteEnable();

	//Make sure it is a 64k block address
	if(addr & 0x00FFFF)
	{
		addr = addr - (addr % 0x8000);
	}

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Block Erase (64kB) Command
	Flash__SpiWrite(CMD_ERASE_BLOCK64);
	Flash__SpiWrite((uint8_t) (addr >> 16));
	Flash__SpiWrite((uint8_t) (addr >> 8));
	Flash__SpiWrite((uint8_t) addr);
	//Assert Spi CS pin
	Spi1_AssertCs();

	// Wait for block erase 64k operation to end
	flashWaitWhileBusy();
}


/**
 * @brief Flash Erase Chip routine
 **/

void Flash__ChipErase()
{
	// Wait for last operation to end
	flashWaitWhileBusy();
	// Enable write operation
	Flash__WriteEnable();

	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Chip Erase Command
	Flash__SpiWrite(CMD_ERASE_CHIP);
	//Assert Spi CS pin
	Spi1_AssertCs();

	// Wait for chip erase operation to end
	flashWaitWhileBusy();
}


/**
 * @brief Flash Power down routine
 **/

void Flash__PowerDown(void)
{
	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Power Down Command
	Flash__SpiWrite(CMD_PWR_DOWN);
	//Assert Spi CS pin
	Spi1_AssertCs();
}

/**
 * @brief Flash Wake Up routine
 **/

void Flash__WakeUp(void)
{
	//Deassert Spi CS pin
	Spi1_DeassertCs();
	//Send Release Powerdown Command
	Flash__SpiWrite(CMD_POWERDOWN);
	//Assert Spi CS pin
	Spi1_AssertCs();
}
