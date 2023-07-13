/*
 * Maxbotix.c
 *
 *  Created on: Jun 28, 2023
 *      Author: psc368
 */

#include "Maxbotix.h"


uint16_t getSonarDistance(void){
	  unsigned char RxBuffer[4];
	  bool newData = false;
	  uint16_t dist_mm = 0;
	  unsigned char rx;
	  uint8_t tries = 0;
	  do {
	    HAL_GPIO_WritePin(MB_CTL_GPIO_Port, MB_CTL_Pin, GPIO_PIN_SET);
	    HAL_Delay(1); // todo: implement HAL_Delay_Microseconds()
	    HAL_GPIO_WritePin(MB_CTL_GPIO_Port, MB_CTL_Pin, GPIO_PIN_RESET);
	    if (HAL_UART_Receive(Get_SonarHandle(), (uint8_t *)&rx, 1, 20) == HAL_OK) {
	      if ((char)rx == 'R') {
	        if (HAL_UART_Receive(Get_SonarHandle(), (uint8_t *)&RxBuffer, 4, 20) == HAL_OK) {
	          if (isdigit(RxBuffer[3])) {
	            newData = true;
	          }
	          if (newData) {
	            for (int i = 0; i < 4; i++)
	              dist_mm += (RxBuffer[3 - i] - '0') * pow(10, i);
	            if (dist_mm==0)
	            	newData = false;
	          }
	        }
	      } else {
	        newData = false;
	      }
	    } else {
	      tries++;
	    }
	  } while (newData == false && tries < MAX_SONAR_TRIES - 1);
	  return dist_mm;
}
