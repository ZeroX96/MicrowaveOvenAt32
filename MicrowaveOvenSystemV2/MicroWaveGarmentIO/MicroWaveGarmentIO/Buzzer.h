/*
 *  File    : BuzzApp.h
 *
 *  Author  : MahmoudSaad.ZeroX96
 *  Email   : Mahmoud.S.AbdElhares@gmail.com
 *  Github  : github.com/ZeroX96
 *  LinkedIn: www.linkedin.com/in/mahmoudsaad96
 */


#ifndef BUZZAPP_H_
#define BUZZAPP_H_

#include <stdint.h>
#include "Gpio.h"
#include "main.h"

//define the number of Lamps in the system
#define BUZZERS_NUM      (1)
//define a safe-guard to protect the system from underflowing when iterating
#define BUZZ_SAFE_GUARD  (10)
/************************************************************************/
/* BuzzStateT, a defined data type for the states of the Buzzers        */
/************************************************************************/
typedef enum{
    BUZZ_OFF,
    BUZZ_ON
}BuzzStateT;

/************************************************************************/
/* BuzzSelectT, a defined data type for selecting a specific Buzzer     */
/************************************************************************/
typedef enum{
    BUZZ_ONE
}BuzzSelectT;

void BuzzInit(BuzzSelectT BuzzSelect, BuzzStateT BuzzInitState);
void BuzzSetState(BuzzSelectT BuzzSelect, BuzzStateT BuzzState, int16_t Duration);
void BuzzUpdate(void );


#endif /* BUZZAPP_H_ */