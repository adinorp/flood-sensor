/*
 * DeviceCommands.h
 *
 *  Created on: Jul 24, 2023
 *      Author: adinor
 */

#ifndef DEVICECOMMANDS_H_
#define DEVICECOMMANDS_H_

#include "main.h"


void commandReadDeviceId(char *data);
void commandReadDeviceBattery(char *data);
void commandInvalid(char *data);
void commandGetTime(char *data);
void commandGetDate(char *data);
void commandGetDistance(char *data);
void commandGetVersion(char *data);
void commandReboot(char *data);

#endif /* DEVICECOMMANDS_H_ */
