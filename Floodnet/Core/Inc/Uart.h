/*
 * Uart.h
 *
 *  Created on: May 7, 2023
 *      Author: adinor
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"
#include <string.h>

#define DEBUG_UART_TIMEOUT 10
#define UART_DMA_RECEIVE_SIZE 1

void serialPutStr(const char *data);


#endif /* UART_H_ */
