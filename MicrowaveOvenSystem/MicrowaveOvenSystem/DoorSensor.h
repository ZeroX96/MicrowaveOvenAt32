/*
 * DoorSensor.h
 *
 * Created: 7/22/2021 9:05:04 AM
 *  Author: ZeroX96
 */ 


#ifndef DOORSENSOR_H_
#define DOORSENSOR_H_
#include "Buttons.h"

typedef BtnStateT DoorStateT;

void DoorSensInit(void );
DoorStateT DoorSensGetState(void );
void DoorSensUpdate(void );


#endif /* DOORSENSOR_H_ */