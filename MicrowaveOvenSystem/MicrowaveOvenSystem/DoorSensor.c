/*
 * DoorSensor.c
 *
 * Created: 7/23/2021 6:35:06 AM
 *  Author: Mosta
 */ 
#include "DoorSensor.h"

void DoorSensInit(void ){
	BtnInit(BTN_DOOR, BTN_RELEASED);
}

DoorStateT DoorSensGetState(void ){
	return BtnGetState(BTN_DOOR);
}

void DoorSensUpdate(void ){
	BtnUpdate();	
}


