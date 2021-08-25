/*
 * Time.c
 *
 * Created: 8/21/2021 9:35:09 PM
 *  Author: ZeroX96
 */ 
#include "Time.h"
typedef enum{
    TIME_PAUSED,
    TIME_RESUMED
}TimerStateT;
/*******************************************************************************/
/* An internal variable to hold the system remaining seconds to finish the job */
/*******************************************************************************/
static uint16_t InternalTimerValue;

static TimerStateT InternalTimerState;

/*******************************************************************************/
/* TimeInit: Function initializes the timer variable to zero                   */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeInit(void){
    
    InternalTimerValue = 0;  
    InternalTimerState = TIME_PAUSED;  
}

/*******************************************************************************/
/* TimeSetTime: Function updates the timer value as needed                     */
/* Params:                                                                     */
/* Input = TimeVal = the required value to be set                              */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeSetTime(uint16_t TimeVal){
    //store the received data in the internal variable
    InternalTimerValue = TimeVal;
}

/*******************************************************************************/
/* TimeIncTime: Function increments the timer variable with step of 5 s        */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeIncTime(void){
    
    if (InternalTimerValue != TIME_MAX_VAL){
        
        InternalTimerValue += TIME_STEP_VAL;
    } 
    else{
    	//Do-Nothing
    }
}

/*******************************************************************************/
/* TimeDecTime: Function decrements the timer variable with step of 5 s        */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeDecTime(void){
    
    if(InternalTimerValue != 0){
        
        InternalTimerValue -= TIME_STEP_VAL;
    }
    else{
        //do nothing
    }
}

/*******************************************************************************/
/* TimePauseTime: Function pauses the timer variable and module operation      */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimePauseTime(void){
    
    InternalTimerState = TIME_PAUSED;
}

/*******************************************************************************/
/* TimeResumeTime: Function resumes the timer variable and module operation    */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeResumeTime(void){
    
    InternalTimerState = TIME_RESUMED;
}

/*******************************************************************************/
/* TimeGetTime: Function returns the timer variable current value              */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= uint16_t the value of the current time variable                     */
/*******************************************************************************/
uint16_t TimeGetTime(void){
    
    return InternalTimerValue;
}

/*******************************************************************************/
/* TimeUpdate: Function updates the timer variable current value  and handles  */
/*             the system mode of cocking when cocking is done                 */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void TimeUpdate(void){
    if (InternalTimerState == TIME_RESUMED){
        
        if (InternalTimerValue != 0){
            InternalTimerValue--;
        }
        MicrowaveStateT State = MicroWaveGetState();
        if( (InternalTimerValue == 0) && (State == MICROWAVE_COCKING_RUNNING) ){
            MicroWaveSetState( MICROWAVE_COCKING_DONE );
        }
    } 
    else{
    	//Do-Nothing
    }
}

