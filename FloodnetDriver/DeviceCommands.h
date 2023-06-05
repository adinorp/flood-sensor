/*
 * DeviceCommands.h
 *
 *  Created on: Jun 5, 2023
 *      Author: adinor
 */

#ifndef DEVICECOMMANDS_H_
#define DEVICECOMMANDS_H_

#include "main.h"
#include <string.h>

void commandReadDeviceId(char *data);
void commandReadDeviceBattery(char *data);
void commandInvalid(char *data);
void commandGetTime(char *data);
void commandGetDate(char *data);

#endif /* DEVICECOMMANDS_H_ */
