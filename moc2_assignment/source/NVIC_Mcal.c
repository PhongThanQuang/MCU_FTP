#include "NVIC_Mcal.h"

void Enable_Intterupt_NVIC(IRQn_Type IRQ){
	NVIC->ISER[0] |= (1 << IRQ);
}

void Disable_Intterupt_NVIC(IRQn_Type IRQ){
	NVIC->ISER[0] |= (0 << IRQ);
}

void setPriorityInterrupt(IRQn_Type IRQ, uint8_t Priority){
		uint8_t IPRx = 0 ;
		uint8_t offset_IPRx = 0 ;
		IPRx = IRQ / 4;
		offset_IPRx = IRQ % 4;

		NVIC->IP[IPRx] &= ~(0x03 << 6);
		NVIC->IP[IPRx] |= SET_PRI(Priority,offset_IPRx);
}


