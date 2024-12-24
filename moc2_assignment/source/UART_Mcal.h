#ifndef UART_MCAL_H
#define	UART_MCAL_H


#include "MKE16Z4.h"
#include "fsl_common.h"
#include "PCC_Mcal.h"
#include "Port_Mcal.h"
#include "math.h"
#include "NVIC_Mcal.h"


typedef enum {

	UART_0 = 0,
	UART_1,
	UART_2

}UART_Instance_t;

typedef enum {
    BAURATE_300     = 300,      // 300 baud
    BAURATE_1200    = 1200,     // 1,200 baud
    BAURATE_2400    = 2400,     // 2,400 baud
    BAURATE_4800    = 4800,     // 4,800 baud
    BAURATE_9600    = 9600,     // 9,600 baud
    BAURATE_19200   = 19200,    // 19,200 baud
    BAURATE_38400   = 38400,    // 38,400 baud
    BAURATE_57600   = 57600,    // 57,600 baud
    BAURATE_115200  = 115200,   // 115,200 baud
    BAURATE_230400  = 230400,   // 230,400 baud
    BAURATE_460800  = 460800,   // 460,800 baud
    BAURATE_921600  = 921600    // 921,600 baud
} BAURATE_uart;

typedef struct {

	Port_PCR_Config_t *Port_uart_config;
	BAURATE_uart baurate_uart;
	Source_AsyncClock AsyncUART;
	Divide_type Divide;

} UARTx_Config_t;



void UART_Init(UART_Instance_t UARTx, UARTx_Config_t *uartconfig);
// CLOCK(Peripheral CLK / Asynce clk)
// IO Port - // UART0_TX = PB1 / UART_RX = PB0 (mux & pull up)
// BaudRate (OSR & SBR)
// Frame
// - Data length
// - how many stop bit
// - Parity Bit (None - Old - Even)

void UART_Transmit_Buff(UART_Instance_t UARTx, uint8_t *Buffer,uint8_t length);
void UART_Transmit_Byte(UART_Instance_t UARTx ,uint8_t Data);

// TE = 1
// Wait TX buffer Empty
// TxBuffer = Data
// Wait TX Transmission Complete
// TE = 0

void UART_Receive_Byte(UART_Instance_t UARTx ,uint8_t *Data);

// RE = 1
// Wait RX Buffer is full
// Temp = RX Buffer
// RE = 0

void UART_Receive_Buff(UART_Instance_t UARTx, uint8_t *Buffer, uint8_t length);

void UART_Receive_Byte_Interrupt();


void Enable_Interrupt_UART_Recive(UART_Instance_t UARTx);

void Disnable_Interrupt_UART_Recive(UART_Instance_t UARTx);
#endif
