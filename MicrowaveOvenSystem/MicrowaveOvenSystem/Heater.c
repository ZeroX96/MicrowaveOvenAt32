/*
 * Heater.c
 *
 * Created: 7/23/2021 3:04:17 PM
 *  Author: ZeroX96
 */ 
#include "Heater.h"

static HeaterStateT InternalHeaterStates[HEATERS_NUM];


void HeaterInit(HeaterSelectT HeaterSelect, HeaterStateT HeaterInitState){
	if (HeaterSelect == HEATER_ONE){
		GpioInitPin(HEATER_ONE_BASE, HEATER_ONE_PIN, PIN_OUT);
	}
	else{
		//donothingfornow
	}
	InternalHeaterStates[HeaterSelect] = HeaterInitState;
}
void HeaterSetState(HeaterSelectT HeaterSelect, HeaterStateT HeaterState){
	InternalHeaterStates[HeaterSelect] = HeaterState;
}
HeaterStateT HeaterGetState(HeaterSelectT HeaterSelect){
	return InternalHeaterStates[HeaterSelect];
}
void HeaterUpdate(void ){
	if (InternalHeaterStates[HEATER_ONE] == HEATER_ON){
		GpioWritePin(HEATER_ONE_BASE, HEATER_ONE_PIN, PIN_HIGH);
	}
	else{
		GpioWritePin(HEATER_ONE_BASE, HEATER_ONE_PIN, PIN_LOW);
	}
}
