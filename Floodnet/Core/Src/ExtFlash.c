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
#define WINBOND_FLASH_SIZE             0x800000  // 8 MB

//Power
#define WINBOND_POWER_DOWN			0xB9	// put flash in deep power down mode
#define WINBOND_REL_POWER_DOWN		0xAB	// resume from deep power down mode

//Read commands
#define WINBOND_READ_DATA           0X03    // Read Data from Flash
#define WINBOND_READ_FAST           0X0B    // Read Data from Flash

#define WINBOND_FLASH_ADDR_SIZE		   3


#define CONVERT_FLASH_ADDR_TO_UINT(addr, addr_uint32) (addr_uint32) = ((addr)[0] << 16) | ((addr)[1] << 8) | (addr)[2];
typedef uint8_t flash_addr[3];

static void flashSpiTransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);


void Flash__SpiWrite (unsigned char data)
{
	HAL_Delay(SPI_DELAY);
	Spi1_Transmit (&data, sizeof(data));
	HAL_Delay(SPI_DELAY);
}


/**
 * @brief Read a byte of data
 *
 */
unsigned char Flash__SpiRead (void)
{
	unsigned char ret = 0xFF;
	HAL_Delay(SPI_DELAY);
	Spi1_Receive (&ret, sizeof(ret));
	HAL_Delay(SPI_DELAY);
	return ret;
}

/**
 * @brief Read manufacturer's ID
 *
 */
void Flash__GetManufacturerId(uint8_t rx_buffer[])
{
    unsigned char ret = 0x00;
    unsigned char reset_cmd = 0x66;
    unsigned char issue_reset = 0x99;
    unsigned char manufacture_id_cmd[] = {CMD_JEDEC_ID,0x00,0x00,0x00};
    flashSpiTransmitReceive(&reset_cmd, &ret, 1, MAX_TIMEOUT);
    flashSpiTransmitReceive(&issue_reset, &ret, 1, MAX_TIMEOUT);
    flashSpiTransmitReceive(manufacture_id_cmd, rx_buffer, 4, MAX_TIMEOUT);
}



/**
 * @brief Flash read device status
 *
 */
uint8_t Flash__ReadDeviceStatus(void)
{
    uint8_t data = 0;
	Flash__SpiWrite(CMD_RDSR1);
    data = Flash__SpiRead() ;                     // dummy
    return( data ) ;
}


/**
 * @brief Flash Read Byte
 *
 */
uint8_t Flash__ReadByte(uint32_t addr)                  // Single Byte Read
{
    uint8_t data ;
    Flash__SpiWrite(CMD_READ_DATA) ;                         // send 03h
    Flash__SpiWrite((addr >> 16)&0xFF) ;                     // Send ReadAddr high nibble
    Flash__SpiWrite((addr >>  8)&0xFF) ;                     // Send ReadAddr middle nibble address byte to read from
    Flash__SpiWrite(addr & 0xFF) ;                           // Send ReadAddr low nibble address byte to read from
    data = Flash__SpiRead() ;                     // write data is dummy
    return( data ) ;                                // return 1 byte
}


/**
 * @brief Reads a block of data from flash
* -addr : Flash's internal address to read from
* -pBuffer : Pointer to the buffer that receives the data read
* -Length  : Number of bytes to read
*/
bool Flash__ReadBuffer(uint32_t addr, uint8_t* pBuffer, uint32_t length)
{
    Flash__SpiWrite(CMD_READ_DATA);
    Flash__SpiWrite((addr >> 16) & 0xff);
    Flash__SpiWrite((addr >> 8) & 0xff);
    Flash__SpiWrite(addr & 0xff);
    for (uint32_t i=0; i<length; ++i)
    {
       pBuffer[i] = Flash__SpiRead();
    }
    return true;
}

/**
 * @brief Flash wait while busy
 * Polls the status of the write in progress (WIP) bit of the status register
 * until the write operation is completed
 */
void flashWaitWhileBusy(void)
{
    uint8_t flash_status =0;
    Flash__SpiWrite(CMD_RDSR1);   //Send RDSR command
    /*Loop whiles memory is busy with a write cycle */
    do
    {  /* Send dummy bytes to clock out data from flash */
       flash_status = Flash__SpiRead();
    }
    while(flash_status & 0x01);  /* Write in progress */
}

/**
 * @brief Flash Page Program
 * Writes more than one byte to the flash with a single write cycle (Page Write Sequence)
 * The number of bytes cannot exceed the flash page size
 * -write_buffer : Pointer to buffer containing the date to be written to flash
 * -WriteAddr     : Flash's internal address to write to
 *
 */
void Flash__PageProgram(uint32_t addr, uint8_t* write_buffer, uint16_t length)
{

    // write enable
    Flash__WriteEnable();
    // Write Page Command
    Flash__SpiWrite(CMD_PAGEPROG);
    Flash__SpiWrite((uint8_t)(addr >> 16));
    Flash__SpiWrite((uint8_t)(addr >> 8));
    Flash__SpiWrite((uint8_t)addr);
    if(length > SPI_FLASH_PERWRITEPAGESIZE)
    {
     length = SPI_FLASH_PERWRITEPAGESIZE;
    }
    /* while there is data to be written on the FLASH */
    while (length--)
    {
      /* Send the current byte */
      Flash__SpiWrite(*write_buffer);
      /* Point on the next byte to be written */
      write_buffer++;
    }
    flashWaitWhileBusy();
}


/**
* @brief Flash Sector Erase 4K
* Sets all memory within a specified sector (4-K) to the erased state.
* addr : Address of the sector to erase
*/
void Flash__SectorErase4k(uint32_t addr)
{
   // write enable
   Flash__WriteEnable();
   Flash__SpiWrite(CMD_ERASE_SECTOR);
   Flash__SpiWrite((uint8_t)(addr >> 16));
   Flash__SpiWrite((uint8_t)(addr >> 8));
   Flash__SpiWrite((uint8_t)addr);
   flashWaitWhileBusy();
}


/**
* @brief Flash Block Erase 32K
* Sets all memory within a specified sector (32-K) to the erased state.
* addr : Address of the sector to erase
*/
void Flash__BlockErase32k(uint32_t addr)
{
   // write enable
   Flash__WriteEnable();
   Flash__SpiWrite(CMD_ERASE_BLOCK32);
   Flash__SpiWrite((uint8_t)(addr >> 16));
   Flash__SpiWrite((uint8_t)(addr >> 8));
   Flash__SpiWrite((uint8_t)addr);
   flashWaitWhileBusy();
}

/**
* @brief Flash Sector Erase 64K
* Sets all memory within a specified sector (4-K) to the erased state.
* addr : Address of the sector to erase
*/

void Flash__BlockErase64k(uint32_t addr)
{
   // write enable
   Flash__WriteEnable();
   Flash__SpiWrite(CMD_ERASE_BLOCK64);
   Flash__SpiWrite((uint8_t)(addr >> 16));
   Flash__SpiWrite((uint8_t)(addr >> 8));
   Flash__SpiWrite((uint8_t)addr);
   flashWaitWhileBusy();
}


/**
* @brief Flash Chip Erase
*
*/
void Flash__ChipErase()
{
   Flash__WriteEnable();
   Flash__SpiWrite(CMD_ERASE_CHIP);
   flashWaitWhileBusy();
}


/**
* @brief Flash Chip Erase
*
*/
void Flash__PowerDown(void)
{
  Flash__SpiWrite(CMD_PWR_DOWN);
}


/**
* @brief Flash Chip Erase
*
*/
void Flash__WakeUp(void)
{
  Flash__SpiWrite(CMD_POWERDOWN);
}


/**
* @brief flashSpiTransmitReceive
*
*/
static void flashSpiTransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  Spi1_TransmitReceive ( pTxData, pRxData, Size);
}


