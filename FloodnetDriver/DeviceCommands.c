/*
 * DeviceCommands.c
 *
 *  Created on: Jun 5, 2023
 *      Author: adinor
 */

#include "DeviceCommands.h"
#include "Uart.h"
#include "Adc.h"
#include "Rtc.h"


char DataBuffer[200];

void commandReadDeviceId(char *data)
{
  /* Read MCU Id, 32-bit access */
  uint8_t i;
  char DeviceId[50];
  uint8_t serialNumber[12]={0};
  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = HAL_GetUIDw0();
  deviceserial1 = HAL_GetUIDw1();
  deviceserial2 = HAL_GetUIDw2();
  memset(serialNumber, 0, 12);
  memcpy(&serialNumber[0], &deviceserial0, 4);
  memcpy(&serialNumber[4], &deviceserial1, 4);
  memcpy(&serialNumber[8], &deviceserial2, 4);
  snprintf(DeviceId, sizeof(DeviceId), "OK,STDEVICEID,");
  serialPutStr(DeviceId);
  for(i=0; i<12; i++)
  {
    i < 11 ? snprintf(DeviceId, sizeof(DeviceId), "%x", serialNumber[i]) : snprintf(DeviceId, sizeof(DeviceId), "%d\n", serialNumber[i]);
    serialPutStr(DeviceId);
  }
}


void commandReadDeviceBattery(char *data)
{

	 serialPutStr("OK,BATTREAD");
	//sprintf(DataBuffer,"OK,BATTREAD %f",AdcRead_VBatt());
	//serialPutStr(DataBuffer);

}

void commandInvalid(char *data)
{
  serialPutStr("ERROR,Invalid Command Handler!\n");
}

char dateTime[100];
void commandGetTime(char *data)
{
	RTC_TimeShow(dateTime);
	serialPutStr("OK,GETTIME\n");
	serialPutStr(dateTime);

}

void commandGetDate(char *data)
{
	RTC_DateShow(dateTime);
    serialPutStr("OK,GETDATE\n");
    serialPutStr(dateTime);
}
