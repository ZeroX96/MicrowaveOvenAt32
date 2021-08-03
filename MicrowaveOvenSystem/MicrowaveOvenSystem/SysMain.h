/*
 * SysMain.h
 *
 * Created: 8/3/2021 11:22:48 AM
 *  Author: ZeroX96
 */ 


#ifndef SYSMAIN_H_
#define SYSMAIN_H_
#include "MicroWave.h"

typedef enum{
    SYSTEM_STOPPED,
    SYSTEM_PAUSED,
    SYSTEM_RUNNING
}SysStateT;

void SysMainApp(void);


#endif /* SYSMAIN_H_ */