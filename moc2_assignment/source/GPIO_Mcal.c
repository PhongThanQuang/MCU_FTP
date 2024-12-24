#include "GPIO_Mcal.h"



status_t PinMode(GPIO_Type *GPIO_t,uint8_t Pin,GPIO_Drection_t Mode){

	GPIO_t->PDDR |= (GPIO_PDDR_PDD(Mode) << Pin) ;
}

status_t digitalWrite(GPIO_Type *GPIO_t,uint8_t Pin,Logic_t value){
	GPIO_t->PDOR |= (GPIO_PDOR_PDO(value) << Pin );
}

status_t digitalRead(GPIO_Type *GPIO_t, uint8_t Pin) {

    return (GPIO_t->PDIR & (1 << Pin)) ? 1 : 0;
}

status_t togglePin(GPIO_Type *GPIO_t,uint8_t Pin){
	GPIO_t->PTOR |= (GPIO_PTOR_PTTO(1) << Pin);
}

status_t clearPin(GPIO_Type *GPIO_t,uint8_t Pin){
	GPIO_t->PCOR |= (GPIO_PCOR_PTCO(1) << Pin);
}

status_t setPin(GPIO_Type *GPIO_t,uint8_t Pin){
	GPIO_t->PSOR |= (GPIO_PSOR_PTSO(1) << Pin);
}
