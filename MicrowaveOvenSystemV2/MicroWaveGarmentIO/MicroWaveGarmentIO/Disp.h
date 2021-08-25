/*
 * Disp.h
 *
 * Created: 8/21/2021 7:49:02 PM
 *  Author: ZeroX96
 */ 


#ifndef DISP_H_
#define DISP_H_
#include "main.h"
#include "SevenSeg.h"
#include "Time.h"


/* DispInit: Function initializes the Display module                           */
void DispInit(void);
/* DispSetVal: Function updates the Display value as needed                        */
void DispSetVal(uint16_t DataVal);
/* DispUpdate: Function updates the display data current shown on the segments */
void DispUpdate(uint8_t Id);



#endif /* DISP_H_ */