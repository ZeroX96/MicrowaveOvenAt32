/*
 * Buttons.c
 *
 * Created: 8/20/2021 7:12:40 PM
 *  Author: ZeroX96
 */ 

#include "Buttons.h"

/************************************************************************/
/* Buttons info including sampling and the current state                */
/************************************************************************/
typedef struct{
	uint8_t	  BtnSamples[SAMPLES_NUM];
	BtnStateT BtnState;
}BtnInfo;

/************************************************************************/
/* An internal Array to hold the system buttons states and informations */
/* BTNS_NUM defines the number of the buttons required in the project   */
/************************************************************************/
static BtnInfo BtnsInfo[BTNS_NUM];

/****************************************************************************/
/* BtnInit: Function initializes the hardware for the system buttons        */
/* Params:                                                                  */
/* Input = BtnSelect = Defines which button to initialize                   */
/* Input = BtnInitState = Defines the initial state for the targeted button */
/* Output= NON                                                              */
/****************************************************************************/
void BtnInit(BtnSelectT BtnSelect, BtnStateT BtnInitState){
    //initialize the hardware GPIOs as inputs for the required button
	if (BtnSelect == BTN_START){
		GpioInitPin(BTN_START_BASE,BTN_START_PIN,PIN_IN);
	}
	else if (BtnSelect == BTN_PLUS){
		GpioInitPin(BTN_PLUS_BASE,BTN_PLUS_PIN,PIN_IN);
	}
	else if (BtnSelect == BTN_MINUS){
		GpioInitPin(BTN_MINUS_BASE,BTN_MINUS_PIN,PIN_IN);
	}
	else if (BtnSelect == BTN_DOOR){
		GpioInitPin(BTN_DOOR_BASE,BTN_DOOR_PIN,PIN_IN);
	}
    else{
        //Do nothing - Report Error
    }
	BtnsInfo[BtnSelect].BtnState = BtnInitState;
	//set the samples // if need to handle the variable numb of samples just use a loop here 
	BtnsInfo[BtnSelect].BtnSamples[0] = BtnInitState;
	BtnsInfo[BtnSelect].BtnSamples[1] = BtnInitState;
}

/************************************************************************/
/* BtnGetState: Function gets the current state of the targeted button  */
/* Params:                                                              */
/* Input = BtnSelect = Defines which button to initialize               */
/* Output= BtnStateT = returns the state of the targeted button         */
/************************************************************************/
BtnStateT BtnGetState(BtnSelectT BtnSelect){
	return BtnsInfo[BtnSelect].BtnState;
}

/************************************************************************/
/* BtnUpdate: Function updates the current state of all the buttons     */
/* Params:                                                              */
/* Input = NON                                                          */
/* Output= NON                                                          */
/************************************************************************/
void BtnUpdate(void ){
	static uint32_t UpdateSynch = 0; //used to synchronize the func with the period
	static uint8_t iter = 0;         //used as internal iterator
    // wait till reaching the defined Buttons Period of 20ms
	UpdateSynch += SYS_TICK_PERIOD;
	
	if (UpdateSynch < BTNS_PERIOD){
		return ;
	}
	UpdateSynch = 0;
    
    // now that, it's synchronized, perform the operation
    //operation = loop on all the buttons and get a new sample and store it
	for (iter = BTN_START_PIN; iter < BTNS_NUM; iter++){
		//save the old sample
		BtnsInfo[iter].BtnSamples[0] = BtnsInfo[iter].BtnSamples[1];
		
		//get another sample for the system buttons
		if (iter == BTN_START_PIN){
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_START_BASE, BTN_START_PIN);
		}
		else if (iter == BTN_PLUS_PIN){
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_PLUS_BASE, BTN_PLUS_PIN);
		}
		else if (iter == BTN_MINUS_PIN){
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_MINUS_BASE, BTN_MINUS_PIN);
		}
		else if (iter == BTN_DOOR_PIN){
			BtnsInfo[iter].BtnSamples[1] = GpioReadPin(BTN_DOOR_BASE, BTN_DOOR_PIN);
		}
		else{
			//error
			//while (1); //not a production solution
		}
        
		//now check the states and update what is needed
		switch (BtnsInfo[iter].BtnState)
		{
			case BTN_RELEASED:
				if ((BtnsInfo[iter].BtnSamples[0] == BTN_LEVEL_PRESSED) && 
				    (BtnsInfo[iter].BtnSamples[1] == BTN_LEVEL_PRESSED) ){
						BtnsInfo[iter].BtnState = BTN_PRE_PRESSED;
				} 
				else{
					//do nothing
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
					//do nothing
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
                     //do-nothing
			  break;
		}
	}
}