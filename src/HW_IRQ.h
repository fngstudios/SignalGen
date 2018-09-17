/*

Electronica Digital 2
Unsam

Signal Generator

Ezequiel Pedace
V0.1  -  17/09/2018

*/


#ifndef HW_IRQ_H
#define HW_IRQ_H


void GPIO0_IRQHandler();
void GPIO1_IRQHandler();
void GPIO2_IRQHandler();
void GPIO3_IRQHandler();
void DMA_IRQHandler();
void Led_Write(int *ptr, int Pin_N);
void Generate_Signals();
void Configure_Leds();
void Configure_Buttons();
void IRQ_Init();
void DAC_Config();
void DMA_Config();

#endif //HW_IRQ_H