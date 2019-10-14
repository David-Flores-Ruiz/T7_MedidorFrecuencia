/*
 * main_3_3.c
 *
 *  Created on: 13 oct 2019
 *      Author: Lanix
 */

#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"

int main(void)
{
	/** Configuration for pin 1 on port c.
	 * Output compare is on option 4 in the pin control register*/
	SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA | GPIO_CLOCK_GATING_PORTC;
	PORTC->PCR[1] = PORT_PCR_MUX(0x4);	// Channel 0
	PORTC->PCR[2] = PORT_PCR_MUX(0x4);	// Channel 1
	PORTC->PCR[3] = PORT_PCR_MUX(0x4);	// Channel 2
	PORTC->PCR[4] = PORT_PCR_MUX(0x4);	// Channel 3

	/**Pin control configuration of GPIOC pin7 as GPIO*/
	PORTC->PCR[7] = 0x00000100;
	/**Configures GPIOC pin7 as input */
	GPIOC->PDDR = 0x00000000;

	/**Initialization of FlexTimer in output compare mode*/
	//FlexTimer_Init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
//	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(FTM0_IRQ,PRIORITY_10);
	NVIC_global_enable_interrupts;


	//Copia de ejemplo 3.8 del PDF:

	//void singleCapture(void)
	SIM->SCGC6 |= 0x03000000; //enable FTM0 and FTM0 module clock
	SIM->SCGC5 |= 0x3E00; //enable port A/B/C/D/E clock

	FTM0->SC = 0x00;
	FTM0->CONTROLS[0].CnSC |= 0x04; //Capture on Rising Edge Only
	FTM0->COMBINE = 0x00; //clear
	//enable capture interrupt
	FTM0->CONTROLS[0].CnSC |= 0x40; //enable CH0 interrupt
	FTM0->SC |= 0x08;
	//in ISR of capture interrupt, read the FTM_c0V register to get the capture value

	for (;;) {

	}


	return 0;
}
