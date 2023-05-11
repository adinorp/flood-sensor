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
#define CONVERSION_POLL_TIME 10

static float ReadADCChannel(uint32_t Channel);

static float ReadADCChannel(uint32_t Channel)
{
	float result = 0.00;

	HAL_ADC_Start(Get_AdcHandle());
	HAL_ADC_PollForConversion(Get_AdcHandle(), CONVERSION_POLL_TIME);

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
	return ReadADCChannel(ADC_CHANNEL_2);
}
