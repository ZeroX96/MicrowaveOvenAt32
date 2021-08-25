/*
 * Microwave.h
 *
 * Created: 8/21/2021 11:15:41 PM
 *  Author: ZeroX96
 */ 


#ifndef MICROWAVE_H_
#define MICROWAVE_H_

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"
#include "Lamp.h"
#include "Buzzer.h"
#include "Buttons.h"
#include "Disp.h"
#include "Time.h"
#include "DoorSensor.h"
#include "Heater.h"

/* MicroWaveInitState: Function initializes the the system State               */
void MicroWaveInitState(MicrowaveStateT State);

/* MicroWaveSetState: Function sets the state of the System                    */
void MicroWaveSetState(MicrowaveStateT State);

/* MicroWaveGetState: Function gets the state of the System                    */
MicrowaveStateT MicroWaveGetState(void );

/*-TaskOutputsUpdate: Task to handle the state and the operation of the output   */
/*                    Modules including the Lamp, Heater, and the Buzzer         */
void TaskOutputsUpdate(void* VoidPtr);

/*-TaskTimeUpdate: Task to handle the state and the operation of the Timer module */
void TaskTimeUpdate(void* VoidPtr);

/*-TaskInputsUpdate: Task to handle the inputs to the system including all buttons */
void TaskInputsUpdate(void* VoidPtr);

/*-TaskDisplayUpdate: Task to handle the outputs on the display                     */
void TaskDisplayUpdate(void* VoidPtr);

#endif /* MICROWAVE_H_ */