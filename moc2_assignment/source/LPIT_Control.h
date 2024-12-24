#ifndef LPIT_CONTROL_MCAL_H
#define	LPIT_CONTROL_MCAL_H

#include <LPIT_Mcal.h>
#include "NVIC_Mcal.h"
#include "PCC_Mcal.h"

void Init_timer_LPIT(Channel_Type Channel, funcCallBackLPIT func_interrupt_LPIT_App);

void enable_interrupt_LPIT();
#endif
