/*
 * SevenSeg.c
 *
 * Created: 3/20/2020 5:40:14 AM
 *  Author: Mahmo
 */ 
#include "SevenSeg.h"
/************************************************************************/
/* an internal array holding the mapping between the displayed value    */
/*    and it's actual binary value to be used on the registers          */
/************************************************************************/
static uint8_t DispPatterns[MAX_POSSIBLE_VAL] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

 SevenSegRetT DisplayInit(SevenSegT* Display,GpioBaseT DispPort,SevenSegTypeT DispType){
	if (NULL != Display){
		Display->DataBase = DispPort;
		Display->Type = DispType;
		GpioInitPort(DispPort,PORT_OUT);
		return SEVENSEG_ERR_NO;
	}
	return SEVENSEG_ERR_INV_PARAMS;
}
 SevenSegRetT DisplayWrite(SevenSegT* Display,uint8_t OutVal){
	 if( (NULL != Display)&&(OutVal < MAX_POSSIBLE_VAL) ){
		 if (Display->Type == DISP_COMMON_CATHODE){
			 GpioWritePort(Display->DataBase,DispPatterns[OutVal]);
		 } 
		 else{
			 GpioWritePort(Display->DataBase,~(DispPatterns[OutVal]) );
		 }
		 return SEVENSEG_ERR_NO;
	 }
	 return SEVENSEG_ERR_INV_PARAMS;
 }
 SevenSegRetT DisplayReset(SevenSegT* Display){
	 if (NULL != Display){
		 if (Display->Type == DISP_COMMON_CATHODE){
			 GpioWritePort(Display->DataBase,DispPatterns[0]);
		 }
		 else{
			 GpioWritePort(Display->DataBase,~(DispPatterns[0]) );
		 }
		 return SEVENSEG_ERR_NO;
	 }
	 return SEVENSEG_ERR_INV_PARAMS;
 }
 SevenSegRetT DisplayDeInit(SevenSegT* Display){
	 if (NULL != Display){
		 if (Display->Type == DISP_COMMON_CATHODE){
			 GpioWritePort(Display->DataBase,DispPatterns[0]);
		 }
		 else{
			 GpioWritePort(Display->DataBase,~(DispPatterns[0]) );
		 }
		 Display->DataBase = 0x00;
		 return SEVENSEG_ERR_NO;
	 }
	 return SEVENSEG_ERR_INV_PARAMS;
 }
 
//multiplexed displays
SevenSegRetT DisplayMuxInit(SevenSegT* Display,GpioBaseT DataPort,GpioBaseT CtrlPort,SevenSegTypeT DispType)
{
	Display->CtrlBase = CtrlPort;
	Display->DataBase = DataPort;
	Display->Type = DispType;
	DisplayInit(Display,DataPort,DispType);
	for(uint8_t i =DISPLAY_CTRL_START_BIT;i < DISPLAY_CTRL_START_BIT + MUX_NUMBER_OF_DISPS; i++){
		GpioInitPin(CtrlPort,i,PIN_OUT);	
	}
	return SEVENSEG_ERR_NO;
}
SevenSegRetT DisplayMuxWrite(SevenSegT* Display,uint8_t OutDataVal[], uint8_t DispId){
    //look which display to present data on it 
	switch (DispId){
        
		case 0:
	        DisplayWrite(Display,OutDataVal[0]);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_HIGH);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_LOW);
		    break;
            
		case 1:
		    DisplayWrite(Display,OutDataVal[1]);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_HIGH);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_LOW);
			break;
		
        case 2:
	        DisplayWrite(Display,OutDataVal[2]);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_LOW);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_HIGH);
	        GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_LOW);
			break;
            
		case 3:
		    DisplayWrite(Display,OutDataVal[3]);
		    GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_LOW);
		    GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_LOW);
		    GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_LOW);
		    GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_HIGH);
			break;
            
        case DISPLAY_COCKING_DONE:
            DisplayWrite(Display,OutDataVal[0]);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_HIGH);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_HIGH);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_HIGH);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_HIGH);
            break;
            
        case DISPLAY_OUTPUT_OFF:
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_LOW);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_LOW);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_LOW);
            GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_LOW);
            break;
            
		default :
            break;
	}

	return SEVENSEG_ERR_NO;
}
SevenSegRetT DisplayMuxReset(SevenSegT* Display){
	
	DisplayWrite(Display,0);
	GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+0,PIN_HIGH);
	GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+1,PIN_HIGH);
	GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+2,PIN_HIGH);
	GpioWritePin(Display->CtrlBase,DISPLAY_CTRL_START_BIT+3,PIN_HIGH);
	return SEVENSEG_ERR_NO;
}
SevenSegRetT DisplayMuxDeInit(SevenSegT* Display){
	DisplayMuxReset(Display);
	DisplayDeInit(Display);
	Display->CtrlBase = 0x00;
	return SEVENSEG_ERR_NO;
}