/*
 * DoorSensor.h
 *
 * Created: 7/22/2021 9:05:04 AM
 *  Author: ZeroX96
 */ 


#ifndef DOORSENSOR_H_
#define DOORSENSOR_H_
#include "Buttons.h"

/******************************************************************************/
/* DoorStateT andBtnStateT, a defined data type for the states of the buttons */
/******************************************************************************/
typedef BtnStateT DoorStateT;

/* DoorSensInit: Function initializes the hardware for the system Door Sensor button */
void DoorSensInit(void );
/* DoorSensGetState: Function gets the current state of the targeted button  */
DoorStateT DoorSensGetState(void );
/* DoorSensUpdate: Function updates the current state of all the buttons     */
void DoorSensUpdate(void );


#endif /* DOORSENSOR_H_ */