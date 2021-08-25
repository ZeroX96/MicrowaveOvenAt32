/*
 * Buttons.h
 *
 * Created: 7/22/2021 9:05:18 AM
 *  Author: ZeroX96
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_
#include <stdint.h>
#include "Gpio.h"
//this is defined in the sys-timer 
#define SYS_TICK_PERIOD 1
//the period per which the 
#define BTNS_PERIOD 20
#define BTNS_NUM (4)
#define SAMPLES_NUM (2)
/* Btn_Update period */
#define BTN_PERIOD_MS   (30)
//the sample levels
#define BTN_LEVEL_PRESSED  (1)
#define BTN_LEVEL_RELEASED (0)
//buttons locations
#define BTN_START_BASE BASE_A
#define BTN_START_PIN  PIN_0
#define BTN_CANCEL_BASE BASE_A
#define BTN_CANCEL_PIN  PIN_1
#define BTN_WEIGHT_BASE BASE_A
#define BTN_WEIGHT_PIN  PIN_2
#define BTN_DOOR_BASE BASE_A
#define BTN_DOOR_PIN  PIN_3

typedef enum{
	BTN_RELEASED,
	BTN_PRE_PRESSED,
	BTN_PRESSED,
	BTN_PRE_RELEASED
}BtnStateT;

typedef enum{
	BTN_START,
	BTN_CANCEL,
	BTN_WEIGHT,
	BTN_DOOR,
}BtnSelectT;

void BtnInit(BtnSelectT BtnSelect, BtnStateT BtnInitState);
BtnStateT BtnGetState(BtnSelectT BtnSelect);
void BtnUpdate(void );




#endif /* BUTTONS_H_ */