/*

Electronica Digital 2
Unsam

Signal Generator

Ezequiel Pedace

V0.1  -  17/09/2018

*/


#include "HW_IRQ.h"
#include "SignalGen.h"




int main(void) {

	
	Configure_Leds();
	Configure_Buttons();
	IRQ_Init();
	DAC_Config();
	DMA_Config();
	Generate_Signals();

	while (1) {
	}
}






