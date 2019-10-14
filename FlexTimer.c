/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	21/03/2019
	\tomo
	    Add configuration structures.
 */


#include "FlexTimer.h"
#include "MK64F12.h"

void FTM0_IRQHandler(void)
{
//	uint32_t static tempPrev = 0;
//	uint32_t static temp = 0;
//	uint32_t diff = 0;
	uint32_t var0 = 0;
	//Copia de ejemplo 3.8 del PDF:

	//Void FTM0_ISR(void)
	if (FTM0->STATUS & 0x01)
	{
//		tempPrev = temp;
//		temp = FTM0->CNT; //read FTM0 counter register
//		diff = temp - tempPrev;
		FTM0->STATUS &= 0xFE; /* APAGA BANDERA DE HARDWARE */
		//read Hall sensor logic
		//The FTM0_CH0 channel is multiplexed with GPIOC1, read GPIOC1 logic
		var0 = GPIOC->PDIR;			  // Lee completo el GPIOC
		var0 = var0 & 0x80; // Mask del GPIOC en pin 7
		GPIOC->PTOR = 0x00000080; // ON y toogle
		asm("nop");
		//set a break point here
	}


}

void FlexTimer_Init()
{
	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	/**It enable the FTM*/
	FTM0->MODE |= FTM_MODE_FTMEN_MASK;
	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM0->CONF |= FTM_CONF_BDMMODE(3);
	/**Assign modulo register with a predefined value ---MOD EN 32,728--- */
	FTM0->MOD = 0x8000;
	/**Configure FlexTimer in output compare in ---SET OUTPUT ON MATCH--- mode*/
//	FTM0->CONTROLS[0].CnSC |= FTM_CnSC_CHIE(1);
	FTM0->CONTROLS[0].CnSC |= FTM_CnSC_MSA(1) | FTM_CnSC_ELSA(1) | FTM_CnSC_ELSB(1);
	/**Assign channel value register with a predefined value*/
	FTM0->CONTROLS[0].CnV = 0x8000;
	/**Select clock source and ---PRESCALER en 128--- */
//	FTM0->SC |= FTM_SC_TOIE(1);
	FTM0->SC |= FTM_SC_CLKS (FLEX_TIMER_CLKS_1) | FTM_SC_PS(FLEX_TIMER_PS_128);
}

