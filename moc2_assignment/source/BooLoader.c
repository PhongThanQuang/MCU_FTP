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

/*
 * Global variable for srec
 */
int Srec_Length;
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
	return (uint32_t) queue[Write_Idx];
}

/*
 * @Description
 */
void Increase_Write_Idx() {
	if (!QUEUE_IsFull()) {
		Write_Idx++;
		Queue++;
		if (Write_Idx > BUFFER_FULL) {
			Write_Idx = 0;
		}
	}
}

uint32_t Get_Current_Read_Idx()
{
	return (uint32_t)queue[Read_Idx];
}

void Increase_Read_Idx()
{
	if(!QUEUE_Empty())
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
	initLed();
	/* Run baudrate 1000000 with FLL clock */
	UART0_Init(1000000);
    UART_SendString("\r\n  -- BOOTLOADER MODE --\r\n");
    UART_SendString("Send SREC file through terminal.\r\n");
    uint8_t add_new[9];
    uint8_t data_new[256];
	int i;
	int j;
    Fls_EraseMultiSector(INIT_DATA_MEMORY, 5);
    while (1)
    {
    	if(!QUEUE_Empty())
    	{
    	    uint8_t* myString = (uint8_t*)Get_Current_Read_Idx();
    		src_type = myString[1];
    		src_lenght = TwoChar_toByte(myString[2], myString[3])*2 + 4;
    		Add_lenght = add_lenght(src_type);
    		for (i = 0; i <  Add_lenght; i++)
    		    {
    		      arr_add[i]=myString[i+4];
    		    }
    		arr_add[Add_lenght] = '\0';
    		for (i = 0; i <  Add_lenght ; i+=2 )
    		{
    				add_new[i>>1] = TwoChar_toByte(arr_add[i], arr_add[i+1]);
    		}
    		Data_lenght = src_lenght - 6 - Add_lenght;
            for (j = 0; j <  Data_lenght; j++)
        	{
            	arr_data[j] = myString[j + 4 + Add_lenght];
        	}
            arr_data[Data_lenght] = '\0';
    		for (j = 0; j <  Data_lenght; j+=2 )
    		{
    				data_new[j>>1] = TwoChar_toByte(arr_data[j], arr_data[j+1]);
    		}
    		Increase_Read_Idx();
    		 if(src_type !='0')
    				   {
    					  Fls_Write(add_new, data_new, (Data_lenght/2));

    				   }
    		 if(src_type =='9')
    				   {
    			 	 	   UART_SendString("\r\n  -- APPLICATION MODE --\r\n");
    			 	 	    uint32_t reset_address = 0;
    					    pFunction jump_to_address;
    					    __disable_irq();
    					    /* Relocate exception vector table */
    					    SCB->VTOR = INIT_DATA_MEMORY;
    					    /* Set main stack pointer */
    					    SetMSP(*(uint32_t*)INIT_DATA_MEMORY);
    					    /* Reset interrupt handler address */
    					    reset_address = *(uint32_t*)(INIT_DATA_MEMORY + 4);
    					    /* Call reset interrupt handler */
    					    jump_to_address = (pFunction)(reset_address);
    					    /* Jump to application */
    					    jump_to_address();
    				   }
    		 src_lenght = 0;
    	}
    }
}

void UART0_IRQHandler(void)
{
	uint8_t* currentline = (uint8_t*)Get_Current_Write_Idx();
	static int i = 0;
	if (((UART0->S1 & UART_S1_RDRF_MASK) != 0) && (QUEUE_IsFull() == false))
	{
				currentline[i] = UART0->D;
                if( currentline[i] == '\r')
                {
                	Increase_Write_Idx();
                	i = 0;
                }
                else
                {
                	i++;
                }
	}
}
