# MicrowaveOvenAt32
An RTOS-based system implemented using the FreeRTOS Kernel on the Atmega-32. The Kernel Monitor and control the system tasks. The user selects the cooking needed time using his smart phone or a keypad.

![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWaveSim.png)

```c
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
```

![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWave%20-%201.png)



![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWave%20-%202.png)

![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWave%20-%203.png)

![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWave%20-%204.png)

![](https://github.com/ZeroX96/MicrowaveOvenAt32/blob/main/MicrowaveOvenSystemV2/MicroWave%20-%205.png)
