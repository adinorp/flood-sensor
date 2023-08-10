/*
 * Adc.c
 *
 *  Created on: May 11, 2023
 *      Author: adinor
 */

#include "Adc.h"


//Get_AdcHandle
float adcResult;

#define CONVERSION_POLL_TIME 10

static uint16_t ReadADCChannel(uint32_t Channel);

static uint16_t ReadADCChannel(uint32_t Channel)
{
	uint16_t result;
	if (HAL_ADCEx_Calibration_Start(Get_AdcHandle()) != HAL_OK) {
	    Error_Handler();
	  }
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = Channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	if (HAL_ADC_ConfigChannel(Get_AdcHandle(), &sConfig) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_ADC_Start(Get_AdcHandle()) != HAL_OK) {
		Error_Handler();
	}
	HAL_ADC_PollForConversion(Get_AdcHandle(), HAL_MAX_DELAY);
	HAL_ADC_Stop(Get_AdcHandle());
	if((HAL_ADC_GetState(Get_AdcHandle()) & HAL_ADC_STATE_EOC_REG) == HAL_ADC_STATE_EOC_REG)
	{
		/*##-5- Get the converted value of regular channel  ######################*/
		result = (uint16_t)HAL_ADC_GetValue(Get_AdcHandle());
	}
	return result;
}


uint16_t AdcRead_VBatt(void)
{
	HAL_GPIO_WritePin(GPIOB, ADC_SW_Pin, GPIO_PIN_RESET);
	adcResult = ReadADCChannel(ADC_CHANNEL_3); // * 3.3 * 23) / (4096 * 13);
	return adcResult;
}
