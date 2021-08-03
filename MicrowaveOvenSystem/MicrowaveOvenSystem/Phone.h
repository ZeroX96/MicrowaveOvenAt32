/*
 * Phone.h
 *
 * Created: 7/22/2021 9:04:13 AM
 *  Author: ZeroX96
 */ 


#ifndef PHONE_H_
#define PHONE_H_

#include "Usart.h"
#define MAX_PHONE_MESSAGE_LENGTH (100)
void PhoneInit(void );
uint8_t PhoneGetCommand();
void PhoneSendInfo(uint8_t* InfoPtr, uint8_t InfoSize);
void PhoneUpdateRx(void );
void PhoneUpdateTx(void );
#endif /* PHONE_H_ */