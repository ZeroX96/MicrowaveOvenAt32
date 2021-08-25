/*
 * Time.h
 *
 * Created: 8/21/2021 9:35:21 PM
 *  Author: ZeroX96
 */ 


#ifndef TIME_H_
#define TIME_H_

#include "main.h"

#define TIME_MAX_VAL   (1200) //1200 Seconds = 20 Minutes
#define TIME_STEP_VAL  (5)


/* TimeInit: Function initializes the timer variable to zero                   */
void TimeInit(void);
/* TimeIncTime: Function increments the timer variable with step of 5 s        */
void TimeIncTime(void);
/* TimeDecTime: Function decrements the timer variable with step of 5 s        */
void TimeDecTime(void);
/* TimeSetTime: Function updates the timer value as needed                     */
void TimeSetTime(uint16_t TimeVal);
/* TimeResumeTime: Function resumes the timer variable and module operation    */
void TimeResumeTime(void);
/* TimePauseTime: Function pauses the timer variable and module operation      */
void TimePauseTime(void);
/* TimeGetTime: Function returns the timer variable current value              */
uint16_t TimeGetTime(void);
/* TimeUpdate: Function updates the timer variable current value  and handles  */
/*             the system mode of cocking when cocking is done                 */
void TimeUpdate(void);




#endif /* TIME_H_ */