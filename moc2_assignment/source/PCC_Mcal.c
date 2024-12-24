#include "PCC_Mcal.h"


status_t Enable_Clock_Module(uint8_t Module_index) {

	PCC->CLKCFG[Module_index] |= PCC_CLKCFG_CGC(1);


}

status_t Disable_Clock_Module(uint8_t Module_index) {

	PCC->CLKCFG[Module_index] |= PCC_CLKCFG_CGC(0);


}


void Select_Soure_Async_CLK(uint8_t Module_index, Source_AsyncClock sourceAsyncCLK, Divide_type divive_type){


		PCC->CLKCFG[Module_index] &= ~PCC_CLKCFG_PCS_MASK;
		PCC->CLKCFG[Module_index] |= PCC_CLKCFG_PCS(3);

		switch (sourceAsyncCLK) {
			case DISABLE_SELECT_SOURCE_ASYNC:
				// Nothing
			break;
			case SOURCE_FLLDIV2_CLK_ASYNC:
				SCG->LPFLLDIV &= ~SCG_LPFLLDIV_LPFLLDIV2_MASK;
				SCG->LPFLLDIV |= SCG_LPFLLDIV_LPFLLDIV2(divive_type);
			break;

			case SOURCE_SIRCDIV2_CLK_ASYNC:
				SCG->SIRCDIV &= ~SCG_SIRCDIV_SIRCDIV2_MASK;
				SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(divive_type);
			break;

			case SOURCE_FIRCDIV2_CLK_ASYNC:
				SCG->FIRCDIV &= ~SCG_FIRCDIV_FIRCDIV2_MASK;
				SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(divive_type);
			break;

			case SOURCE_SOSCDIV2_CLK_ASYNC:
				SCG->SOSCDIV &= ~SCG_SOSCDIV_SOSCDIV2_MASK;
				SCG->SOSCDIV |= SCG_SOSCDIV_SOSCDIV2(divive_type);
			break;

		}

}
