#ifndef BOOTLOADER_HANDLE_H
#define	BOOTLOADER_HANDLE_H
#include "UART_Mcal.h"
#include "Srec.h"
#include "KE16_Flash.h"

typedef enum {
	APPLICATION_MODE = 0,
	BOOT_MODE
}Mode_active_t;

void array_to_uint32_array(uint8_t *array, uint32_t *output);
void ReceiveData_UART(uint8_t Data,SREC_Record *record);
void writeNewFirware(uint32_t address, uint8_t *Data);
#endif
