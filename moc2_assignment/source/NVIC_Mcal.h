#ifndef NVIC_MCAL_H
#define NVIC_MCAL_H

#include "MKE16Z4.h"
#include "fsl_common.h"



#define SET_PRI(x, y) ((x) << (6 + (y) * 8))

void Enable_Intterupt_NVIC(IRQn_Type IRQ);
void Disable_Intterupt_NVIC(IRQn_Type IRQ);
void setPriorityInterrupt(IRQn_Type IRQ, uint8_t Priority);

#endif


