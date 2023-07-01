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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define EXT_SDA_Pin GPIO_PIN_15
#define EXT_SDA_GPIO_Port GPIOA
#define EXT_SCL_Pin GPIO_PIN_15
#define EXT_SCL_GPIO_Port GPIOB
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define ADC_IN_Pin GPIO_PIN_3
#define ADC_IN_GPIO_Port GPIOB
#define PG_Pin GPIO_PIN_4
#define PG_GPIO_Port GPIOB
#define ADC_SW_Pin GPIO_PIN_7
#define ADC_SW_GPIO_Port GPIOB
#define FLASH_CS_Pin GPIO_PIN_9
#define FLASH_CS_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_14
#define MISO_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_10
#define MOSI_GPIO_Port GPIOA
#define MB_OC_Pin GPIO_PIN_5
#define MB_OC_GPIO_Port GPIOB
#define MB_PWR_Pin GPIO_PIN_0
#define MB_PWR_GPIO_Port GPIOA
#define SCK_Pin GPIO_PIN_13
#define SCK_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_6
#define LED_GPIO_Port GPIOB
#define EXT_PWR_Pin GPIO_PIN_9
#define EXT_PWR_GPIO_Port GPIOA
#define MB_RX_Pin GPIO_PIN_1
#define MB_RX_GPIO_Port GPIOC
#define MB_CTL_Pin GPIO_PIN_0
#define MB_CTL_GPIO_Port GPIOC
#define UART_RX_Pin GPIO_PIN_3
#define UART_RX_GPIO_Port GPIOA
#define UART_TX_Pin GPIO_PIN_2
#define UART_TX_GPIO_Port GPIOA
#define EXT_OC_Pin GPIO_PIN_10
#define EXT_OC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
I2C_HandleTypeDef   *Get_I2cHandle(void);
ADC_HandleTypeDef *Get_AdcHandle(void);
UART_HandleTypeDef *Get_DebugHandle(void);
UART_HandleTypeDef *Get_SonarHandle(void);
SPI_HandleTypeDef   *Get_SpiHandle(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
