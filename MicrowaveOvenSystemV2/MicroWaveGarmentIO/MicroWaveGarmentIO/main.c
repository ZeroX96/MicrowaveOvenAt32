/*
 * main.c
 *
 * Created: 8/22/2021 12:12:44 AM
 *  Author: ZeroX96
 */ 
#include "Microwave.h"

void systemInit(void);

//system tasks handlers
TaskHandle_t OutputsUpdateHandler;
TaskHandle_t SysTimeUpdateHandler;
TaskHandle_t InputsUpdateHandler;
TaskHandle_t DisplayUpdateHandler;

int main(void)
{
    //initialization of the system
    systemInit();
    
    /* Replace with your application code */
    
    //create tasks
    //Task Display Update functions >> 5 = highest priority in the system with period = 5ms
    xTaskCreate(TaskDisplayUpdate, "DisplayUpdate", configMINIMAL_STACK_SIZE, NULL, 5, &DisplayUpdateHandler);
    //Task Outputs Update functions >> 4 = second highest priority in the system with period = 10ms
    xTaskCreate(TaskOutputsUpdate, "OutputsUpdate", configMINIMAL_STACK_SIZE, NULL, 4, &OutputsUpdateHandler);
    //Task Inputs Update functions  >> 3 = third highest priority in the system with period = 20ms
    xTaskCreate(TaskInputsUpdate,  "InputsUpdate",  configMINIMAL_STACK_SIZE, NULL, 3, &InputsUpdateHandler);
    //Task Time Update functions    >> 2 = lowest priority in the system with period = 1S
    xTaskCreate(TaskTimeUpdate,    "TimeUpdate",    configMINIMAL_STACK_SIZE, NULL, 2, &SysTimeUpdateHandler);
    
    //let the system begin!!!
    vTaskStartScheduler();
    while (1)
    {
        /*System Is Never Supposed To Come Here!!!!!*/
    }
}


/*******************************************************************************/
/* systemInit: Function initializes the hardware and software modules to be    */
/*                ready for usage for the whole system.                        */
/* initializes: Timer - Display - Buttons - Buzzer - Lamp - Heater - Door      */
/* Params:                                                                     */
/* Input = NON                                                                 */
/* Output= NON                                                                 */
/*******************************************************************************/
void systemInit(void){
    // initialize the timer module
    TimeInit();
    //initialize the display module
    DispInit();
    //initialize the Door sensor module
    DoorSensInit();
    //initialize the Lamp Module
    LampInit(LAMP_ONE, LAMP_OFF);
    //initialize the buzzer module
    BuzzInit(BUZZ_ONE, BUZZ_OFF);
    //initialize the heater module
    HeaterInit(HEATER_ONE, HEATER_OFF);
    //initialize the buttons
    BtnInit(BTN_MINUS, BTN_RELEASED);
    BtnInit(BTN_PLUS, BTN_RELEASED);
    BtnInit(BTN_START, BTN_RELEASED);
    //initialize the system
    MicroWaveInitState(MICROWAVE_COCKING_STARTUP);
}