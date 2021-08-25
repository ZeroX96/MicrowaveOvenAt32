/*
 * DoorSensor.c
 *
 * Created: 7/23/2021 6:35:06 AM
 *  Author: ZeroX96
 */ 
#include "DoorSensor.h"

/****************************************************************************/
/* DoorSensInit: Function initializes the hardware for the system buttons        */
/* Params:                                                                  */
/* Input = BtnSelect = Defines which button to initialize                   */
/* Input = BtnInitState = Defines the initial state for the targeted button */
/* Output= NON                                                              */
/****************************************************************************/
void DoorSensInit(void ){
	BtnInit(BTN_DOOR, BTN_RELEASED);
}

/************************************************************************/
/* DoorSensGetState: Function gets the current state of the targeted button  */
/* Params:                                                              */
/* Input = BtnSelect = Defines which button to initialize               */
/* Output= BtnStateT = returns the state of the targeted button         */
/************************************************************************/
DoorStateT DoorSensGetState(void ){
	return BtnGetState(BTN_DOOR);
}

/************************************************************************/
/* BtnUpdate: Function updates the current state of all the buttons     */
/* Params:                                                              */
/* Input = NON                                                          */
/* Output= NON                                                          */
/************************************************************************/
void DoorSensUpdate(void ){
	BtnUpdate();	
}


