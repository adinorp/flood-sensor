/*
 * sys_tick.c
 *
 *  Created on: Jul 1, 2023
 *      Author: adinor
 */

#include "sys_tick.h"			// For timer initialization
#include "main.h"
#include <constants.h>


/**
 * System tick variable
 */
static volatile uint32_t Tick = 0;
extern TIM_HandleTypeDef htim16;

void Tick_Init(void)
{
	/* USER CODE BEGIN TIM16_Init 0 */

	/* USER CODE END TIM16_Init 0 */

	/* USER CODE BEGIN TIM16_Init 1 */

	/* USER CODE END TIM16_Init 1 */
	htim16.Instance = TIM16;
	htim16.Init.Prescaler = 0;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = 47999;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM16_Init 2 */
	HAL_TIM_Base_Start_IT(&htim16);
	/* USER CODE END TIM16_Init 2 */
}

uint32_t SysTick_Get()
{
	return Tick;
}



/**
 * @brief This function handles TIM16 global interrupt.
 */
void TIM16_IRQHandler(void)
{
	/* USER CODE BEGIN TIM16_IRQn 0 */

	/* USER CODE END TIM16_IRQn 0 */
	HAL_TIM_IRQHandler(&htim16);
	/* USER CODE BEGIN TIM16_IRQn 1 */
	Tick++;
	/* USER CODE END TIM16_IRQn 1 */
}
