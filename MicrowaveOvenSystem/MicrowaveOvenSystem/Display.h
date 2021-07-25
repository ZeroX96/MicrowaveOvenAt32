/*
 * Display.h
 *
 * Created: 7/22/2021 9:02:50 AM
 *  Author: Mosta
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <stdlib.h>
#include "Lcd.h"

typedef enum{
	DISPLAY_SETTING_TIME,
	DISPLAY_RUNING,
}DisplayStateT;

//called in the init
void DisplayInit(void );
//called in the loop
void DisplaySetTime(uint8_t Minutes, uint8_t Seconds);
//called in the isr
void DisplayUpdate(void );





#endif /* DISPLAY_H_ */