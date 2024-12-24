/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Appplication

//#include <GPIO_Control.h>
//#include <LPIT_Control.h>
#include "stdint.h"
#include "UART_Mcal.h"
#include "KE16_Flash.h"
//#include "core_cm0plus.h"
//#include "ADC_Mcal.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(uint8_t time);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(uint8_t time)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 480000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


//void SystickDelay(uint32_t time_ms){
//
//
//	SysTick->CTRL |= 1 << SysTick_CTRL_ENABLE_Pos ;
//	SysTick->CTRL |= 1 << SysTick_CTRL_CLKSOURCE_Pos; // 48MHz => 1000 cycle CPU = 20.8 = 21ms
//
//	SysTick->LOAD = (48000000/(1000/time_ms)) + 1;
//
//	SysTick->LOAD |= SysTick_CTRL_COUNTFLAG_Msk;
//
//	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
//
//}


/*!
 * @brief Main function
 */




//void firstEvent(){
//	set_Led(LED_GREEN);
//	set_Led(LED_RED);
//	SystickDelay(200);
//	clear_Led(LED_GREEN);
//	clear_Led(LED_RED);
//	SystickDelay(200);
//}
//
//void secondEvent(){
//	set_Led(LED_GREEN);
//	clear_Led(LED_RED);
//	SystickDelay(200);
//
//	set_Led(LED_RED);
//	clear_Led(LED_GREEN);
//	SystickDelay(200);
//
//}


// INTERRUPT NVIC

// + Exception Vector is Enable or Disable
// + Configure Exception Priority
// + Manage Exception State

//volatile bool Flag_mode = false ;
//
//
//
//void buttonIRQ_Handle(SWITCH_List SW){
//	Flag_mode = !Flag_mode;
//
//}
//
//volatile bool Flag_LPIT = false;
//
//void channel0IRQ_Handle(Channel_Type Channel)
//{
//	if (Channel == CHANNEL_0)	Flag_LPIT = !Flag_LPIT;
//
//
//}
//
//
//
//ADC_Config Adc_conf = {
//		.Async_CLK_Source = SOURCE_FIRCDIV2_CLK_ASYNC,
//		.AsyncClock_Divide = DIVIDE_1_ASYNC,
//		.mode_ADC_Trigger = SOFTWARE_TRIGGER,
//		.modeRead = READ_CONTINOUS,
//		.interrupt_ADC_status = INTERRUPT_ADC_ENABLE
//};
//
//
//// Synchoronous - Blocking
//// Asynchoronous - None Blocking
//
//void ADC0_IRQHandler(){
//	toggle_Led(LED_GREEN);
//}
volatile uint32_t data;

uint8_t dataRC ;
uint8_t data_;
int main(void)
{
	// PIT - Timer counter
	// - Generation Periodic Interrupt (Delay)
	// - Generation Periodic Trigger (Trigger ADC)
	// Start: Software/ Trigger input/ timeout
	// Clock: can configuration


	//ADC_Init(ADC0,&Adc_conf);
	//Enable_Intterupt_NVIC_ADC();


	//init_GPIO_System(SW2,&buttonIRQ_Handle);
	//EnableInterruptButton();

	//Init_timer_LPIT(CHANNEL_0,&channel0IRQ_Handle);
	//enable_interrupt_LPIT();

	UARTx_Config_t uartTest = {
			.baurate_uart = BAURATE_115200,
			.AsyncUART = SOURCE_FIRCDIV2_CLK_ASYNC,
			.Divide = DIVIDE_1_ASYNC

	};
	uint8_t txbuff[]   = "Lpuart polling example\r\nBoard will send back received characters\r\n";
	uint8_t txbuff_test[5];
	UART_Init(UART_0, &uartTest);
	uint8_t test_data = 0xA;
	//Enable_Interrupt_UART_Recive(UART_0);
	//FLASH_Write(0x5000, test_data);
	//UART_Transmit_Byte(UART_0,test_data);
	//UART_Receive_Buff(UART_0, txbuff_test, 5);
	//uint8_t dataRC = 0;
	uint8_t i = 0 ;
    while (1)
    {

    	delay(20);
    	UART_Receive_Byte(UART_0,&dataRC);
    	txbuff_test[i] = dataRC;
    	i++;
    	delay(20);
    	//data_ = dataRC;
    	//data =	Read_ADC(ADC0);
    	//SystickDelay(10);
    }
    //(void) data;
}
