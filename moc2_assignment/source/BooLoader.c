/*
 * BootLoader for Board KE16Z4
 * Created at: 26/12/2024
 */

#include "MKE16Z4.h"
#include "KE16_Flash.h"
#include "ADC_Mcal.h"
#include "GPIO_Control.h"
#include "GPIO_Mcal.h"
#include "LPIT_Control.h"
#include "LPIT_Mcal.h"
#include "NVIC_Mcal.h"
#include "PCC_Mcal.h"
#include "Port_Mcal.h"
#include "UART_Mcal.h"
#include "SREC.h"

/*
 * Global variable for srec
 */
int Srec_Length;
uint8_t Add_Length;
uint32_t Data_Length;
char Arr_Data[256], Arr_Add[256];
int Srec_Type;
/*
 * QUEUE
 */

/******Define*******/
#define INIT_MEMORY_DATA 0X8000
#define BUFFER_FULL 4
volatile uint8_t Read_Idx = 0;
volatile uint8_t Write_Idx = 0;
volatile uint8_t Queue = 0;
uint8_t Arr_Queue[100][100];

/*
 * @return bool
 */
bool Queue_isFull() {
	bool status = false;
	if (Queue > BUFFER_FULL) {
		status = true;
	}
	return status;
}

/*
 * @return bool
 */
bool Queue_isEmpty() {
	bool status = false;
	if (Queue == 0) {
		status = true;
	}
	return status;
}

/*
 * @initial : Write_Idx = 0
 * @return queue[Write_Idx]
 */
uint32_t Get_Current_Write_Idx() {
	return (uint32_t) Arr_Queue[Write_Idx];
}

/*
 * @Description
 */
void Increase_Write_Idx() {
	if (!Queue_isFull()) {
		Write_Idx++;
		Queue++;
		if (Write_Idx > BUFFER_FULL) {
			Write_Idx = 0;
		}
	}
}

uint32_t Get_Current_Read_Idx()
{
	return (uint32_t)Arr_Queue[Read_Idx];
}

void Increase_Read_Idx()
{
	if(!Queue_isEmpty())
	{
		Read_Idx++;
		Queue--;
		if(Read_Idx > BUFFER_FULL)
		{
			Read_Idx = 0;
		}
	}
}

/******************************************************************************
 *  Run app
 *****************************************************************************/

uint32_t ram_vector_table[48] __attribute__ ((aligned (0x100)));

void Vector_Table()
{
	uint32_t i;
	uint32_t* vector_table = (uint32_t*)(0x000);
	uint32_t* ram_table = ram_vector_table;
	for( i = 0; i < 48; i++)
	{
		ram_table[i] = vector_table[i];
	}
	SCB->VTOR = (uint32_t)ram_table;
}

__attribute__((naked)) void SetMSP(uint32_t newMSP);

typedef void(*pFunction)(void);

uint32_t ReadAdressSelfMain(uint32_t address)
{
	return (*(__IO uint32_t *) address);
}

__attribute__((naked)) void SetMSP(uint32_t newMSP)
{
	__asm("MSR PSP, R0");
	__asm("BX LR");
}

/******************************************************************************
 *  Main
 *****************************************************************************/

void main()
{
	Vector_Table();
//	initLed();
	/* Run baudrate 1000000 with FLL clock */
	UART0_Init(1000000);
    UART_SendString("\r\n  -- BOOTLOADER MODE --\r\n");
    UART_SendString("Send SREC file through terminal.\r\n");
    uint8_t add_new[9];
    uint8_t data_new[256];
	int i;
	int j;
    Fls_EraseMultiSector(INIT_MEMORY_DATA, 5);
    while (1)
    {
    	if(!QUEUE_Empty())
    	{
    	    uint8_t* myString = (uint8_t*)Get_Current_Read_Idx();
    		Srec_Type = myString[1];
    		Srec_Length = TwoChar_toByte(myString[2], myString[3])*2 + 4;
    		Add_Length = hex_to_byte(Srec_Type);
    		for (i = 0; i <  Add_Length; i++)
    		    {
    				Arr_Add[i]=myString[i+4];
    		    }
    		Arr_Add[Add_Length] = '\0';
    		for (i = 0; i <  Add_Length ; i+=2 )
    		{
    				add_new[i>>1] = TwoChar_toByte(Arr_Add[i], Arr_Add[i+1]);
    		}
    		Data_Length = Srec_Length - 6 - Add_Length;
            for (j = 0; j <  Data_Length; j++)
        	{
            	Arr_Add[j] = myString[j + 4 + Add_Length];
        	}
            Arr_Add[Data_Length] = '\0';
    		for (j = 0; j <  Data_Length; j+=2 )
    		{
    				data_new[j>>1] = TwoChar_toByte(Arr_Add[j], Arr_Add[j+1]);
    		}
    		Increase_Read_Idx();
    		 if(Srec_Type !='0')
    				   {
    					  FLASH_Write(add_new, data_new);

    				   }
    		 if(Srec_Type =='9')
    				   {
    			 	 	   UART_SendString("\r\n  -- APPLICATION MODE --\r\n");
    			 	 	    uint32_t reset_address = 0;
    					    pFunction jump_to_address;
    					    __disable_irq();
    					    /* Relocate exception vector table */
    					    SCB->VTOR = INIT_MEMORY_DATA;
    					    /* Set main stack pointer */
    					    SetMSP(*(uint32_t*)INIT_MEMORY_DATA);
    					    /* Reset interrupt handler address */
    					    reset_address = *(uint32_t*)(INIT_MEMORY_DATA + 4);
    					    /* Call reset interrupt handler */
    					    jump_to_address = (pFunction)(reset_address);
    					    /* Jump to application */
    					    jump_to_address();
    				   }
    		 Srec_Length = 0;
    	}
    }
}

void JumpToApplication(void) {
    uint32_t app_start_address = *(volatile uint32_t*)(INIT_MEMORY_DATA + 4);  // Vector Reset
    void (*app_reset_handler)(void) = (void (*)(void))app_start_address;

    __disable_irq();  // Vô hiệu hóa ngắt
    SCB->VTOR = INIT_MEMORY_DATA;  // Cập nhật bảng vector
    __set_MSP(*(volatile uint32_t*)APP_START_ADDRESS);  // Stack Pointer
    app_reset_handler();  // Nhảy vào ứng dụng
}


//void UART0_IRQHandler(void)
//{
//	uint8_t* currentline = (uint8_t*)Get_Current_Write_Idx();
//	static int i = 0;
//	if (((UART0->S1 & UART_S1_RDRF_MASK) != 0) && (QUEUE_IsFull() == false))
//	{
//				currentline[i] = UART0->D;
//                if( currentline[i] == '\r')
//                {
//                	Increase_Write_Idx();
//                	i = 0;
//                }
//                else
//                {
//                	i++;
//                }
//	}
//}
