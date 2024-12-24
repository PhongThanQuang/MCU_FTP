// MCAL

#include"Port_Mcal.h"

static PORT_Type *Port_Instance[] = PORT_BASE_PTRS;

CallBack_Type_Mcal PortBCD_CallbackHandler = NULL;

Port_t Port;

uint8_t Pin_PORT;

status_t PORT_Pin_Init(Port_Instance_t PORT_INS_x,uint8_t Pin,const Port_PCR_Config_t *pPinconfig){

	status_t retVal = E_OK;
	PORT_Type *Portx;

	retVal &= (0 <= Pin && Pin <= 31);
	retVal &= (pPinconfig != NULL);
	retVal & (PORT_INS_x < PORT_INS_NUM);

	if(E_OK == retVal){

		Portx = Port_Instance[PORT_INS_x];
		// Port Interrupt
		Portx ->PCR[Pin] &= ~PORT_PCR_IRQC_MASK;
		Portx ->PCR[Pin] |= PORT_PCR_IRQC(pPinconfig ->IRQC_Config);

		Portx ->PCR[Pin] &= ~PORT_PCR_LK_MASK;
		Portx ->PCR[Pin] |= PORT_PCR_LK(pPinconfig ->LK_Config);

		Portx ->PCR[Pin] &= ~PORT_PCR_MUX_MASK;
		Portx ->PCR[Pin] |= PORT_PCR_MUX(pPinconfig ->MUX_Config);

		Portx ->PCR[Pin] &= ~PORT_PCR_DSE_MASK;
		Portx ->PCR[Pin] |= PORT_PCR_DSE(pPinconfig ->DSE_Config);

		// Port pull
		Portx ->PCR[Pin] &= ~(PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
		Portx ->PCR[Pin] |= PORT_PCR_PE(pPinconfig->PE_Config); // Enable mode Pull
		Portx ->PCR[Pin] |= PORT_PCR_PS(pPinconfig->PS_Config); // Select mode pull


		// Call Back

		PortBCD_CallbackHandler = pPinconfig->CallBack;

		Pin_PORT = pPinconfig->Pin;

		Port = pPinconfig->Port;

	}




	return retVal;
}







void PORTBCD_IRQHandler(void){



	if(NULL != PortBCD_CallbackHandler) PortBCD_CallbackHandler(Pin_PORT,Port);

	PORTD->PCR[3] &= ~PORT_PCR_ISF_MASK;
	PORTD->PCR[3] |=  PORT_PCR_ISF(1);
}

