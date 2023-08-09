/*
 * DeviceCommands.c
 *
 *  Created on: Jul 24, 2023
 *      Author: adinor
 */


#include "DeviceCommands.h"
#include "Uart.h"
#include "Adc.h"
#include "Maxbotix.h"


char DataBuffer[200];
char *Version = "4.0";

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
	 sprintf(DataBuffer,"OK,BATTREAD %d\n",AdcRead_VBatt());
	 serialPutStr(DataBuffer);
}


char sonarBuffer[100];
void commandGetDistance(char *data)
{
	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_SET); 		/* turn on */
	sprintf(sonarBuffer,"OK,DISTREAD %d\n",getSonarDistance());
	serialPutStr(sonarBuffer);
//	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_SET);	/* turn off to save power */
}

void commandGetVersion(char *data)
{

	sprintf(DataBuffer,"OK,VERSION %s\n",Version);
	serialPutStr(DataBuffer);
}

void commandReboot(char *data){
	NVIC_SystemReset();
}


void commandSleep(char *data){
	serialPutStr("Sleep called...\n");
}

void commandInvalid(char *data)
{
  serialPutStr("ERROR,Invalid Command Handler!\n");
}
