/*
 * MicroWaveGarmentIO.c
 *
 * Created: 8/20/2021 7:19:31 PM
 * Author : ZeroX96
 */ 
#include "Microwave.h"

static MicrowaveStateT InternalMicrowaveState;

/*******************************************************************************/
/* MicroWaveInitState: Function initializes the the system State               */
/* Params:                                                                     */
/* Input = State = Defines initial state for the system                        */
/* Output= NON                                                                 */
/*******************************************************************************/
void MicroWaveInitState(MicrowaveStateT State){
    InternalMicrowaveState = State;
}

/*******************************************************************************/
/* MicroWaveSetState: Function sets the state of the System                    */
/* Params:                                                                     */
/* Input = State = Defines initial state for the system                        */
/* Output= NON                                                                 */
/*******************************************************************************/
void MicroWaveSetState(MicrowaveStateT State){
    InternalMicrowaveState = State;
}

/*******************************************************************************/
/* MicroWaveGetState: Function gets the state of the System                    */
/* Params:                                                                     */
/* Input= NON                                                                  */
/* Output = State = returns the current state of the system                    */
/*******************************************************************************/
MicrowaveStateT MicroWaveGetState(void ){
    return InternalMicrowaveState;
}


/*********************************************************************************/
/*-TaskOutputsUpdate: Task to handle the state and the operation of the output   */
/*                    Modules including the Lamp, Heater, and the Buzzer         */
/*-Task Operation: Calls the three output modules functions to update the output */
/*-Task Period: 10 ms so the delay is 2 sys-ticks since every tick is 5ms each   */
/*-Params:                                                                       */
/*-Input  = NON                                                                  */
/*-Output = NON                                                                  */
/*********************************************************************************/
void TaskOutputsUpdate(void* VoidPtr){
    
    //data variables to handle the delay with accurate periods
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 2;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    for( ;; ){
        HeaterUpdate();
        LampUpdate();
        BuzzUpdate();
        
        //sleep for the next turn, Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
    /* Tasks must not attempt to return else, Delete */
    vTaskDelete( NULL );
}


/**********************************************************************************/
/*-TaskTimeUpdate: Task to handle the state and the operation of the Timer module */
/*--------------------------------------------------------------------------------*/
/*-Task Operation: Calls the time update modules function and then, checks the    */
/*                 current system state and if it's MICROWAVE_COCKING_DONE, makes */
/*                 buzzer beebs 2-times 100ms on and 100ms off each               */
/*-Task Period: 1000 ms so the delay is 200 sys-ticks since every tick is 5ms     */
/*-Params:                                                                        */
/*-Input  = NON                                                                   */
/*-Output = NON                                                                   */
/**********************************************************************************/
void TaskTimeUpdate(void* VoidPtr){
    
    //data variables to handle the delay with accurate periods
    static MicrowaveStateT uwaveStateTemp = MICROWAVE_COCKING_STARTUP;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 200;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    for( ;; ){
        
        //update the time
        TimeUpdate();
        
        uwaveStateTemp = MicroWaveGetState();
        
        if (uwaveStateTemp == MICROWAVE_COCKING_DONE){
            //set lamp and heater off
            LampSetState(LAMP_ONE, LAMP_OFF);
            HeaterSetState(HEATER_ONE, HEATER_OFF);
            //Beeb twice when system is done, then switch to off state
            BuzzSetState(BUZZ_ONE, BUZZ_ON, 100);
            vTaskDelay(40); //sleep for 200ms
            BuzzSetState(BUZZ_ONE, BUZZ_ON, 100);
            vTaskDelay(40); //sleep again for 200ms
            //now switch to off state
            MicroWaveSetState(MICROWAVE_COCKING_OFF);
        } 
        else{
        	//Do-Nothing
    }
    
    //sleep for the next turn, Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }    
    /* Tasks must not attempt to return else, Delete */
    vTaskDelete( NULL );
}


/***********************************************************************************/
/*-TaskInputsUpdate: Task to handle the inputs to the system including all buttons */
/*---------------------------------------------------------------------------------*/
/*-Task Operation: gets the current inputs states using modules functions then     */
/*                 handles the operation and mode of the system accordingly        */
/*                 as defined in the project document.                             */
/*-Task Period: 20 ms so the delay is 4 sys-ticks since every tick is 5ms          */
/*-Params:                                                                         */
/*-Input  = NON                                                                    */
/*-Output = NON                                                                    */
/***********************************************************************************/
void TaskInputsUpdate(void* VoidPtr){
    
    //state-holders to get the current state of the buttons and the door to decide upon
    static BtnStateT       BtnStartTemp   = BTN_RELEASED;
    static BtnStateT       BtnPlusTemp    = BTN_RELEASED;
    static BtnStateT       BtnMinusTemp   = BTN_RELEASED;
    static DoorStateT      DoorStateTemp  = BTN_RELEASED;
    static MicrowaveStateT uwaveStateTemp = MICROWAVE_COCKING_STARTUP;
    static uint16_t        TimeValueTemp  = 0;

    //data variables to handle the delay with accurate periods
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 4;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
        
    for( ;; ){
        
        //update the buttons and the door states
        BtnUpdate();
        
        //get the new system-inputs states
        BtnStartTemp   = BtnGetState(BTN_START);
        BtnPlusTemp    = BtnGetState(BTN_PLUS);
        BtnMinusTemp   = BtnGetState(BTN_MINUS);
        DoorStateTemp  = DoorSensGetState();
        uwaveStateTemp = MicroWaveGetState();
        TimeValueTemp  = TimeGetTime();
        //perform task operation checking for start command
        if (BtnStartTemp == BTN_PRESSED){
            
            //after every correct press, the buzzer beebs for 100ms
            BuzzSetState(BUZZ_ONE , BUZZ_ON, 100);
            
            if( (DoorStateTemp == BTN_PRESSED) && (uwaveStateTemp == MICROWAVE_COCKING_OFF) &&
                (TimeValueTemp != 0) ){
                //enable the cocking, all settings are ok
                MicroWaveSetState(MICROWAVE_COCKING_RUNNING);
                //set the lamp and the heater on
                LampSetState(LAMP_ONE, LAMP_ON);
                HeaterSetState(HEATER_ONE, HEATER_ON);
                TimeResumeTime();
            } 
            else if ( (DoorStateTemp == BTN_PRESSED) && (uwaveStateTemp == MICROWAVE_COCKING_RUNNING) ){
                //if door is closed, system running, and start is clicked, turn off the system
                MicroWaveSetState(MICROWAVE_COCKING_OFF); // turn-off the system, stop the cocking
                LampSetState(LAMP_ONE, LAMP_OFF);
                HeaterSetState(HEATER_ONE, HEATER_OFF);
                TimePauseTime();
            }
            else if ( (DoorStateTemp == BTN_RELEASED) && (uwaveStateTemp == MICROWAVE_COCKING_PAUSED) ){
            	//if door is opened, system paused, and start is clicked, turn off the system
            	MicroWaveSetState(MICROWAVE_COCKING_OFF); // turn-off the system, stop the cocking
            	LampSetState(LAMP_ONE, LAMP_OFF);
            	HeaterSetState(HEATER_ONE, HEATER_OFF);
                TimeSetTime(0);  //zero the timing
                TimePauseTime();
            }
        }
        else{
        	//Do-Nothing
        }
        
        //perform task operation checking for PLUS command
        if (BtnPlusTemp == BTN_PRESSED){
            
            //after every correct press, the buzzer beebs for 100ms
            BuzzSetState(BUZZ_ONE , BUZZ_ON, 100);
            //time increment
            TimeIncTime();
        }
        else{
            //Do-Nothing
        }
        
        //perform task operation checking for MINUS command
        if (BtnMinusTemp == BTN_PRESSED){
            
            //after every correct press, the buzzer beebs for 100ms
            BuzzSetState(BUZZ_ONE , BUZZ_ON, 100);
            //time decrement if only stooped, else neglect
            if (uwaveStateTemp == MICROWAVE_COCKING_OFF){
                TimeDecTime();
            } 
            else{
            	//Do-Nothing
            }
        }
        else{
            //Do-Nothing
        }
        
        //perform task operation checking for DOOR State
        if (DoorStateTemp == BTN_RELEASED){
            //check the current system state
            if (uwaveStateTemp == MICROWAVE_COCKING_OFF){
                //if door is opened while the heating is off, just turn-on the lamp
                LampSetState(LAMP_ONE, LAMP_ON);
            } 
            else if (uwaveStateTemp == MICROWAVE_COCKING_RUNNING){
                //if the door is opened while the heating is on, turn off the heater first and then turn on the lamp
                HeaterSetState(HEATER_ONE, HEATER_OFF);
                LampSetState(LAMP_ONE, LAMP_ON);
                //set the state to be paused and pause the timer
                MicroWaveSetState(MICROWAVE_COCKING_PAUSED);
                TimePauseTime();
            }
            else{
            	//Do-Nothing
            }
        }
        else{  //the door is closed
            //if the heating was paused, resume the heating operation
            if (uwaveStateTemp == MICROWAVE_COCKING_PAUSED){
                HeaterSetState(HEATER_ONE, HEATER_ON);
                MicroWaveSetState(MICROWAVE_COCKING_RUNNING);
                TimeResumeTime();
            } 
            else if (uwaveStateTemp == MICROWAVE_COCKING_OFF){
                //if door is closed while the heating is off, just turn-off the lamp
                LampSetState(LAMP_ONE, LAMP_OFF);
            }
            else{
            	//Do-Nothing
            }
        }
        
        //sleep for the next turn, Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
    
    /* Tasks must not attempt to return else, Delete */
    vTaskDelete( NULL );
}

/************************************************************************************/
/*-TaskDisplayUpdate: Task to handle the outputs on the display                     */
/*----------------------------------------------------------------------------------*/
/*-Task Operation: handle the outputs on the display according to the system states */
/*                 and internal values as defined in the project document file.     */
/*-Task Period: 5 ms so the delay is 1 sys-ticks since every tick is 5ms            */
/*-Params:                                                                          */
/*-Input  = NON                                                                     */
/*-Output = NON                                                                     */
/************************************************************************************/
void TaskDisplayUpdate(void* VoidPtr){
    
    //iterator used to synchronize the blinking when the system is not running
    //the iterator will count for 60-times which will achieve the 300ms ON-State
    //then this task will go to sleeping for 300ms as required
    static uint8_t iterator = 0;
    //display_id used to multiplex the displays to be used in comparison
    static uint8_t DisplayId = 0;
    //State variable to get the system state
    static MicrowaveStateT State = MICROWAVE_COCKING_STARTUP;
    
    //data variables to handle the delay with accurate periods
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    for( ;; ){
        
        State = MicroWaveGetState(); // get the current system state
        
        if (MICROWAVE_COCKING_STARTUP == State){
            BuzzSetState(BUZZ_ONE, BUZZ_ON, 100); //when startup, system beebs for 100ms
            TimeSetTime(0);
            TimePauseTime();
            DispUpdate(DisplayId);
            DisplayId++; //increment the id till reaching it's max, reset it.
            if (DisplayId == MUX_NUMBER_OF_DISPS){
                DisplayId = 0;
            }
            MicroWaveSetState(MICROWAVE_COCKING_OFF);
        }
        else if (MICROWAVE_COCKING_OFF == State){
            
            if (TimeGetTime() != 0){ //wait for the first change from zeros as required
                //once the time is changed, display and perform the blinking
                iterator++;
                if (iterator < DISPLAY_TICK_COUNT){
                    DispUpdate(DisplayId);
                    DisplayId++; //increment the id till reaching it's max, reset it.
                    if (DisplayId == MUX_NUMBER_OF_DISPS){
                        DisplayId = 0;
                    }
                }
                else{
                    iterator = 0;
                    DisplayId = 0;
                    DispUpdate(DISPLAY_OUTPUT_OFF);
                    vTaskDelay(DISPLAY_TICK_COUNT); //sleep/don't represent for 60-tick = 300ms as needed
                }
            }
            else{ //if the time-setting is still zeros, just preview them on the display
                
                DispUpdate(DisplayId);
                DisplayId++; //increment the id till reaching it's max, reset it.
                if (DisplayId == MUX_NUMBER_OF_DISPS){
                    DisplayId = 0;
                }
                
            }
        }
        else if( (MICROWAVE_COCKING_RUNNING == State) || (MICROWAVE_COCKING_PAUSED == State) ){
            //if the system is running, just present the data continuously on the displays
            DispUpdate(DisplayId);
            DisplayId++; //increment the id till reaching it's max, reset it.
            if (DisplayId == MUX_NUMBER_OF_DISPS){
                DisplayId = 0;
            }
        }
        else if(MICROWAVE_COCKING_DONE == State){
            
            // now that, the cocking is done, clear the display, beeb, and goto off state
            iterator = 0;
            DisplayId = 0;
            DispUpdate(DISPLAY_COCKING_DONE);
        }
        else{
            //Do-Nothing
        }
        
        //sleep for the next turn, Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
    /* Tasks must not attempt to return else, Delete */
    vTaskDelete( NULL );
}