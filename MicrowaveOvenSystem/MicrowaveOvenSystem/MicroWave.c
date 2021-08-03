/*
 * MicrowaveOvenSystem.c
 *
 * Created: 7/14/2021 8:52:51 AM
 * Author : ZeroX
 */ 
#include "MicroWave.h"
#include "SysMain.h"


//system task handlers
TaskHandle_t SysInHandler;
TaskHandle_t SysOutHandler;
TaskHandle_t SysMainHandler;
void SystemInputUpdate(void* VoidPtr);
void SystemOutputUpdate(void* VoidPtr);
void SystemMain(void* VoidPtr);

int main(void){

    //initialization
    systemInit();
	//create tasks
	//System Input Update Task functions >> 5 = max priority in sys
	xTaskCreate(SystemInputUpdate, "SysInUpdate", configMINIMAL_STACK_SIZE, NULL, 5, &SysInHandler);
	//System Output Update Task Functions >> 4 
	xTaskCreate(SystemOutputUpdate, "SysOutUpdate", configMINIMAL_STACK_SIZE, NULL, 4, &SysOutHandler);
	//task send data and current state to the phone
	xTaskCreate(SystemMain, "SysMain", configMINIMAL_STACK_SIZE, NULL, 3, &SysMainHandler);
    //task cock
    while (1){
      //update
        //input 
        // time from the user
        // button start - pause - stop
        //process
        //show the result
        //turn on - of devices
        //calculate the remaining time
        //output
        //turn on - off devices
        //turn on - off the heater - the lamp - the motor
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

void SystemInputUpdate(void* VoidPtr){
	for( ;; ){
		//-- Task application code here. --
		BtnUpdate();
		DoorSensUpdate();
		WeightSensUpdate();
		KeypadUpdate();
		PhoneUpdateRx();
		PhoneUpdateTx();
	}
	/* Tasks must not attempt to return else, delete */
	vTaskDelete( NULL );
}

void SystemOutputUpdate(void* VoidPtr){
	for( ;; ){
		DisplayUpdate();
		HeaterUpdate();
		LampUpdate();
		MotorUpdate();
	}
	/* Tasks must not attempt to return else, Delete */
	vTaskDelete( NULL );
}


void SystemMain(void* VoidPtr){
    for( ;; ){
        SysMainApp();
    }
    /* Tasks must not attempt to return else, Delete */
    vTaskDelete( NULL );
}