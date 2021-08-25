/*
 * Heater.c
 *
 * Created: 8/21/2021 1:25:17 AM
 *  Author: ZeroX96
 */
#include "Heater.h"
/************************************************************************/
/* HeaterT, a defined data type for the states and info of the Heaters  */
/* PwmT defines the type needed to handle the pwm driver in the mcu     */
/* HeaterStateT defines the state of the targeted heater                */
/************************************************************************/
typedef struct{
    PwmT         HeaterPwm;
    HeaterStateT HeaterState;
}HeaterT;

/***************************************************************************/
/* An internal Array to hold the system heaters states and informations    */
/* HEATERS_NUM defines the number of the heaters required in the project   */
/***************************************************************************/
static HeaterT InternalHeaterInfo[HEATERS_NUM];

/*******************************************************************************/
/* HeaterInit: Function initializes the hardware for the system heaters        */
/* Params:                                                                     */
/* Input = HeaterSelect = Defines which heater to initialize                   */
/* Input = HeaterInitState = Defines the initial state for the targeted heater */
/* Output= NON                                                                 */
/*******************************************************************************/
void HeaterInit(HeaterSelectT HeaterSelect, HeaterStateT HeaterInitState){
	if (HeaterSelect == HEATER_ONE){
        //initialize the pwm hardware module to control the heater
        //use timer 0 since FreeRTOS needs timer 1 to operate
        //use non-inverting mode + 60% duty cycle
        //use fast pwm + frequency = 20 since the period = 50ms > 1/50ms = 20hz
        PwmInit(&InternalHeaterInfo[HEATER_ONE].HeaterPwm,
                PWM_TIMER_0, NON_INVERTING_OUTPUT, 
                PWM_DUTY_CYCLE, FAST_PWM, PWM_FREQ);
	}
	else{
		//do nothing for now only handling one heater in the system
	}
	InternalHeaterInfo[HeaterSelect].HeaterState = HeaterInitState;
}

/************************************************************************/
/* HeaterSetState: Function sets the state of the targeted heater       */
/* Params:                                                              */
/* Input = HeaterSelect = Defines which heater to initialize            */
/* Input = HeaterState = Defines the needed state for a targeted heater */
/* Output= NON                                                          */
/************************************************************************/
void HeaterSetState(HeaterSelectT HeaterSelect, HeaterStateT HeaterState){
	InternalHeaterInfo[HeaterSelect].HeaterState = HeaterState;
}

/**************************************************************************/
/* HeaterGetState: Function gets the current state of the targeted heater */
/* Params:                                                                */
/* Input = HeaterSelect = Defines which heater to get it's state          */
/* Output= HeaterStateT = returns the state of the targeted heater        */
/**************************************************************************/
HeaterStateT HeaterGetState(HeaterSelectT HeaterSelect){
	return InternalHeaterInfo[HeaterSelect].HeaterState;
}

/***************************************************************************/
/* HeaterUpdate: Function updates the system state of all the heaters         */
/* Task: Perform the main module task by activating the hardware as needed */
/* Params:                                                                 */
/* Input = NON                                                             */
/* Output= NON                                                             */
/***************************************************************************/
void HeaterUpdate(void){
	if (InternalHeaterInfo[HEATER_ONE].HeaterState == HEATER_ON){
        PwmRun(&InternalHeaterInfo[HEATER_ONE].HeaterPwm);
	}
	else{
        PwmStop(&InternalHeaterInfo[HEATER_ONE].HeaterPwm);
	}
}
