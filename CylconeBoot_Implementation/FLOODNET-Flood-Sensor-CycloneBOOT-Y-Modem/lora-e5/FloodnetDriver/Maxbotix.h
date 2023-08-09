/*
 * Maxbotix.h
 *
 *  Created on: Jun 28, 2023
 *      Author: psc368
 */

#ifndef MAXBOTIX_H_
#define MAXBOTIX_H_

#include "math.h"
#include "ctype.h"
#include "stdint.h"
#include "main.h"

#define MAX_SONAR_TRIES 5
#define MAX_SONAR_SAMPLES 7
#define MAX_SONAR_SAMPLING_DELAY 150
#define AVERAGING_METHOD 2	/* Median */

uint16_t getSonarDistance(void);

#endif /* MAXBOTIX_H_ */
