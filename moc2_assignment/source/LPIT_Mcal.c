#include <LPIT_Mcal.h>

funcCallBackLPIT func_interrupt_LPIT_Mcal;

/*        LPIT Function        */
// Input: 	Clock / Reload value / Interrupt
// 			Mode: (single / chanied ) // SW or HW Trigger
void LPIT_Init(Channel_Type _channel, LPIT_Config_t *LPIT_config){

	// Clock (E) / Async Clock

	LPIT0->MCR |= LPIT_MCR_SW_RST_MASK;
	LPIT0->MCR &= ~LPIT_MCR_SW_RST_MASK;

	LPIT0->MCR |= (LPIT_MCR_M_CEN(LPIT_config->MCR_EN) | LPIT_MCR_DBG_EN(LPIT_config->debug_timer_mode_EN) | LPIT_MCR_DOZE_EN(1) ); // Turn on clock for module timer

	LPIT0->MIER |= LPIT_MIER_TIE0(LPIT_config->interrupt_EN); // Turn on interrupt channels 0

	LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_0(LPIT_config->SETTEN_EN); // Turn on policy setup for clock all channel

	LPIT0->CHANNEL[0].TCTRL |= LPIT_TCTRL_MODE(LPIT_config->timerOpeMode);

	LPIT0->CHANNEL[_channel].TVAL = LPIT_config->value_reload;

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_TRG_SEL(LPIT_config->trigger_select_channelx);

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_TRG_SRC(LPIT_config->triggerSource);

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_TROT(LPIT_config->timerReloadTrigger);

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_TSOI(LPIT_config->timerStopModeInterrupt);

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_TSOT(LPIT_config->timerStartModeTrigger);

	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_CHAIN(LPIT_config->timerChainEn);


	func_interrupt_LPIT_Mcal = LPIT_config->funcCallBackLPIT_t;


}

void LPIT_Start_Timer(Channel_Type _channel){
	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_T_EN(1);
}


void LPIT_Stop_Timer(Channel_Type _channel){
	LPIT0->CHANNEL[_channel].TCTRL |= LPIT_TCTRL_T_EN(0);
}


void LPIT0_IRQHandler(){

	if (LPIT0->MIER & LPIT_MIER_TIE0_MASK){
			func_interrupt_LPIT_Mcal(CHANNEL_0);
			LPIT0->MIER |= LPIT_MIER_TIE0(1);
	} else {
		if (LPIT0->MIER & LPIT_MIER_TIE1_MASK){
			func_interrupt_LPIT_Mcal(CHANNEL_1);
			LPIT0->MIER |= LPIT_MIER_TIE0(1);
		}
	}

}
//void Select_Soure_Async_CLK(Source_AsyncClock sourceAsyncCLK, Didive_type divive_type){
//
//
//		PCC->CLKCFG[PCC_LPIT0_INDEX] &= ~PCC_CLKCFG_PCS_MASK;
//		PCC->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_PCS(sourceAsyncCLK);
//
//		switch (sourceAsyncCLK) {
//			case DISABLE_SELECT_SOURCE_ASYNC :
//				// Nothing
//			break;
//			case SOURCE_FLLDIV2_CLK_ASYNC :
//				SCG->LPFLLDIV &= ~SCG_LPFLLDIV_LPFLLDIV2_MASK;
//				SCG->LPFLLDIV |= SCG_LPFLLDIV_LPFLLDIV2(divive_type);
//			break;
//
//			case SOURCE_SIRCDIV2_CLK_ASYNC :
//				SCG->SIRCDIV &= ~SCG_SIRCDIV_SIRCDIV2_MASK;
//				SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(divive_type);
//			break;
//
//			case SOURCE_FIRCDIV2_CLK_ASYNC :
//				SCG->FIRCDIV &= ~SCG_FIRCDIV_FIRCDIV2_MASK;
//				SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(divive_type);
//			break;
//
//			case SOURCE_SOSCDIV2_CLK_ASYNC :
//				SCG->SOSCDIV &= ~SCG_SOSCDIV_SOSCDIV2_MASK;
//				SCG->SOSCDIV |= SCG_SOSCDIV_SOSCDIV2(divive_type);
//			break;
//
//		}
//
//}
