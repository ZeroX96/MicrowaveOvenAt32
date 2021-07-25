/*
 * WeightSensor.c
 *
 * Created: 7/23/2021 9:36:07 AM
 *  Author: Mosta
 */ 

void WeightSensInit(void ){
	BtnInit(BTN_WEIGHT, BTN_RELEASED);
}

WeightStateT WeightSensGetState(void ){
	return BtnGetState(BTN_WEIGHT);
}

void WeightSensUpdate(void ){
	BtnUpdate();
}