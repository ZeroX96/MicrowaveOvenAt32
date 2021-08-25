/*
 * Lamp.c
 *
 * Created: 7/23/2021 3:04:40 PM
 *  Author: ZeroX96
 */ 
#include "Lamp.h"

/***************************************************************************/
/* An internal Array to hold the system Lamps states and informations      */
/* LAMPS_NUM defines the number of the Lamps required in the project       */
/***************************************************************************/
static LampStateT InternalLampStates[LAMPS_NUM];

/*******************************************************************************/
/* LampInit: Function initializes the hardware for the system Lamps            */
/* Params:                                                                     */
/* Input = LampSelect = Defines which Lamp to initialize                       */
/* Input = LampInitState = Defines the initial state for the targeted Lamp     */
/* Output= NON                                                                 */
/*******************************************************************************/
void LampInit(LampSelectT LampSelect, LampStateT LampInitState){
	if (LampSelect == LAMP_ONE){
		GpioInitPin(LAMP_ONE_BASE, LAMP_ONE_PIN, PIN_OUT);
	}
	else{
		//do nothing for now
	}
	InternalLampStates[LampSelect] = LampInitState;
}

/************************************************************************/
/* LampSetState: Function sets the state of the targeted Lamp           */
/* Params:                                                              */
/* Input = LampSelect = Defines which Lamp to initialize                */
/* Input = LampState = Defines the needed state for a targeted Lamp     */
/* Output= NON                                                          */
/************************************************************************/
void LampSetState(LampSelectT LampSelect, LampStateT LampState){
	InternalLampStates[LampSelect] = LampState;
}

/**************************************************************************/
/* LampGetState: Function gets the current state of the targeted Lamp     */
/* Params:                                                                */
/* Input = LampSelect = Defines which Lamp to get it's state              */
/* Output= BtnStateT = returns the state of the targeted Lamp             */
/**************************************************************************/
BtnStateT LampGetState(LampSelectT LampSelect){
	return InternalLampStates[LampSelect];
}


/***************************************************************************/
/* LampUpdate: Function updates the system state of all the Lamps         */
/* Task: Perform the main module task by activating the hardware as needed */
/* Params:                                                                 */
/* Input = NON                                                             */
/* Output= NON                                                             */
/***************************************************************************/
void LampUpdate(void ){
	if (InternalLampStates[LAMP_ONE] == LAMP_ON){
		GpioWritePin(LAMP_ONE_BASE, LAMP_ONE_PIN, PIN_HIGH);
	}
	else{
		GpioWritePin(LAMP_ONE_BASE, LAMP_ONE_PIN, PIN_LOW);
	}
}

