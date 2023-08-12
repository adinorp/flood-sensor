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

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hlpuart1;

char DataBuffer[200];

void commandOK(char *data){
	serialPutStr("OK\n");
}

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
	 sprintf(DataBuffer,"%d\n",AdcRead_VBatt());
	 HAL_Delay(250);
	 serialPutStr(DataBuffer);
}


char sonarBuffer[100];
void commandGetDistance(char *data)
{
	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_RESET); 		/* turn on */
	sprintf(sonarBuffer,"%d\n",getSonarDistance());
	serialPutStr(sonarBuffer);
//	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_SET);	/* turn off to save power */
}

void commandGetVersion(char *data)
{

	sprintf(DataBuffer,"OK,VERSION %s\n","v0");
	serialPutStr(DataBuffer);
}

void commandReboot(char *data){
	NVIC_SystemReset();
}


void commandSleep(char *data){
	serialPutStr("SOK\n");
	serialPutStr("SOK\n");
	serialPutStr("SOK\n");
	serialPutStr("SOK\n");
	HAL_SuspendTick();
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin = GPIO_PIN_All&(~GPIO_PIN_0);
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	__HAL_RCC_GPIOA_CLK_DISABLE();
	GPIO_InitStructure.Pin = GPIO_PIN_All;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	__HAL_RCC_GPIOB_CLK_DISABLE();
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	__HAL_RCC_GPIOC_CLK_DISABLE();
	HAL_UART_MspDeInit(&huart2);
	LL_PWR_ClearFlag_C1STOP_C1STB();
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0xFFFF, RTC_WAKEUPCLOCK_RTCCLK_DIV16,0);
	HAL_PWREx_EnterSTOP1Mode(PWR_STOPENTRY_WFI);
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0xFFFF, RTC_WAKEUPCLOCK_RTCCLK_DIV16,0);
	HAL_PWREx_EnterSTOP1Mode(PWR_STOPENTRY_WFI);
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	SystemClock_Config();
	HAL_ResumeTick();
	HAL_UART_MspInit(&huart2);
	HAL_UART_MspInit(&hlpuart1);
	MX_GPIO_Init();
	for(int i=0;i<3;i++){
		serialPutStr("..\n");
		HAL_Delay(50);
	}
}

void commandInvalid(char *data)
{
  serialPutStr("ERROR,Invalid Command Handler!\n");
}
