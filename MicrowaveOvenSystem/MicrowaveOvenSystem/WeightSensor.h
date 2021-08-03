/*
 * WeightSensor.h
 *
 * Created: 7/22/2021 9:04:46 AM
 *  Author: ZeroX96
 */ 


#ifndef WEIGHTSENSOR_H_
#define WEIGHTSENSOR_H_


typedef BtnStateT WeightStateT;

void WeightSensInit(void );
WeightStateT WeightSensGetState(void );
void WeightSensUpdate(void );




#endif /* WEIGHTSENSOR_H_ */