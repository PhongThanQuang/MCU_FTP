#include <LPIT_Control.h>

funcCallBackLPIT func_interrupt_LPIT_Middleware;

void Func_CallBack_LPIT_MDW(Channel_Type Channel){

	func_interrupt_LPIT_Middleware(Channel);
}
void Init_timer_LPIT(Channel_Type Channel, funcCallBackLPIT func_interrupt_LPIT_App ){

	//	f = 1Mhz, Delay Time (200ms) = T * (reload - 1)
	//			reload = Time / T + 1 = 200001

	//Set up async clk
	Select_Soure_Async_CLK(PCC_LPIT0_INDEX,SOURCE_FIRCDIV2_CLK_ASYNC,DIVIDE_1_ASYNC);
	//CLOCK_EnableClock
	Enable_Clock_Module(PCC_LPIT0_INDEX);
	func_interrupt_LPIT_Middleware = func_interrupt_LPIT_App;

	LPIT_Config_t timer_LPIT_config_default ={
		.MCR_EN = PROTOCOL_CLOCK_ENABLE,
		.SETTEN_EN = CHANNEL_CLOCK_ENABLE,
		.interrupt_EN = TIMER_INTERRUPT_ENABLE,
		.debug_timer_mode_EN = DEBUG_ENABLE,
		.timerOpeMode = _32BIT_PER_COUNTER,
		.value_reload = 9600001,// 200ms ,
		.funcCallBackLPIT_t = Func_CallBack_LPIT_MDW
	};

	LPIT_Init(Channel,&timer_LPIT_config_default);
	LPIT_Start_Timer(Channel);
}

void enable_interrupt_LPIT(){
	Enable_Intterupt_NVIC(LPIT0_IRQn);
}

