/*
 * sys_tick.h
 *
 *  Created on: Jul 1, 2023
 *      Author: adinor
 */

#ifndef INC_SYS_TICK_H_
#define INC_SYS_TICK_H_

#include "main.h"

void Tick_Init(void);
uint32_t SysTick_Get(void);
void SysTick_Handler(void);

#endif /* INC_SYS_TICK_H_ */
