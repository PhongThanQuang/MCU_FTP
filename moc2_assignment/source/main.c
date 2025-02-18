/*
 * BootLoader for Board KE16Z4
 */
#include <GPIO_Control.h>
#include <LPIT_Control.h>
#include "stdint.h"
#include "UART_Mcal.h"
#include "KE16_Flash.h"
//#include "fsl_lpuart.h"
#include "BootLoader_Handle.h"
#include "Srec.h"
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
void jump_To_Application(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(uint8_t time) {
	volatile uint32_t i = 0;
	for (i = 0; i < 480000; ++i) {
		__asm("NOP");
		/* delay */
	}
}

/*!
 * @brief Main function
 */
#define ADDRESS_NEW_FIRMWARE 0x2000

Mode_active_t modeActive;
SREC_Record SREC_New_Firm;

uint8_t Mode_Select = 0;
uint8_t data_rx;
uint8_t idx_hex;
uint32_t Value_only_register[4] = { -1 };
uint8_t flag_completed_receive_one_line = 1;

typedef void (*pFunction)(void);

void LPUART0_IRQHandler() {

	data_rx = LPUART0->DATA;
	ReceiveData_UART(data_rx, &SREC_New_Firm);
	array_to_uint32_array(SREC_New_Firm.data, Value_only_register);
	flag_completed_receive_one_line = 1;
}

int main(void) {
	UARTx_Config_t uartDefault = { .baurate_uart = BAURATE_115200, .AsyncUART =
			SOURCE_FIRCDIV2_CLK_ASYNC, .Divide = DIVIDE_1_ASYNC };
	UART_Init(UART_0, &uartDefault);
	Enable_Interrupt_UART_Recive(UART_0);
	modeActive = BOOT_MODE; // Always boot mode
	while (1) {
		if (Mode_Select == 1) {
			// Application mode
			jump_To_Application();
		} else {
			// transfer vector table from flash to ram

			// Write new firmware
			// - Send ack to confirm started
			// Receive new firware
			switch (SREC_New_Firm.type) {
			case '0':
			case '1':
				for (uint8_t i = 0; i < 4; i++) {
					if (Value_only_register[i] != -1) {
						FLASH_Write(SREC_New_Firm.address + (i * 4),
								Value_only_register[i]);
						Value_only_register[i] = -1;
					}
				}

				break;
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Mode_Select = 1;
				break;

			}

			// jump to Application
		}
	}
}

void jump_To_Application() {
//	uint32_t reset_address = 0;
//	pFunction jump_to_address;
//	__disable_irq();
//	/* Relocate exception vector table */
//	SCB->VTOR = INIT_MEMORY_DATA;
//	/* Set main stack pointer */
//	SetMSP(*(uint32_t*) INIT_MEMORY_DATA);
//	/* Reset interrupt handler address */
//	reset_address = *(uint32_t*) (INIT_MEMORY_DATA + 4);
//	/* Call reset interrupt handler */
//	jump_to_address = (pFunction) (reset_address);
//	/* Jump to application */
//	jump_to_address();

	uint32_t app_start_address = *(volatile uint32_t*) (INIT_MEMORY_DATA + 4); // Vector Reset
	void (*app_reset_handler)(void) = (void (*)(void))app_start_address;

	__disable_irq();  // Vô hiệu hóa ngắt
	SCB->VTOR = INIT_MEMORY_DATA;  // Cập nhật bảng vector
	__set_MSP(*(volatile uint32_t*) APP_START_ADDRESS);  // Stack Pointer
	app_reset_handler();
}
