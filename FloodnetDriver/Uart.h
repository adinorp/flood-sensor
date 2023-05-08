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

void serialPutStr(const char *data);
void serialPutStrNoMutex(const char *data);

#endif /* UART_H_ */
