/*
 * Phone.c
 *
 * Created: 7/23/2021 2:25:44 AM
 *  Author: ZeroX96
 */ 
#include "Phone.h"
static UsartT Phone;
//mutual exclusion here - two
static uint8_t* PtrDataTx;	//used to give information to the user
static uint8_t SizeDataTx;	//used to give hold the size of info to the user
static uint8_t CurrentDataTx;	//used to keep track of the sent data
static uint8_t  PtrDataRx;	//used to get commands from the user
UsartRetT UsartSendByte(UsartT * UsartObj,uint8_t* byte);

void PhoneInit(void ){
	//init hardware			
	UsartInit(&Phone, B_SENDER_N_RECEIVER, ONE_STP_BIT, EVEN_PARITY,
					  EIGHT_DATA_BITS, INTERRUPT_DRIVEN, Rising_EDGE);
	UsartSetIsrRxcCb( &Phone, PhoneUpdateRx); //isr really?

	UsartSetIsrTxcCb( &Phone, PhoneUpdateTx); //isr really?
}

uint8_t PhoneGetCommand(void ){
	//mutual exclusion here xsem take
	return PtrDataRx;
}

void PhoneSendInfo(uint8_t* InfoPtr, uint8_t InfoSize){
	//mutual execlusion here xsem take
	PtrDataTx = InfoPtr;
	SizeDataTx = InfoSize;
}

void PhoneUpdateTx(void ){
	UsartSendByte( &Phone, PtrDataTx + CurrentDataTx);
	CurrentDataTx++;
	if (CurrentDataTx == SizeDataTx){
		CurrentDataTx = 0;
		//xsem give
	}
}
void PhoneUpdateRx(void ){
	//mutual exclusion here
	UsartReceiveByte( &Phone, &PtrDataRx);
	//xsem give
}