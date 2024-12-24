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
#include "fsl_lpuart.h"
//#include "core_cm0plus.h"
//#include "ADC_Mcal.h"

#define DEMO_LPUART            LPUART0
#define DEMO_LPUART_CLKSRC     kCLOCK_ScgSysOscClk
#define DEMO_LPUART_CLK_FREQ   CLOCK_GetFreq(kCLOCK_ScgSysOscClk)
#define DEMO_LPUART_IRQn       LPUART0_IRQn
#define DEMO_LPUART_IRQHandler LPUART0_IRQHandler

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
uint8_t select_mode = 0;

int main(void)
{


    while (1)
    {
    	if (select_mode){
    			// Application mode
    		} else {
    			// transfer vector table from flash to ram


    			// Write new firmware


    			// jump to Application
    		}
    }
}


}
