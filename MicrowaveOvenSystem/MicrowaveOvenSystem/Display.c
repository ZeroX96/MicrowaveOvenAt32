/*
 * Display.c
 *
 * Created: 7/22/2021 9:08:59 AM
 *  Author: ZeroX96
 * -2.2.0.295
 */ 

#include "Display.h"

static LcdT	   Display;
// to hold the values of the time
static uint8_t DisplayTimeMinutes = 0;
static uint8_t DisplayTimeSeconds = 0;
//arrays to present on the screen
static uint8_t* SettingsFLine   = " Time Settings ";
static uint8_t* PausedFLine     = " System Paused ";
static uint8_t* PausedScndLine  = "Waiting  Command";
static uint8_t* RemainingFLine  = " Remaining Time ";
static uint8_t* DispSecondLine  = " Time = ";
//to buffer the time value to present on the display
static uint8_t  TimeMinBuffer[3];	//two for the value + the null for the minutes
static uint8_t  TimeSecBuffer[3];   //two for the value + the null for the seconds
static DisplayStateT DisplaySt  = DISPLAY_SETTING_TIME;

void DisplayInit(void ){
	Display.DataBase = BASE_B;
	Display.CommBase = BASE_B;
	LcdInit(&Display);
}

void DisplaySetTime(uint8_t Minutes, uint8_t Seconds){
    //mutual exclusion here
    DisplayTimeMinutes = Minutes;
    DisplayTimeSeconds = Seconds;
}

void DisplaySetState(DisplayStateT NewState){
    //mutual exclusion here
    DisplaySt = NewState;
}

void DisplayGetState(void){
	//mutual exclusion here
	return DisplaySt;
}
void DisplayUpdate(void ){
	
	if (DisplaySt == DISPLAY_SETTING_TIME){
		LcdCommOut(&Display,BEGIN_FROM_1ST_LINE);
		LcdArrDataOut(&Display,SettingsFLine);
		LcdCommOut(&Display,BEGIN_FROM_2ND_LINE);
		LcdArrDataOut(&Display,DispSecondLine);
	}
	else if (DisplaySt == DISPLAY_RUNING){
		LcdCommOut(&Display,BEGIN_FROM_1ST_LINE);
		LcdArrDataOut(&Display,RemainingFLine);
		LcdCommOut(&Display,BEGIN_FROM_2ND_LINE);
		LcdArrDataOut(&Display,DispSecondLine);
	    //mutual exclusion here
	    itoa(DisplayTimeMinutes, TimeMinBuffer, 10);
	    LcdArrDataOut(&Display, TimeMinBuffer);
	    LcdCharDataOut(&Display,':');
	    itoa(DisplayTimeSeconds, TimeSecBuffer, 10);
	    LcdArrDataOut(&Display, TimeSecBuffer);
	}
    else if (DisplaySt == DISPLAY_PAUSED){
        LcdCommOut(&Display,BEGIN_FROM_1ST_LINE);
        LcdArrDataOut(&Display,PausedFLine);
        LcdCommOut(&Display,BEGIN_FROM_2ND_LINE);
        LcdArrDataOut(&Display,PausedScndLine);
    }
    else{
        //do-nothing
    }        
	return LCD_ERR_NO;
}