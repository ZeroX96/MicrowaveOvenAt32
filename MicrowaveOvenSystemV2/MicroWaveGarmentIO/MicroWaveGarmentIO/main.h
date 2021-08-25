/*
 *  File    : main.h
 *
 *  Author  : MahmoudSaad.ZeroX96
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/ZeroX96
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 */
/**************************************************************************/
/* Main.h file includes and defines the Hardware and Software Information */
/*         that are related to the specific micro-controller I'm using    */
/**************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include "FreeRTOSConfig.h"

typedef enum{
    MICROWAVE_COCKING_STARTUP,
    MICROWAVE_COCKING_OFF,
    MICROWAVE_COCKING_RUNNING,
    MICROWAVE_COCKING_PAUSED,
    MICROWAVE_COCKING_DONE,
}MicrowaveStateT;

/*************************************************************************/
/* Defining the Buttons locations connected to the micro-controller Pins */
/*************************************************************************/
//buttons locations
#define BTN_PLUS_BASE       BASE_A
#define BTN_PLUS_PIN        PIN_0

#define BTN_MINUS_BASE      BASE_A
#define BTN_MINUS_PIN       PIN_1

#define BTN_DOOR_BASE       BASE_A
#define BTN_DOOR_PIN        PIN_2

#define BTN_START_BASE      BASE_A
#define BTN_START_PIN       PIN_3

/************************************************************************/
/* Defining the Heater locations connected to the micro-controller Pins */
/************************************************************************/
#define HEATER_ONE_BASE BASE_B
#define HEATER_ONE_PIN  PIN_3

/************************************************************************/
/* Defining the Lamp locations connected to the micro-controller Pins   */
/************************************************************************/
#define LAMP_ONE_BASE BASE_A
#define LAMP_ONE_PIN  PIN_7

/************************************************************************/
/* Defining the Buzzer locations connected to the micro-controller Pins */
/************************************************************************/
#define BUZZ_ONE_BASE	BASE_A
#define BUZZ_ONE_PIN	PIN_6

/************************************************************************/
/* Define the Level that corresponds to the current micro-controller    */
/************************************************************************/
#define BTN_LEVEL_PRESSED   (1)
#define BTN_LEVEL_RELEASED  (0)

/************************************************************************/
/* SYS_TICK_PERIOD is defined in the FreeRTOS Config File as (5ms)      */
 /* SYS_TICK_PERIOD     (1 / configTICK_RATE_HZ)  //5ms                 */
/************************************************************************/
#define SYS_TICK_PERIOD     (5)

/************************************************************************/
/* Define the Seven Segment Display Data and Info                       */
/************************************************************************/
#define DISPLAY_DATA_BASE       BASE_C
#define DISPLAY_CTRL_BASE       BASE_D
#define DIPSLAY_MODULE_TYPE     DISP_COMMON_CATHODE
#define DISPLAY_CTRL_START_BIT  (0)
#define MUX_NUMBER_OF_DISPS     (4)
//      Display_REQUIRED_PERIOD (3/10) //300ms as define in the document
//      DISPLAY_TICK_COUNT      (Display_REQUIRED_PERIOD / SYS_TICK_PERIOD) //60-ticks
#define DISPLAY_TICK_COUNT      (60) //60-ticks
#define DISPLAY_OUTPUT_OFF      (4)
#define DISPLAY_COCKING_DONE    (5) //used in the cocking done state to show zero on all the displays

#endif /* MAIN_H_ */
