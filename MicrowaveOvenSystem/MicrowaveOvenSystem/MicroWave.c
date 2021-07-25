/*
 * MicrowaveOvenSystem.c
 *
 * Created: 7/14/2021 8:52:51 AM
 * Author : ZeroX
 */ 
#include "MicroWave.h"

int main(void){
    //initialization
    systemInit();
	//create tasks
	xTaskCreate
	//task send data and current state to the phone
    //task cock
    while (1){
      //update
        //input 
        
        //process
        
        //output
        vTaskStartScheduler();
    }
    return 0;
}


void systemInit(){
	
	DisplayInit();
	HeaterInit(HEATER_ONE, HEATER_OFF);
	LampInit(LAMP_ONE, LAMP_OFF);
	MotorInit(MOTOR_ONE, MOTOR_STOPPED);
	PhoneInit();
	KeypadAppInit();
	WeightSensInit();
	DoorSensInit();
	BtnInit(BTN_START, BTN_RELEASED);
	BtnInit(BTN_CANCEL, BTN_RELEASED);
	
}
void vATaskFunction( void *pvParameters );
void vATaskFunction( void *pvParameters ){
	        for( ;; )
        {
            //-- Task application code here. --
        }

        /* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
        vTaskDelete( NULL );
}