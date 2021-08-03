/*
 * Motor.c
 *
 * Created: 7/23/2021 10:36:35 AM
 *  Author: ZeroX96
 */ 
#include "Motor.h"

static MotorStateT MotorOneState;

void MotorInit(MotorSelectT MotorSelect, MotorStateT MotorInitState){
	if (MotorSelect == MOTOR_ONE){
		GpioInitPin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_R, PIN_OUT);
		GpioInitPin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_L, PIN_OUT);
		if (MotorInitState == MOTOR_RUNNING){
			GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_R, PIN_HIGH);
			GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_L, PIN_LOW);
			MotorOneState = MotorInitState;
		}
		else{
			//do-nothing
		}
	}
	else{
		//currently do-nothing, we only handle one motor
	}
}
void MotorSetState(MotorSelectT MotorSelect, MotorStateT MotorState){
	if (MotorSelect == MOTOR_ONE){
		if (MotorState == MOTOR_RUNNING){
			MotorOneState = MOTOR_RUNNING;
		}
		else{
			MotorOneState = MOTOR_STOPPED;
		}
	}
	else{
		//currently do-nothing, we only handle one motor
	}
}
MotorStateT MotorGetState(MotorSelectT MotorSelect){
	return MotorOneState;
}
void MotorUpdate(void ){
	if (MotorOneState == MOTOR_RUNNING){
		GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_R, PIN_HIGH);
		GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_L, PIN_LOW);
	}
	else{
		GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_R, PIN_LOW);
		GpioWritePin(MOTOR_ONE_BASE, MOTOR_ONE_PIN_L, PIN_LOW);	
	}
}