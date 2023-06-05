/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void rTosDelay(uint32_t Delay);
UART_HandleTypeDef *Get_DebugHandle(void);
osMessageQId Get_TerminalQueueHandle(void);
UART_HandleTypeDef *Get_SonarHandle(void);
RTC_HandleTypeDef  *Get_RtcHandle(void);
SPI_HandleTypeDef   *Get_SpiHandle(void);
osMutexId  Get_UartMutexHandle(void);
osMutexId  Get_SpiMutexHandle(void);
osMutexId  Get_I2cMutexHandle(void);
osMutexId  Get_RtcMutexHandle(void);
I2C_HandleTypeDef   *Get_I2cHandle(void);
ADC_HandleTypeDef *Get_AdcHandle(void);
void terminalTaskHandler(void const * argument);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define ADC_SW_Pin GPIO_PIN_7
#define ADC_SW_GPIO_Port GPIOB
#define MB_OC_Pin GPIO_PIN_5
#define MB_OC_GPIO_Port GPIOB
#define MB_PWR_Pin GPIO_PIN_0
#define MB_PWR_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_6
#define LED_GPIO_Port GPIOB
#define EXT_PWR_Pin GPIO_PIN_9
#define EXT_PWR_GPIO_Port GPIOA
#define MB_RX_Pin GPIO_PIN_1
#define MB_RX_GPIO_Port GPIOC
#define MB_CTL_Pin GPIO_PIN_0
#define MB_CTL_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
