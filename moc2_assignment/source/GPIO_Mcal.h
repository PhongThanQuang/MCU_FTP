#ifndef GPIO_MCAL_H
#define	GPIO_MCAL_H

#include "MKE16Z4.h"
#include "fsl_common.h"


typedef enum {
	INPUT = 0,
	OUTPUT
}GPIO_Drection_t;

typedef enum {
	LOW = 0,
	HIGH
}Logic_t;


status_t PinMode(GPIO_Type *GPIO_t,uint8_t Pin,GPIO_Drection_t Mode);

status_t digitalWrite(GPIO_Type *GPIO_t,uint8_t Pin,Logic_t value);

status_t digitalRead(GPIO_Type *GPIO_t, uint8_t Pin);

status_t togglePin(GPIO_Type *GPIO_t,uint8_t Pin);

status_t clearPin(GPIO_Type *GPIO_t,uint8_t Pin);

status_t setPin(GPIO_Type *GPIO_t,uint8_t Pin);

#endif
