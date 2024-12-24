#include "ADC_Mcal.h"


void ADC_Init(ADC_Type *ADC_Channel,ADC_Config *adc_config){

	PCC->CLKCFG[PCC_ADC0_INDEX] &= ~PCC_CLKCFG_CGC_MASK; // Turn off PCC
	Select_Soure_Async_CLK(PCC_ADC0_INDEX, adc_config->Async_CLK_Source,adc_config->AsyncClock_Divide); // Config async CLK
	PCC->CLKCFG[PCC_ADC0_INDEX] |= PCC_CLKCFG_CGC(1); // Turn on PCC

	// Interrupt
	ADC_Channel->SC1[0] |= ADC_SC1_AIEN(adc_config->interrupt_ADC_status);
	// Lack of NVIC

	// CLK
	ADC_Channel->CFG1 &= ~ADC_CFG1_ADICLK_MASK;
	// Mode trigger (SW or HW)
	ADC_Channel->SC2 |= ADC_SC2_ACFE(adc_config->mode_ADC_Trigger);
	// Continuous mode
	ADC_Channel->SC3 |= ADC_SC3_ADCO(adc_config->modeRead);



}

// Clock

// V-ref
// Resolution
// Mode - Single - continuous SC3[]
// Software trigger or HW trigger // SC2[ADTGR]
// Automatic compare with interrupt for less-than - None
// Hardware average function - None

uint16_t Read_ADC(ADC_Type *ADC_Channel){

	// METHOR READ - MODIFY - WRITE
	// Start conversion --> SC1A[ADCH] (SW) OR
	ADC_Channel->SC1[0] = (ADC_Channel->SC1[0] & ~ADC_SC1_ADCH_MASK | ADC_SC1_ADCH(0b11010)) ;


	// Wait end of conversion (N*T) SC1n[COCO] == 1
	while(0 == (ADC_Channel->SC1[0] & ADC_SC1_COCO_MASK));

	return ADC_Channel->R[0];
	// Read data Register - Rn


}


void Enable_Intterupt_NVIC_ADC(void){
	NVIC->ISER[0] |= (1 << ADC0_IRQn);
}


//ADC_Enable_Interrupt(); // SC1n[AIEN]
