/*
 * Buttons.c
 *
 * Created: 7/22/2021 3:25:59 PM
 *  Author: ZeroX96
 */ 
// 
// /* SW voltage level */
// #define BTN_PRESSED_LEVEL        (0)
// #define BTN_RELEASED_LEVEL       (1)
#include "Buttons.h"
typedef struct{
	uint8_t	  BtnSamples[SAMPLES_NUM];
	BtnStateT BtnState;
}BtnInfo;

static BtnInfo BtnsInfo[BTNS_NUM];

void BtnInit(BtnSelectT BtnSelect, BtnStateT BtnInitState){
	if (BtnSelect == BTN_START){
		GpioInitPin(BTN_START_BASE,BTN_START_PIN,PIN_IN);
	}
	else if (BtnSelect == BTN_CANCEL){
		GpioInitPin(BTN_CANCEL_BASE,BTN_CANCEL_PIN,PIN_IN);
	}
	else if (BtnSelect == BTN_WEIGHT){
		GpioInitPin(BTN_WEIGHT_BASE,BTN_WEIGHT_PIN,PIN_IN);
	}
	else{  //btn door
		GpioInitPin(BTN_DOOR_BASE,BTN_DOOR_PIN,PIN_IN);
	}
	BtnsInfo[BtnSelect].BtnState = BtnInitState;
	//set the samples // if need to handle the variable num of samples just use a loop here 
	BtnsInfo[BtnSelect].BtnSamples[0] = BtnInitState;
	BtnsInfo[BtnSelect].BtnSamples[1] = BtnInitState;
}
BtnStateT BtnGetState(BtnSelectT BtnSelect){
	return BtnsInfo[BtnSelect].BtnState;
}
void BtnUpdate(void ){
	static uint32_t UpdateSynch = 0; //used to synchronize the func with the period
	static uint8_t iter = 0;
	UpdateSynch += SYS_TICK_PERIOD;
	
	if (UpdateSynch < BTNS_PERIOD){
		return ;
	}
	UpdateSynch = 0;
	for (iter = BTN_START_PIN; iter < BTNS_NUM; iter++){
		//save the old sample
		BtnsInfo[iter].BtnSamples[0] = BtnsInfo[iter].BtnSamples[1];
		
		//for the start btn
		if (iter == BTN_START_PIN)
		{
			//get another sample
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_START_BASE, BTN_START_PIN);
		}
		else if (iter == BTN_CANCEL_PIN){
			//get another sample
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_CANCEL_BASE, BTN_CANCEL_PIN);
		}
		else if (iter == BTN_WEIGHT_PIN){
			//get another sample
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_WEIGHT_BASE, BTN_WEIGHT_PIN);
		}
		else if (iter == BTN_DOOR_PIN){
			//get another sample
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_DOOR_BASE, BTN_DOOR_PIN);
		}
		else{
			//error
			while (1); //not a production solution
		}
		//now check the states
		switch (BtnsInfo[iter].BtnState)
		{
			case BTN_RELEASED:
				if ((BtnsInfo[iter].BtnSamples[0] == BTN_LEVEL_PRESSED) && 
				    (BtnsInfo[iter].BtnSamples[1] == BTN_LEVEL_PRESSED) ){
						BtnsInfo[iter].BtnState = BTN_PRE_PRESSED;
				} 
				else{
					//donothing
				}
			  break;
			case BTN_PRE_PRESSED:
				if (BtnsInfo[iter].BtnSamples[1] == BTN_LEVEL_PRESSED){
					BtnsInfo[iter].BtnState = BTN_PRESSED;
				}
				else{
					BtnsInfo[iter].BtnState = BTN_RELEASED;					
				}
			  break;
			case BTN_PRESSED:
				if ((BtnsInfo[iter].BtnSamples[0] == BTN_LEVEL_RELEASED) &&
				(BtnsInfo[iter].BtnSamples[1] == BTN_LEVEL_RELEASED) ){
					BtnsInfo[iter].BtnState = BTN_PRE_RELEASED;
				}
				else{
					//donothing
				}
			  break;
			case BTN_PRE_RELEASED:
				if (BtnsInfo[iter].BtnSamples[1] == BTN_LEVEL_RELEASED){
					BtnsInfo[iter].BtnState = BTN_RELEASED;
				}
				else{
					BtnsInfo[iter].BtnState = BTN_PRESSED;
				}
			  break;
			default:
			  break;
		}
	}
}