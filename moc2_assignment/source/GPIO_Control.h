#ifndef GPIO_CONTROL_MCAL_H
#define	GPIO_CONTROL_MCAL_H

#include "GPIO_Mcal.h"
#include "Port_Mcal.h"
#include "NVIC_Mcal.h"
#include "PCC_Mcal.h"

typedef enum{
	LED_GREEN,
	LED_RED,
	LED_BLUE

}LED_List;


typedef enum{
	SW2,
	SW3

}SWITCH_List;

typedef void (*CallBack_Type_MDW)(SWITCH_List);

void init_GPIO_System(SWITCH_List button,CallBack_Type_MDW Func_CallBack_App);

void set_Led(LED_List LED);

void clear_Led(LED_List LED);

void toggle_Led(LED_List LED);

void EnableInterruptButton(void);


#endif
