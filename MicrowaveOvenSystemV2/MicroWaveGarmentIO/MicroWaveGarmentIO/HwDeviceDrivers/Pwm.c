/*
 * Pwm.c
 *
 * Created: 3/20/2020 5:38:54 AM
 *  Author: Mahmo
 */ 
#include "Pwm.h"


PwmRetT PwmInit(PwmT* Pwm, PwmBaseT PwmBase,	     \
				PwmOutputModeT		PwmOutputMode,   \
				PWmDutyCycleT		PWmDutyCycle,    \
				PwmOperatingModeT	PwmOperatingMode,\
				uint32_t			PwmFrequency)
{
	if (NULL != Pwm)
	{
		Pwm->Base = PwmBase;
		Pwm->OperatingMode = PwmOperatingMode;
		Pwm->OutputMode	= PwmOutputMode;
		Pwm->DutyCycle = PWmDutyCycle;
		Pwm->Freq = PwmFrequency;
		
		uint16_t OcrRegVal = 0;
		double	 RequiredPrescaller = 0;
		//getting the prescaller and the ocr reg val
		if (PwmOperatingMode == FAST_PWM){
			RequiredPrescaller = (double)((double)PWM_SYS_CLOCK / (double)(PwmFrequency * 256) );
			if (PwmOutputMode == NON_INVERTING_OUTPUT){
				OcrRegVal = (((PWmDutyCycle * 256) / 100) - 1);
			} 
			else{
				OcrRegVal = (255 - ((PWmDutyCycle * 256) / 100));				
			}
		} 
		else{
			RequiredPrescaller = (double)((double)PWM_SYS_CLOCK / (double)(PwmFrequency * 510) );
			if (PwmOutputMode == NON_INVERTING_OUTPUT){
				OcrRegVal = ((PWmDutyCycle * 255) / 100);
			}
			else{
				OcrRegVal = (255 - ((PWmDutyCycle * 255) / 100));
			}
			
		}
		if (  RequiredPrescaller < (double)1.0) Pwm->Prescaller=PWM_NO_PRESCALER;
		else if ( (RequiredPrescaller > (double)1.0) && (RequiredPrescaller <(double)8.0) ) Pwm->Prescaller=PWM_PRESCALER_8;
		else if ( (RequiredPrescaller > (double)8.0) && (RequiredPrescaller <(double)64.0) ) Pwm->Prescaller=PWM_PRESCALER_64;
		else if ( (RequiredPrescaller > (double)64.0) && (RequiredPrescaller <(double)256.0) ) Pwm->Prescaller=PWM_PRESCALER_256;
		else if ( (RequiredPrescaller > (double)256.0) && (RequiredPrescaller <(double)1024.0) ) Pwm->Prescaller=PWM_PRESCALER_1024;
		else return PWM_ERR_IMP_PRESCALLER;
		
		HwWriteRegOring(Pwm->Base,Pwm->Prescaller);
		HwWriteRegOring(Pwm->Base, (( (Pwm->OperatingMode) & 0x02)<< WGM1_BIT) |((( (Pwm->OperatingMode) & 0x01)<<WGM0_BIT)) );
		HwWriteRegOring(Pwm->Base, (Pwm->OutputMode)<<COM0_BIT);
		
		if (PwmBase == PWM_TIMER_0){
			HwWriteReg(OCR0_REG,OcrRegVal);
		}
		else if(PwmBase == PWM_TIMER_2){
			HwWriteReg(OCR2_REG,OcrRegVal);
		}
		//by default and after initialization, no output signal is active
		//PwmEnableSrc(Pwm->Base);
		return PWM_ERR_NO;
	}
	return PWM_ERR_INV_PARAMS;
}

PwmRetT PwmRun(PwmT* Pwm){
    if (NULL != Pwm)
    {
        if (Pwm->Base == PWM_TIMER_0){
            HwSetRegBit(OCN0_BASE + DDRx_OFFSET, OCN0_PIN);
        }
        else{
            HwSetRegBit(OCN2_BASE + DDRx_OFFSET, OCN2_PIN);
        }
        return PWM_ERR_NO;
    }
    return PWM_ERR_INV_PARAMS;
}
PwmRetT PwmStop(PwmT* Pwm){
	if (NULL != Pwm)
	{
        //disable and stop the signal output
        if (Pwm->Base == PWM_TIMER_0){
            HwClrRegBit(OCN0_BASE + DDRx_OFFSET, OCN0_PIN);
        }
        else{
            HwClrRegBit(OCN2_BASE + DDRx_OFFSET, OCN2_PIN);
        }
		return PWM_ERR_NO;
	}
	return PWM_ERR_INV_PARAMS;
}
PwmRetT PwmDeInit(PwmT* Pwm){
	if (NULL != Pwm)
	{
		PwmStop(Pwm);
		Pwm->Base = 0x00;
		Pwm->DutyCycle = 0x00;
		Pwm->Freq = 0x00;
		Pwm->OperatingMode = 0x00;
		Pwm->OutputMode = 0x00;
		Pwm->Prescaller = 0x00;
		return PWM_ERR_NO;
	}
	return PWM_ERR_INV_PARAMS;
}