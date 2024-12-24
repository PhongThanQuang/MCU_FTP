// Middle ware

#include <GPIO_Control.h>


CallBack_Type_MDW PortBCD_Middleware_Callback  = NULL;

void Func_CallBack_MDW(uint8_t Pin,Port_t Port){
	if(3 == Pin && PORT_D == Port){
		if(NULL != PortBCD_Middleware_Callback ){
			PortBCD_Middleware_Callback (SW2);
		}

	}
}



void init_GPIO_System(SWITCH_List button,CallBack_Type_MDW PORTBCD_CallBack_App){



	Enable_Clock_Module(PCC_PORTB_INDEX);
	Enable_Clock_Module(PCC_PORTD_INDEX);

	PortBCD_Middleware_Callback  = PORTBCD_CallBack_App;

	const Port_PCR_Config_t gpioConfigDefault = {
				.MUX_Config 	= 	PORT_MUX_GPIO,
				.PE_Config 		= 	PULL_ENABLE,
				.PS_Config 		= 	PULL_UP,
				.IRQC_Config 	= 	IRQC_INTERRUPT_DISABLE

	};

	const Port_PCR_Config_t gpioButtonConfigDefault = {
				.MUX_Config 	= 	PORT_MUX_GPIO,
				.PE_Config 		= 	PULL_ENABLE,
				.PS_Config 		= 	PULL_UP,
				.IRQC_Config 	= 	IRQC_INTERRUPT_FALLING_EDGE,
				.Pin 			=  	(SW2 == button) ? 3 : 2,
				.Port			= 	(SW2 == button || SW3 == button) ? PORT_D : 0,
				.CallBack 		= 	Func_CallBack_MDW
	};

		PORT_Pin_Init(PORT_INS_B,4,&gpioConfigDefault); // LED GREEN
		PORT_Pin_Init(PORT_INS_B,5,&gpioConfigDefault); // LED RED
		PORT_Pin_Init(PORT_INS_D,1,&gpioConfigDefault); // LED BLUE

		PORT_Pin_Init(PORT_INS_D, 2,&gpioButtonConfigDefault); // SW3
		PORT_Pin_Init(PORT_INS_D, 3,&gpioButtonConfigDefault); // SW2

		PinMode(GPIOD,2,INPUT); // SW3
		PinMode(GPIOD,3,INPUT); // SW2

		PinMode(GPIOB,4,OUTPUT);
		PinMode(GPIOB,5,OUTPUT);
		PinMode(GPIOD,1,OUTPUT);

		digitalWrite(GPIOB,4,HIGH);
		digitalWrite(GPIOB,5,HIGH);
		digitalWrite(GPIOD,1,HIGH);



}

void set_Led(LED_List LED) {
    switch (LED) {
        case LED_GREEN:
            setPin(GPIOB, 4);
            break;
        case LED_RED:
            setPin(GPIOB, 5);
            break;
        case LED_BLUE:
            setPin(GPIOD, 1);
            break;
        default:
            // Optionally, handle invalid cases
            break;
    }
}

void clear_Led(LED_List LED){
	switch (LED) {
		case LED_GREEN:
			clearPin(GPIOB, 4);
			break;
		case LED_RED:
			clearPin(GPIOB, 5);
			break;
		case LED_BLUE:
			clearPin(GPIOD, 1);
			break;
		default:
			// Optionally, handle invalid cases
			break;
	}
}

void toggle_Led(LED_List LED){
	switch (LED) {
		case LED_GREEN:
			togglePin(GPIOB, 4);
			break;
		case LED_RED:
			togglePin(GPIOB, 5);
			break;
		case LED_BLUE:
			togglePin(GPIOD, 1);
			break;
		default:
			// Optionally, handle invalid cases
			break;
	}
}


void EnableInterruptButton(){
	Enable_Intterupt_NVIC(PORTBCD_IRQn);
}
