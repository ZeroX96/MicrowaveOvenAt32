/*
 * Buttons.h
 *
 * Created: 8/20/2021 7:11:28 PM
 *  Author: ZeroX96
 */ 

#ifndef BUTTONS_H_
#define BUTTONS_H_

//includes
#include <stdint.h>
#include "Gpio.h"
#include "main.h"

//the period per which the scanning should happen
#define BTNS_PERIOD         (20)

//define the number of buttons in the system
#define BTNS_NUM            (4)

//define the number of samples needed to update the state
#define SAMPLES_NUM         (2)

/************************************************************************/
/* BtnStateT, a defined data type for the states of the buttons         */
/************************************************************************/
typedef enum{
	BTN_RELEASED,
	BTN_PRE_PRESSED,
	BTN_PRESSED,
	BTN_PRE_RELEASED
}BtnStateT;

/************************************************************************/
/* BtnSelectT, a defined data type for the possible buttons in the sys  */
/************************************************************************/
typedef enum{
	BTN_START,
	BTN_PLUS,
	BTN_MINUS,
	BTN_DOOR,
}BtnSelectT;

/* BtnInit: Function initializes the hardware for the system buttons        */
void BtnInit(BtnSelectT BtnSelect, BtnStateT BtnInitState);

/* BtnGetState: Function gets the current state of the targeted button  */
BtnStateT BtnGetState(BtnSelectT BtnSelect);

/* BtnUpdate: Function updates the current state of all the buttons     */
void BtnUpdate(void );

#endif /* BUTTONS_H_ */