/*
 * SysMain.c
 *
 * Created: 8/3/2021 11:22:24 AM
 *  Author: ZeroX96
 */ 
#include "SysMain.h"

static SysStateT SystemState = SYSTEM_STOPPED;
//statics for start button
static BtnStateT StartBtnState    = 0;
static BtnStateT StartBtnOldState = 0;
static BtnStateT StartBtnNewState = 0;
//statics for cancel button
static BtnStateT CancelBtnState    = 0;
static BtnStateT CancelBtnOldState = 0;
static BtnStateT CancelBtnNewState = 0;
//statics for door Sensor
static DoorStateT DoorBtnState    = 0;
static DoorStateT DoorBtnOldState = 0;
static DoorStateT DoorBtnNewState = 0;
//statics for weight button
static WeightStateT WeightBtnState    = 0;
static WeightStateT WeightBtnOldState = 0;
static WeightStateT WeightBtnNewState = 0;
//statics for sending info to the user
static uint8_t PhoneMessage[MAX_PHONE_MESSAGE_LENGTH];
void SysMainApp(void){
    if (SystemState == SYSTEM_STOPPED){
        //show to the user the message to get the settings
        DisplaySetState(DISPLAY_SETTING_TIME);
        LampSetState(LAMP_ONE, LAMP_OFF);
        MotorSetState(MOTOR_ONE, MOTOR_STOPPED);
        HeaterSetState(HEATER_ONE, HEATER_OFF);
        PhoneMessage = "Hello, The System is stopped\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
        PhoneMessage = "Please, Select Your Time Settings and Press Start\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
        //check the state of the door sensor
        DoorBtnNewState = BtnGetState(BTN_DOOR);
        if ((DoorBtnNewState == BTN_PRESSED) && (DoorBtnOldState == BTN_RELEASED)){
            DoorBtnState = BTN_PRESSED;
            DoorBtnOldState = BTN_PRESSED;
        }
        else if (DoorBtnNewState == BTN_RELEASED){
            DoorBtnOldState = BTN_RELEASED;
        }
        else if ((DoorBtnNewState == BTN_RELEASED) && (DoorBtnOldState == BTN_RELEASED)){
            DoorBtnState = BTN_RELEASED;
        }
        else{
            //Do-Nothing
        }
        //check the state of the weight sensor
        WeightBtnNewState = BtnGetState(BTN_WEIGHT);
        if ((WeightBtnNewState == BTN_PRESSED) && (WeightBtnOldState == BTN_RELEASED)){
            WeightBtnState = BTN_PRESSED;
            WeightBtnOldState = BTN_PRESSED;
        }
        else if (WeightBtnNewState == BTN_RELEASED){
            WeightBtnOldState = BTN_RELEASED;
        }
        else if ((WeightBtnNewState == BTN_RELEASED) && (WeightBtnOldState == BTN_RELEASED)){
            WeightBtnState = BTN_RELEASED;
        }
        else{
            //Do-Nothing
        }
        //check if there is a start button press
        //notice that i take action once for the whole press period
        StartBtnNewState = BtnGetState(BTN_START);
        if ((StartBtnNewState == BTN_PRESSED) && (StartBtnOldState == BTN_RELEASED)){
            //actual press, see if the door and the weight sensors are ok
            if ((DoorBtnState == BTN_PRESSED) && (WeightBtnState == BTN_PRESSED)){
                SystemState = SYSTEM_RUNNING; 
            }
            StartBtnOldState = BTN_PRESSED;
        }
        else if (StartBtnNewState == BTN_RELEASED){
            StartBtnOldState = BTN_RELEASED;
        }
        else{
            //Do-Nothing
        }
        //check if there is a Cancel button press
        //notice that i take action once for the whole press period
        CancelBtnNewState = BtnGetState(BTN_START);
        if ((CancelBtnNewState == BTN_PRESSED) && (CancelBtnOldState == BTN_RELEASED)){
            if (SystemState == SYSTEM_RUNNING){
                SystemState = SYSTEM_PAUSED;
            } 
            else if (SystemState == SYSTEM_PAUSED){
                SystemState = SYSTEM_STOPPED;
            }
            else{
            	//Do-Nothing
            }
            CancelBtnOldState = BTN_PRESSED;
        }
        else if (CancelBtnNewState == BTN_RELEASED){
            CancelBtnOldState = BTN_RELEASED;
        }
        else{
            //Do-Nothing
        }

    }
    else if (SystemState == SYSTEM_RUNNING){
        //show to the user the message information about system working
        DisplaySetState(DISPLAY_RUNING);
        LampSetState(LAMP_ONE, LAMP_ON);
        MotorSetState(MOTOR_ONE, MOTOR_RUNNING);
        HeaterSetState(HEATER_ONE, HEATER_ON);
        PhoneMessage = "Now The System is Running\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
        PhoneMessage = "Please, Wait Until Your Meal Is Ready\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
    }
    else if (SystemState == SYSTEM_PAUSED){
        //show to the user the message information about system working
        DisplaySetState(DISPLAY_PAUSED);
        LampSetState(LAMP_ONE, LAMP_ON);
        MotorSetState(MOTOR_ONE, MOTOR_STOPPED);
        HeaterSetState(HEATER_ONE, HEATER_OFF);
        PhoneMessage = "Now The System is Paused\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
        PhoneMessage = "Please, Press Cancel to Stop or Start to Continue\n";
        PhoneSendInfo(PhoneMessage, strlen(PhoneMessage));
    }
    else{
        //do-nothing
    }
}