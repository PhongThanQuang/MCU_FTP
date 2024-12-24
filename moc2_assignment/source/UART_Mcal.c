#include "UART_Mcal.h"

static uint32_t arr_speed_source[] = {
								0,			// DISABLE
								0,			// LPFLL
								8000000,	// FIRC
								48000000,	// SIRC
								0			// SOSC
};

//static uint32_t arr_baudrate[] = {
//    BAURATE_300,     // 300 baud
//    BAURATE_1200,    // 1,200 baud
//    BAURATE_2400,    // 2,400 baud
//    BAURATE_4800,    // 4,800 baud
//    BAURATE_9600,    // 9,600 baud
//    BAURATE_19200,   // 19,200 baud
//    BAURATE_38400,   // 38,400 baud
//    BAURATE_57600,   // 57,600 baud
//    BAURATE_115200,  // 115,200 baud
//    BAURATE_230400,  // 230,400 baud
//    BAURATE_460800,  // 460,800 baud
//    BAURATE_921600   // 921,600 baud
//};
// UART <-> OpenSDA Chip (PC)
// UART0_TX = PB1 / UART_RX = PB0
// Config Module Port
static uint32_t pow_func(uint8_t x, uint8_t y){
    uint8_t i;
    uint32_t result_multiple = 1;

    for (i = 0; i < y; i++){
        result_multiple *= x;
    }

    return result_multiple;
}

LPUART_Type * UART_Instance[] = LPUART_BASE_PTRS;



static void UART_SetBaudrate(LPUART_Type *base, BAURATE_uart baudrate, uint32_t frequency)
{
    float diver = (float)frequency / baudrate;
    uint8_t osr;
    uint8_t osr_temp;
    uint16_t sbr_temp;
    float min_delta = baudrate;

    for (osr = 4; osr <= 32; osr++)
    {
        sbr_temp = (uint16_t)(diver / osr);
        if ((sbr_temp >= 1) && (sbr_temp <= 8191))
        {
            if (fabs(sbr_temp * osr - diver) <= min_delta)
            {
                osr_temp = osr;
            }
        }
    }
    if ((osr_temp >= 4) || (osr_temp <= 7))
    {
        base->BAUD |= LPUART_BAUD_BOTHEDGE_MASK;
    }
    base->BAUD = (base->BAUD & ~LPUART_BAUD_OSR_MASK) | LPUART_BAUD_OSR(osr_temp - 1);
    base->BAUD = (base->BAUD & ~LPUART_BAUD_SBR_MASK) | LPUART_BAUD_SBR(sbr_temp);
}

void Enable_Interrupt_UART_Recive(UART_Instance_t UARTx){
	LPUART_Type * UART_x = UART_Instance[UARTx];
	UART_x->CTRL |= LPUART_CTRL_RIE(1);
	Enable_Intterupt_NVIC(LPUART0_IRQn);
}

void Disnable_Interrupt_UART_Recive(UART_Instance_t UARTx){
	LPUART_Type * UART_x = UART_Instance[UARTx];
	UART_x->CTRL |= LPUART_CTRL_RIE(0);
	Disble_Intterupt_NVIC(LPUART0_IRQn);
}
void UART_Init(UART_Instance_t UARTx, UARTx_Config_t *uartconfig){

	LPUART_Type * UART_x = UART_Instance[UARTx];

	// Enable Clock
	Disable_Clock_Module(UARTx + PCC_LPUART0_INDEX);
	Select_Soure_Async_CLK(UARTx + PCC_LPUART0_INDEX, uartconfig->AsyncUART, uartconfig->Divide);
	Enable_Clock_Module(UARTx + PCC_LPUART0_INDEX);



	const Port_PCR_Config_t UART_TX_ConfigDefault = {
		.MUX_Config 	= 	ALT2, // PB1
		.PE_Config 		= 	PULL_ENABLE,
		.PS_Config 		= 	PULL_UP,
		//.IRQC_Config 	= 	IRQC_INTERRUPT_DISABLE

	};

	const Port_PCR_Config_t UART_RX_ConfigDefault = {
		.MUX_Config 	= 	ALT2, // PB0
		.PE_Config 		= 	PULL_ENABLE,
		.PS_Config 		= 	PULL_UP,
		.IRQC_Config 	= 	IRQC_INTERRUPT_DISABLE

	};

	Enable_Clock_Module(PCC_PORTB_INDEX);

	PORT_Pin_Init(PORT_INS_B,0,&UART_RX_ConfigDefault);
	PORT_Pin_Init(PORT_INS_B,1,&UART_TX_ConfigDefault);

	UART_SetBaudrate(UART_x,uartconfig->baurate_uart, arr_speed_source[uartconfig->AsyncUART]);

	UART_x->BAUD |= LPUART_BAUD_M10(0); //  0b - Receiver and transmitter use 7-bit to 9-bit data characters

	UART_x->BAUD |= LPUART_BAUD_SBNS(0); // One stop bit.

	UART_x->CTRL |= LPUART_CTRL_M7(0); // Select use 8bit - 10bit mode

	UART_x->CTRL |= LPUART_CTRL_M(0); // Select 8 bit characters

	UART_x->CTRL |= LPUART_CTRL_TE(1) | LPUART_CTRL_RE(1);

	//UART_x->CTRL |= LPUART_CTRL_PE(1); 	// Parity enabled.


}
// CLOCK(Peripheral CLK / Asynce clk)
// IO Port - // UART0_TX = PB1 / UART_RX = PB0 (mux & pull up)
// BaudRate (OSR & SBR)
// Frame
// - Data length
// - how many stop bit
// - Parity Bit (None - Old - Even)

void UART_Transmit_Buff(UART_Instance_t UARTx, uint8_t *Buffer,uint8_t length){

}
void UART_Transmit_Byte(UART_Instance_t UARTx ,uint8_t Data){

	LPUART_Type * UART_x = UART_Instance[UARTx];
	UART_x->CTRL |= LPUART_CTRL_TE(1); // 1b - Transmitter enabled
	while(UART_x->STAT & LPUART_STAT_TDRE_MASK);
	UART_x->DATA |= Data;
	UART_x->CTRL |= LPUART_CTRL_TE(0); // 1b - Transmitter enabled


}

// TE = 1
// Wait TX buffer Empty
// TxBuffer = Data
// Wait TX Transmission Complete
// TE = 0

void UART_Receive_Byte(UART_Instance_t UARTx ,uint8_t *Data){
	LPUART_Type * UART_x = UART_Instance[UARTx];
	UART_x->CTRL |= LPUART_CTRL_RE(1); // 1b - Receiver enabled
	//while(!(UART_x->STAT & LPUART_STAT_RDRF_MASK));
	*Data = UART_x->DATA;
	UART_x->CTRL |= LPUART_CTRL_RE(0); // 1b - Receiver enabled
}

// RE = 1
// Wait RX Buffer is full
// Temp = RX Buffer
// RE = 0

void UART_Receive_Buff(UART_Instance_t UARTx, uint8_t *Buffer, uint8_t length) {
    LPUART_Type *UART_x = UART_Instance[UARTx];
    uint8_t idx;

    for (idx = 0; idx < length; idx++) {
        while (!(UART_x->STAT & LPUART_STAT_RDRF_MASK)); // Wait until Receive Data Register Full flag is set
        Buffer[idx] = UART_x->DATA; // Read received data into buffer
    }
}


void UART_Receive_Byte_Interrupt(){

}
