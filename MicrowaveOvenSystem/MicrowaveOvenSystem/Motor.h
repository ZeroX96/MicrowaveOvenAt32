/*
 * Motor.h
 *
 * Created: 7/22/2021 9:03:59 AM
 *  Author: ZeroX96
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "Gpio.h"

#define MOTOR_ONE_BASE  BASE_A
#define MOTOR_ONE_PIN_R PIN_4
#define MOTOR_ONE_PIN_L PIN_5

typedef enum{
	MOTOR_ONE
}MotorSelectT;

typedef enum{
	MOTOR_STOPPED,
	MOTOR_RUNNING
}MotorStateT;

void MotorInit(MotorSelectT MotorSelect, MotorStateT MotorInitState);
void MotorSetState(MotorSelectT MotorSelect, MotorStateT MotorState);
MotorStateT MotorGetState(MotorSelectT MotorSelect);
void MotorUpdate(void );
#endif /* MOTOR_H_ */