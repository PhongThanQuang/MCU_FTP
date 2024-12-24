#ifndef LPIT_MCAL_H
#define	LPIT_MCAL_H

#include "MKE16Z4.h"
#include "fsl_common.h"
#include "PCC_Mcal.h"

#define SPEED_FIRC 48000000
#define SPEED_SIRC 8000000


typedef enum {
	CHANNEL_0 = 0,
	CHANNEL_1
}Channel_Type;



typedef enum {
	TRIGGER_CHANNEL_0_SELECT = 0,
	TRIGGER_CHANNEL_1_SELECT
	// ... Adjust in different Microcontroller
}CHANNELx_timer_trigger_select;

typedef enum {
	TRIGGER_SOURCE_EXTERNAL_SELECT = 0,
	TRIGGER_SOURCE_INTERNAL_SELECT

}Trigger_Source_Timer;

typedef enum {
	NOT_RELOAD_ON_TRIGGER = 0,
	RELOAD_ON_TRIGGER

}Timer_Reload_On_Trigger;


typedef enum {
	NOT_STOP_AFTER_TIMEOUT = 0,
	STOP_AFTER_TIMEOUT

}Timer_Stop_On_Interrupt;


typedef enum {
	START_ON_RESTART_CONDITION = 0,
	START_ON_TRIGGER_DETECT

}Timer_Start_On_Trigger;


typedef enum {
	_32BIT_PER_COUNTER = 0,
	DUAL_16BIT_PER_COUNTER,
	_32BIT_TRIGGER_ACCUMULATOR,
	_32BIT_TRIGGER_INPUT_CAP

}Timer_Operation_Mode;

typedef enum {
	CHAIN_DISABLE = 0,
	CHAIN_ENABLE

}Timer_Chain_Channel;

typedef enum {
	TIMER_CHANNEL_DISABLE = 0,
	TIMER_CHANNEL_ENABLE

}Timer_Channel_EN;


typedef enum {
	PROTOCOL_CLOCK_DISABLE = 0,
	PROTOCOL_CLOCK_ENABLE
}MCR_CEN_EN;


typedef enum {
	CHANNEL_CLOCK_NOT_CHANGE = 0,
	CHANNEL_CLOCK_ENABLE
}SETTEN_EN;

typedef enum {
	TIMER_INTERRUPT_DISABLE = 0,
	TIMER_INTERRUPT_ENABLE
}MIER_EN;


typedef enum {
	DEBUG_DISABLE = 0,
	DEBUG_ENABLE
}DBG_Timer_EN;

typedef void(*funcCallBackLPIT)(Channel_Type channel);

typedef struct {

	CHANNELx_timer_trigger_select trigger_select_channelx;
	Trigger_Source_Timer triggerSource;
	Timer_Reload_On_Trigger timerReloadTrigger;
	Timer_Stop_On_Interrupt timerStopModeInterrupt;
	Timer_Start_On_Trigger timerStartModeTrigger;
	Timer_Operation_Mode timerOpeMode;
	Timer_Chain_Channel timerChainEn;


	// SUA LAI TEN

	MCR_CEN_EN MCR_EN;
	SETTEN_EN SETTEN_EN;
	DBG_Timer_EN debug_timer_mode_EN;
	MIER_EN interrupt_EN;
	uint32_t value_reload;

	funcCallBackLPIT funcCallBackLPIT_t;

}LPIT_Config_t;


//typedef enum {
//
//	DISABLE_SELECT_SOURCE_ASYNC = 0,
//	SOURCE_FLLDIV2_CLK_ASYNC,
//	SOURCE_SIRCDIV2_CLK_ASYNC,
//	SOURCE_FIRCDIV2_CLK_ASYNC,
//	SOURCE_SOSCDIV2_CLK_ASYNC
//
//} Source_AsyncClock;
//
//typedef enum {
//	DIVIDE_DISABLE_ASYNC = 0,
//	DIVIDE_1_ASYNC,
//	DIVIDE_2_ASYNC,
//	DIVIDE_4_ASYNC,
//	DIVIDE_8_ASYNC,
//	DIVIDE_16_ASYNC,
//	DIVIDE_32_ASYNC,
//	DIVIDE_64_ASYNC
//}Didive_type;

//void Select_Soure_Async_CLK(Source_AsyncClock sourceAsyncCLK, Didive_type divive_type);


void LPIT_Init(Channel_Type _channel, LPIT_Config_t *timer_config);

void LPIT_Start_Timer(Channel_Type channle);

void LPIT_Stop_Timer(Channel_Type channle);

//void LPIT_Delay(Source_AsyncClock sourceAsyncClock,Channel _channel,uint32_t time_ms);
#endif
