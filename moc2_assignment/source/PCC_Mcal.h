#ifndef PCC_MCAL_H
#define PCC_MCAL_H

#include "MKE16Z4.h"
#include "fsl_common.h"

typedef enum {

	DISABLE_SELECT_SOURCE_ASYNC = 0,
	SOURCE_FLLDIV2_CLK_ASYNC,
	SOURCE_SIRCDIV2_CLK_ASYNC,
	SOURCE_FIRCDIV2_CLK_ASYNC,
	SOURCE_SOSCDIV2_CLK_ASYNC

} Source_AsyncClock;


typedef enum {
	DIVIDE_DISABLE_ASYNC_ADC = 0,
	DIVIDE_1_ASYNC,
	DIVIDE_2_ASYNC,
	DIVIDE_4_ASYNC,
	DIVIDE_8_ASYNC,
	DIVIDE_16_ASYNC,
	DIVIDE_32_ASYNC,
	DIVIDE_64_ASYNC
}Divide_type;


status_t Enable_Clock_Module(uint8_t Module_index) ;

status_t Disable_Clock_Module(uint8_t Module_index);

void Select_Soure_Async_CLK(uint8_t Module_index, Source_AsyncClock sourceAsyncCLK, Divide_type divive_type);

#endif // PCC_MCAL_H
