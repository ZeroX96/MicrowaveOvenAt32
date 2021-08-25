/*
 * BuzzApp.c
 *
 * Created: 4/16/2020 2:53:11 PM
 *  Author: ZeroX96
 */ 
#include "Buzzer.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct{
    BuzzStateT BuzzStateObj;
    uint32_t   BuzzDuration;
}BuzzT;
/***************************************************************************/
/* An internal Array to hold the system Buzzers states and informations    */
/* BUZZERS_NUM defines the number of the Buzzers required in the project   */
/***************************************************************************/
static BuzzT InternalBuzzerStates[BUZZERS_NUM];

/*******************************************************************************/
/* BuzzInit: Function initializes the hardware for the system Buzzers          */
/* Params:                                                                     */
/* Input = BuzzSelect = Defines which Buzzer to initialize                     */
/* Input = BuzzInitState = Defines the initial state for the targeted Buzzer   */
/* Output= NON                                                                 */
/*******************************************************************************/
void BuzzInit(BuzzSelectT BuzzSelect, BuzzStateT BuzzInitState){
	if (BuzzSelect == BUZZ_ONE){
    	GpioInitPin(BUZZ_ONE_BASE, BUZZ_ONE_PIN, PIN_OUT);
	}
	else{
    	//do nothing for now
	}
    //Store the buzzer state into the internal array
	InternalBuzzerStates[BuzzSelect].BuzzStateObj = BuzzInitState;
}

/************************************************************************/
/* BuzzSetState: Function sets the state of the targeted Buzzer         */
/* Params:                                                              */
/* Input = LampSelect = Defines which Buzzer to initialize              */
/* Input = LampState = Defines the needed state for a targeted Buzzer   */
/* Input = Duration = Defines the needed duration the buzzer will be ON */
/* Output= NON                                                          */
/************************************************************************/
void BuzzSetState(BuzzSelectT BuzzSelect, BuzzStateT BuzzState, int16_t Duration){
    //Store the buzzer state into the internal array
    InternalBuzzerStates[BuzzSelect].BuzzStateObj = BuzzState;
    //store the duration needed for that specific buzzer
    InternalBuzzerStates[BuzzSelect].BuzzDuration = Duration + BUZZ_SAFE_GUARD;
}

/***************************************************************************/
/* BuzzUpdate: Function updates the system state of all the buzzers         */
/* Task: Perform the main module task by activating the hardware as needed */
/* Params:                                                                 */
/* Input = NON                                                             */
/* Output= NON                                                             */
/***************************************************************************/
void BuzzUpdate(void ){
    uint8_t iter = 0;
    for (iter = 0; iter < BUZZERS_NUM; iter++){
        if (InternalBuzzerStates[iter].BuzzStateObj == BUZZ_ON){
            
            InternalBuzzerStates[iter].BuzzDuration -= SYS_TICK_PERIOD; //period of buzzer?
            
            if (InternalBuzzerStates[iter].BuzzDuration > BUZZ_SAFE_GUARD){
                
                GpioWritePin(BUZZ_ONE_BASE,BUZZ_ONE_PIN,PIN_HIGH);
            } 
            else if(InternalBuzzerStates[iter].BuzzDuration < BUZZ_SAFE_GUARD){
                //change the buzzer state back to the OFF state and turn-off the buzzer
                InternalBuzzerStates[iter].BuzzStateObj = BUZZ_OFF;
                GpioWritePin(BUZZ_ONE_BASE,BUZZ_ONE_PIN,PIN_LOW);
            }
            else{
                //Do-Nothing
            }
        } 
        else{
        	//Do-Nothing
        }
    }
}
