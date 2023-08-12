/*
 * Maxbotix.c
 *
 *  Created on: Jun 28, 2023
 *      Author: psc368
 */

#include "Maxbotix.h"
#include "Uart.h"

volatile uint16_t readings_arr[30] = { 0 };
size_t arr_len = sizeof(readings_arr) / sizeof(readings_arr[0]);

static uint16_t singleRead(void);
static uint16_t mean(unsigned int number_of_samples);
static uint16_t median(unsigned int number_of_samples);
static uint16_t mode_(unsigned int number_of_samples);
static void swap(volatile uint16_t *p, volatile uint16_t *q);
static int partition(int lowIndex, int highIndex);
static void quickSort(int lowIndex, int highIndex);

static uint16_t singleRead(void) {
	unsigned char RxBuffer[4];
	bool newData = false;
	uint16_t dist_mm = 0;
	unsigned char rx;
	uint8_t tries = 0;

	do {
		HAL_GPIO_WritePin(MB_CTL_GPIO_Port, MB_CTL_Pin, GPIO_PIN_SET);
		HAL_Delay(1); // todo: implement HAL_Delay_Microseconds()
		HAL_GPIO_WritePin(MB_CTL_GPIO_Port, MB_CTL_Pin, GPIO_PIN_RESET);
		if (HAL_UART_Receive(Get_SonarHandle(), (uint8_t*) &rx, 1, 20)
				== HAL_OK) {
			if ((char) rx == 'R') {
				if (HAL_UART_Receive(Get_SonarHandle(), (uint8_t*) &RxBuffer, 4,
						20) == HAL_OK) {
					if (isdigit(RxBuffer[3])) {
						newData = true;
					}
					if (newData) {
						for (int i = 0; i < 4; i++)
							dist_mm += (RxBuffer[3 - i] - '0') * pow(10, i);
						if (dist_mm == 0)
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

uint16_t getSonarDistance(void) {
	uint16_t dist_mm = 0;
	/* RESET IS ON, SET IS OFF! is this in reverse? wdik */
	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_RESET);
	/* First two are from the BOOT UP message of Maxbotix */
	singleRead();
	singleRead();
	for (int i = 0; i < MAX_SONAR_SAMPLES; i++) {
		readings_arr[i] = singleRead();
		HAL_Delay(150);
	}
	HAL_GPIO_WritePin(MB_PWR_GPIO_Port, MB_PWR_Pin, GPIO_PIN_SET);
	switch (AVERAGING_METHOD) {
	case 1: /* Mean */
		dist_mm = mean(MAX_SONAR_SAMPLES);
		break;
	case 2: /* Median */
		dist_mm = median(MAX_SONAR_SAMPLES);
		break;
	case 3: /* Mode */
		dist_mm = mode_(MAX_SONAR_SAMPLES);
		break;
	default: /* should never reach here */
		dist_mm = singleRead();
		break;
	}
	return dist_mm;
}

static void swap(volatile uint16_t *p, volatile uint16_t *q) {
	int t = *p;
	*p = *q;
	*q = t;
}

static int partition(int lowIndex, int highIndex) {
	int pivotElement = readings_arr[highIndex];
	int i = (lowIndex - 1);
	for (int j = lowIndex; j <= highIndex - 1; j++) {
		if (readings_arr[j] <= pivotElement) {
			i++;
			swap(&readings_arr[i], &readings_arr[j]);
		}
	}
	swap(&readings_arr[i + 1], &readings_arr[highIndex]);
	return (i + 1);
}

static void quickSort(int lowIndex, int highIndex) {
	if (lowIndex < highIndex) {
		int pivot = partition(lowIndex, highIndex);
		quickSort(lowIndex, pivot - 1);
		quickSort(pivot + 1, highIndex);
	}
}

static uint16_t mean(unsigned int number_of_samples) {
	uint16_t readings_sum = 0;
	for (int i = 0; i < number_of_samples; i++) {
		readings_sum = readings_sum + readings_arr[i];
	}
	return readings_sum / number_of_samples;
}

static uint16_t median(unsigned int number_of_samples) {
	quickSort(0, number_of_samples - 1);
	if (number_of_samples % 2 != 0) {
		return readings_arr[(number_of_samples + 1) / 2 - 1];
	} else {
		return (readings_arr[number_of_samples / 2 - 1]
				+ readings_arr[number_of_samples / 2]) / 2;
	}
}

static uint16_t mode_(unsigned int number_of_samples) {
	int counter = 1;
	int max = 0;
	uint16_t mode_ = readings_arr[0];
	for (int i = 0; i < number_of_samples - 1; i++) {
		if (readings_arr[i] == readings_arr[i + 1]) {
			counter++;
			if (counter > max) {
				max = counter;
				mode_ = readings_arr[i];
			}
		} else
			counter = 1;
	}
	return mode_;
}
