/*
 * Phone.h
 *
 * Created: 7/22/2021 9:04:13 AM
 *  Author: Mosta
 */ 


#ifndef PHONE_H_
#define PHONE_H_

#include "Usart.h"

void PhoneInit(void );
uint8_t PhoneGetCommand();
void PhoneSendInfo();
void PhoneUpdate();
#endif /* PHONE_H_ */