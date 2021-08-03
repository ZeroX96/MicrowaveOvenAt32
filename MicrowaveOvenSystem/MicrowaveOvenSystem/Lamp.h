/*
 * Lamp.h
 *
 * Created: 7/22/2021 9:03:44 AM
 *  Author: ZeroX96
 */ 


#ifndef LAMP_H_
#define LAMP_H_

#include "Gpio.h"

#define LAMPS_NUM (1)

#define LAMP_ONE_BASE BASE_A
#define LAMP_ONE_PIN  PIN_7

typedef enum{
	LAMP_OFF,
	LAMP_ON
}LampStateT;

typedef enum{
	LAMP_ONE
}LampSelectT;

void LampInit(LampSelectT LampSelect, LampStateT LampInitState);
void LampSetState(LampSelectT LampSelect, LampStateT LampState);
BtnStateT LampGetState(LampSelectT LampSelect);
void LampUpdate(void );




#endif /* LAMP_H_ */