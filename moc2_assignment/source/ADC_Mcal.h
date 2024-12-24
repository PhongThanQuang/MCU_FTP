#ifndef ADC_MCAL_H
#define	ADC_MCAL_H


#include "MKE16Z4.h"
#include "fsl_common.h"
#include "PCC_Mcal.h"


typedef enum{
	SOFTWARE_TRIGGER = 0,
	HARDWARE_TRIGGER
}modeTriggerADC_t;


typedef enum{
	INTERRUPT_ADC_DISABLE = 0,
	INTERRUPT_ADC_ENABLE
}Interrupt_ADC_t;


typedef enum{
	READ_SIMPLE = 0,
	READ_CONTINOUS
}modeReadADC_t;


typedef struct {

	Source_AsyncClock Async_CLK_Source;
	Divide_type AsyncClock_Divide;
	modeTriggerADC_t mode_ADC_Trigger;
	modeReadADC_t modeRead;
	Interrupt_ADC_t interrupt_ADC_status;


}ADC_Config;





void ADC_Init(ADC_Type *ADC_Channel,ADC_Config *adc_config);
// Clock

// V-ref
// Resolution
// Mode - Single - continuous SC3[]
// Software trigger or HW trigger // SC2[ADTGR]
// Automatic compare with interrupt for less-than - None
// Hardware average function - None

uint16_t Read_ADC(ADC_Type *ADC_Channel);

void Enable_Intterupt_NVIC_ADC(void);

#endif
