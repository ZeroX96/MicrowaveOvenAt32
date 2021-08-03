/*
 * Heater.h
 *
 * Created: 7/22/2021 9:03:19 AM
 *  Author: ZeroX96
 */ 


#ifndef HEATER_H_
#define HEATER_H_

#include "Gpio.h"

#define HEATERS_NUM (1)

#define HEATER_ONE_BASE BASE_A
#define HEATER_ONE_PIN  PIN_6

typedef enum{
	HEATER_OFF,
	HEATER_ON
}HeaterStateT;

typedef enum{
	HEATER_ONE
}HeaterSelectT;

void HeaterInit(HeaterSelectT HeaterSelect, HeaterStateT HeaterState);
void HeaterSetState(HeaterSelectT HeaterSelect, HeaterStateT HeaterState);
HeaterStateT HeaterGetState(HeaterSelectT HeaterSelect);
void HeaterUpdate(void );




#endif /* HEATER_H_ */