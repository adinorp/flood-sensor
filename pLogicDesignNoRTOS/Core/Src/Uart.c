/*
 * Uart.c
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#include "Uart.h"


void serialPutStr(const char *data)
{

  HAL_UART_Transmit(Get_DebugHandle(),(uint8_t *)data, strlen(data),DEBUG_UART_TIMEOUT);

}




