/*
 * Main.h
 *
 * Created: 7/14/2021 9:06:21 AM
 *  Author: ZeroX
 */ 
#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
//https://github.com/weston-embedded?q=uC-&type=&language=
//FREE-RTOS and its Configurations
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
//HW Drivers

#include "Display.h" //done
#include "Heater.h"  //done
#include "Lamp.h"  //done
#include "Motor.h"  //done
#include "Phone.h" //done
#include "KeyPadApp.h" //done
#include "WeightSensor.h" //done
#include "DoorSensor.h" //done
#include "Buttons.h" //done 

void SysTimerCallback();

void systemInit();


#endif /* MAIN_H_ */