/*
 * Heater.h
 *
 * Created: 8/21/2021 1:21:19 AM
 *  Author: ZeroX96
 */ 


#ifndef HEATER_H_
#define HEATER_H_

//includes
#include "main.h"
#include "Gpio.h"
#include "Pwm.h"

//define the number of Heaters in the system
#define HEATERS_NUM (1)

//required Period of 50ms => F = 1/T = 1/50ms = 20 >> sys_freq = 20Hz
#define PWM_FREQ       (20)
//required duty cycle of 60%
#define PWM_DUTY_CYCLE (FIFTY_PERCENT + TEN_PERCENT)

/************************************************************************/
/* HeaterStateT, a defined data type for the states of the Heater       */
/************************************************************************/
typedef enum{
	HEATER_OFF,
	HEATER_ON
}HeaterStateT;

/************************************************************************/
/* HeaterSelectT, a defined data type for selecting a specific Heater   */
/************************************************************************/
typedef enum{
	HEATER_ONE
}HeaterSelectT;

/* HeaterInit: Function initializes the hardware for the system heaters        */
void HeaterInit(HeaterSelectT HeaterSelect, HeaterStateT HeaterState);
/* HeaterSetState: Function sets the state of the targeted heater       */
void HeaterSetState(HeaterSelectT HeaterSelect, HeaterStateT HeaterState);
/* HeaterGetState: Function gets the current state of the targeted heater */
HeaterStateT HeaterGetState(HeaterSelectT HeaterSelect);
/* HeaterUpdate: Function updates the system state of all the heaters         */
void HeaterUpdate(void );




#endif /* HEATER_H_ */