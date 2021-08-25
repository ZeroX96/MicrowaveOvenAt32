/*
 * Lamp.h
 *
 * Created: 7/22/2021 9:03:44 AM
 *  Author: ZeroX96
 */ 


#ifndef LAMP_H_
#define LAMP_H_

#include "Gpio.h"
#include "Buttons.h"
#include "main.h"

//define the number of Lamps in the system
#define LAMPS_NUM (1)


/************************************************************************/
/* LampStateT, a defined data type for the states of the Lamps          */
/************************************************************************/
typedef enum{
	LAMP_OFF,
	LAMP_ON
}LampStateT;

/************************************************************************/
/* LampSelectT, a defined data type for selecting a specific Lamp       */
/************************************************************************/
typedef enum{
	LAMP_ONE
}LampSelectT;

/* LampInit: Function initializes the hardware for the system Lamps            */
void LampInit(LampSelectT LampSelect, LampStateT LampInitState);
/* LampSetState: Function sets the state of the targeted Lamp           */
void LampSetState(LampSelectT LampSelect, LampStateT LampState);
/* LampGetState: Function gets the current state of the targeted Lamp     */
BtnStateT LampGetState(LampSelectT LampSelect);
/* LampUpdate: Function updates the system state of all the Lamps         */
void LampUpdate(void );




#endif /* LAMP_H_ */