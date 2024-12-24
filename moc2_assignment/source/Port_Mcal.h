#ifndef PORT_MCAL_H
#define	PORT_MCAL_H


#include "MKE16Z4.h"
#include "fsl_common.h"


typedef enum{
	PORT_A = 0,
	PORT_B ,
	PORT_C ,
	PORT_D ,
	PORT_E
}Port_t;


enum{
	E_NOT_OK = 0,
	E_OK = 1

};

typedef struct{

}PinInterruptType;

typedef struct{

}DigitalInputFilterType;


typedef enum{

	IRQC_INTERRUPT_DISABLE = 0,
	IRQC_INTERRUPT_LOW_LOGIC = 8,
	IRQC_INTERRUPT_RISING_EDGE,
	IRQC_INTERRUPT_FALLING_EDGE,
	IRQC_INTERRUPT_EITHER_EDGE,
	IRQC_INTERRUPT_HIGH_LOGIC

}IRQC_Port_t;

typedef enum{

	NOT_LOCK_REGISTER = 0,
	LOCK_REGISTER

}LK_Port_t;

typedef enum{

	PORT_MUX_ANALOG = 0,
	PORT_MUX_GPIO = 1,
	ALT2,
	ALT3,
	ALT4,
	ALT5,
	ALT6,
	ALT7
}MUX_Port_t;

typedef enum{
	LOW_DRIVE_STRENGTH = 0,
	HIGH_DRIVE_STRENGTH
}DSE_Port_t;

typedef enum{
	PASSIVE_INPUT_FILLTER_DISABLED = 0,
	PASSIVE_INPUT_FILLTER_ENABLED
}PFE_Port_t;

typedef enum{
	PULL_ENABLE = 0,
	PULL_DISABLE,
} PE_Port_t;

typedef enum {
	PULL_UP = 0,
	PULL_DOWN
}PS_Port_t;


typedef enum{
	INTERRUPT_DISABLE_DETECTED = 0,
	INTERRUPT_ENABLE_DETECTED
}PortInterruptFlag_t;

// Create Function Pointer Type
typedef void (*CallBack_Type_Mcal)(uint8_t,Port_t);

typedef struct{
	IRQC_Port_t IRQC_Config;

	LK_Port_t LK_Config;

	MUX_Port_t MUX_Config;

	DSE_Port_t DSE_Config;

	PFE_Port_t PFE_Config;

	PE_Port_t PE_Config;

	PS_Port_t PS_Config;

	uint8_t Pin;

	Port_t Port;


	CallBack_Type_Mcal CallBack;


}Port_PCR_Config_t;


typedef enum {

	PORT_INS_A = 0,
	PORT_INS_B = 1,
	PORT_INS_C = 2,
	PORT_INS_D = 3,
	PORT_INS_E = 4,
	PORT_INS_NUM = 5

}Port_Instance_t;




status_t PORT_Pin_Init(Port_Instance_t PORT_INS_x,uint8_t Pin,const Port_PCR_Config_t *pPinconfig);




#endif // PORT_MCAL_H

