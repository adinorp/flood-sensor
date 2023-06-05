/*
 * Adc.c
 *
 *  Created on: May 11, 2023
 *      Author: adinor
 */

#include "Adc.h"


//Get_AdcHandle

const float convFacto = 3.300;
uint16_t rawValue = 0;
float adcResult = 0.0;
#define CONVERSION_POLL_TIME 10

static float ReadADCChannel(uint32_t Channel);

static float ReadADCChannel(uint32_t Channel)
{
	float result = 0.00;

	if (HAL_ADCEx_Calibration_Start(Get_AdcHandle()) != HAL_OK) {
	    Error_Handler();
	  }
	HAL_ADC_Start(Get_AdcHandle());
	HAL_ADC_PollForConversion(Get_AdcHandle(), HAL_MAX_DELAY);
	HAL_ADC_Stop(Get_AdcHandle());

	if((HAL_ADC_GetState(Get_AdcHandle()) & HAL_ADC_STATE_EOC_REG) == HAL_ADC_STATE_EOC_REG)
	{
		/*##-5- Get the converted value of regular channel  ######################*/
		rawValue = HAL_ADC_GetValue(Get_AdcHandle());
		result = ((float)rawValue) / 4095 * convFacto;
	}

	return result;
}


float AdcRead_VBatt(void)
{
	HAL_GPIO_WritePin(GPIOB, ADC_SW_Pin, GPIO_PIN_RESET);
	adcResult = ReadADCChannel(ADC_CHANNEL_2);
	return adcResult;
}
