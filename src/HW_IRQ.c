/*

Electronica Digital 2
Unsam

Signal Generator

Ezequiel Pedace
V0.1  -  17/09/2018

*/



#include "HW_IRQ.h"
#include "SignalGen.h"
#include "math.h"


LED LED1;
LED LED2;
LED LED3;
LED LEDB;
LED LEDG;
LED LEDR;

unsigned int S0[Signal_Samples], S1[Signal_Samples], S2[Signal_Samples], S3[Signal_Samples];
unsigned int Buffer_0[Signal_Samples], Buffer_1[Signal_Samples];
unsigned char S0_Enable,S1_Enable,S2_Enable,S3_Enable;
LLI_T LLI0, LLI1;







void GPIO0_IRQHandler(){

    static char status = 0;
	GPIO_PIN_IRQ->IST |= (1 << 0);			//IRQ Flag clear
	
	if (!status) {
		Led_Write(LEDB.set, LEDB.pin);		//LedB ON
		status=1;
		S0_Enable = 1;							
	}else{
		Led_Write(LEDB.clr, LEDB.pin);		//LedB OFF
		status=0;
		S0_Enable = 0;
	};	
};

void GPIO1_IRQHandler(){

    static char status = 0;
	GPIO_PIN_IRQ->IST |= (1 << 1);			//IRQ Flag clear
	
	if (!status) {
		Led_Write(LED1.set, LED1.pin);		//Led1 ON
		status=1;
		S1_Enable = 1;							
	}else{
		Led_Write(LED1.clr, LED1.pin);		//Led1 OFF
		status=0;
		S1_Enable = 0;
	};	
};

void GPIO2_IRQHandler(){

   static char status = 0;
	GPIO_PIN_IRQ->IST |= (1 << 2);			//IRQ Flag clear
	
	if (!status) {
		Led_Write(LED2.set, LED2.pin);		//Led2 ON
		status=1;
		S2_Enable = 1;							
	}else{
		Led_Write(LED2.clr, LED2.pin);		//Led2 OFF
		status=0;
		S2_Enable = 0;
	};	
};

void GPIO3_IRQHandler(){
	
	static char status = 0;
	GPIO_PIN_IRQ->IST |= (1 << 3);			//IRQ Flag clear
	
	if (!status) {
		Led_Write(LED3.set, LED3.pin);		//Led3 ON
		status=1;
		S3_Enable = 1;							
	}else{
		Led_Write(LED3.clr, LED3.pin);		//Led3 OFF
		status=0;
		S3_Enable = 0;
	};	
};

void DMA_IRQHandler(){
	
	int *PTR_DMA_INTTCCLEARG = (int *)(DMA_INTTCCLEAR);
	*PTR_DMA_INTTCCLEARG = 1;	// IRQ Flag clear
	
	if(DMA0->LLI == ((unsigned int)&LLI0)){
		for(int i=0; i < Signal_Samples; i++){
			Buffer_0[i] = S0_Enable*S0[i]+S1_Enable*S1[i]+S2_Enable*S2[i]+S3_Enable*S3[i];
		}
	}
	if(DMA0->LLI == ((unsigned int)&LLI1)){
		for(int i=0; i < Signal_Samples; i++){
			Buffer_1[i] = S0_Enable*S0[i]+S1_Enable*S1[i]+S2_Enable*S2[i]+S3_Enable*S3[i];
		}
	}
}

void Configure_Leds(){


	LED1.conf=(int *)((SCU_BASE)+(SFSP2_10));
	LED1.dir=(int *)((GPIO_BASE)+(GPIO_PORT0_DIR_OFFSET));
	LED1.clr=(int *)((GPIO_BASE)+(GPIO_PORT0_CLR_OFFSET));
	LED1.set=(int *)((GPIO_BASE)+(GPIO_PORT0_SET_OFFSET));
	LED1.pin=14;
	
	LED2.conf=(int *)((SCU_BASE)+(SFSP2_11));
	LED2.dir=(int *)((GPIO_BASE)+(GPIO_PORT1_DIR_OFFSET));
	LED2.clr=(int *)((GPIO_BASE)+(GPIO_PORT1_CLR_OFFSET));
	LED2.set=(int *)((GPIO_BASE)+(GPIO_PORT1_SET_OFFSET));
	LED2.pin=11;
	
	LED3.conf=(int *)((SCU_BASE)+(SFSP2_12));
	LED3.dir=(int *)((GPIO_BASE)+(GPIO_PORT1_DIR_OFFSET));
	LED3.clr=(int *)((GPIO_BASE)+(GPIO_PORT1_CLR_OFFSET));
	LED3.set=(int *)((GPIO_BASE)+(GPIO_PORT1_SET_OFFSET));
	LED3.pin=12;
		
	LEDB.conf=(int *)((SCU_BASE)+(SFSP2_2));
	LEDB.dir=(int *)((GPIO_BASE)+(GPIO_PORT5_DIR_OFFSET));
	LEDB.clr=(int *)((GPIO_BASE)+(GPIO_PORT5_CLR_OFFSET));
	LEDB.set=(int *)((GPIO_BASE)+(GPIO_PORT5_SET_OFFSET));
	LEDB.pin = 2;
	
	LEDG.conf = (int *)((SCU_BASE)+(SFSP2_1));
	LEDG.dir = (int *)((GPIO_BASE)+(GPIO_PORT5_DIR_OFFSET));
	LEDG.clr = (int *)((GPIO_BASE)+(GPIO_PORT5_CLR_OFFSET));
	LEDG.set = (int *)((GPIO_BASE)+(GPIO_PORT5_SET_OFFSET));
	LEDG.pin = 1;
	
	LEDR.conf = (int *)((SCU_BASE)+(SFSP2_0));
	LEDR.dir = (int *)((GPIO_BASE)+(GPIO_PORT5_DIR_OFFSET));
	LEDR.clr = (int *)((GPIO_BASE)+(GPIO_PORT5_CLR_OFFSET));
	LEDR.set = (int *)((GPIO_BASE)+(GPIO_PORT5_SET_OFFSET));
	LEDR.pin = 0;

	*(LED1.conf)=(0x1 << 4) | (0x0);
	*(LED2.conf)=(0x1 << 4) | (0x0);
	*(LED3.conf)=(0x1 << 4) | (0x0);
	*(LEDB.conf)=(0x1 << 4) | (0x4);
	*(LEDG.conf)=(0x1 << 4) | (0x4);
	*(LEDR.conf)=(0x1 << 4) | (0x4);
	
	*(LED1.dir)	|=	(1 << LED1.pin);
	*(LED2.dir)	|=	(1 << LED2.pin);
	*(LED3.dir)	|=	(1 << LED3.pin);
	*(LEDB.dir)	|=	(1 << LEDB.pin);
	*(LEDG.dir)	|=	(1 << LEDG.pin);
	*(LEDR.dir)	|=	(1 << LEDR.pin);
}

void Configure_Buttons(){

	BUTTON BUT_1;
	BUTTON BUT_2;
	BUTTON BUT_3;
	BUTTON BUT_4;


	BUT_1.conf = (int *)((SCU_BASE)+(SFSP1_0));
	BUT_1.dir = (int *)((GPIO_BASE)+(GPIO_PORT0_DIR_OFFSET));
	BUT_1.clr = (int *)((GPIO_BASE)+(GPIO_PORT0_CLR_OFFSET));
	BUT_1.set = (int *)((GPIO_BASE)+(GPIO_PORT0_SET_OFFSET));
	BUT_1.pin = 4;
	BUT_1.reg = (int *)((GPIO_BASE)+(GPIO0_4));
	
	
	BUT_2.conf = (int *)((SCU_BASE)+(SFSP1_1));
	BUT_2.dir = (int *)((GPIO_BASE)+(GPIO_PORT0_DIR_OFFSET));
	BUT_2.clr = (int *)((GPIO_BASE)+(GPIO_PORT0_CLR_OFFSET));
	BUT_2.set = (int *)((GPIO_BASE)+(GPIO_PORT0_SET_OFFSET));
	BUT_2.pin = 8;
	BUT_2.reg = (int *)((GPIO_BASE)+(GPIO0_8));
	
	
	BUT_3.conf = (int *)((SCU_BASE)+(SFSP1_2));
	BUT_3.dir = (int *)((GPIO_BASE)+(GPIO_PORT0_DIR_OFFSET));
	BUT_3.clr = (int *)((GPIO_BASE)+(GPIO_PORT0_CLR_OFFSET));
	BUT_3.set = (int *)((GPIO_BASE)+(GPIO_PORT0_SET_OFFSET));
	BUT_3.pin = 9;
	BUT_3.reg = (int *)((GPIO_BASE)+(GPIO0_9));
	

	BUT_4.conf = (int *)((SCU_BASE)+(SFSP1_6));
	BUT_4.dir = (int *)((GPIO_BASE)+(GPIO_PORT1_DIR_OFFSET));
	BUT_4.clr = (int *)((GPIO_BASE)+(GPIO_PORT1_CLR_OFFSET));
	BUT_4.set = (int *)((GPIO_BASE)+(GPIO_PORT1_SET_OFFSET));
	BUT_4.pin = 9;
	BUT_4.reg = (int *)((GPIO_BASE)+(GPIO1_9));
	
	
	*(BUT_1.conf)=(0x1 << 4) | (0x1 << 6);
	*(BUT_2.conf)=(0x1 << 4) | (0x1 << 6);
	*(BUT_3.conf)=(0x1 << 4) | (0x1 << 6);
	*(BUT_4.conf)=(0x1 << 4) | (0x1 << 6);
	

}

void IRQ_Init(){

	NVIC_T NVIC;
	NVIC.ISER0=(int *)((NVIC_BASE)+(ISER0_B));
	NVIC.ISER1=(int *)((NVIC_BASE)+(ISER1_B));
	NVIC.ICER0=(int *)((NVIC_BASE)+(ICER0_B));
	NVIC.ICER1=(int *)((NVIC_BASE)+(ICER1_B));
	
	*(NVIC.ISER0) = (1 << 2);
	*(NVIC.ISER1) = (1 << 0)|	//PIN_INT0 GPIO pin interrupt 0
					(1 << 1)|	//PIN_INT1 GPIO pin interrupt 1
					(1 << 2)|	//PIN_INT2 GPIO pin interrupt 2
					(1 << 3);	//PIN_INT3 GPIO pin interrupt 3
					
	//Pin interrupt select register
	int *PIN_IRQ=(int *)(SCU_PIN_IRQ_BASE);
	*PIN_IRQ=	(0x04)|						//GPIO0_4
				(0x08 << 8)|				//GPIO0_8
				(0x09 << 16)|				//GPIO0_9
				(0x09 << 24)|
				(0x01 << 29);				//GPIO1_9
	
	//GPIO pin interupts
	
	GPIO_PIN_IRQ->ISEL=(0x00);
	GPIO_PIN_IRQ->IENF= (1 << 0)|	
					 	(1 << 1)|	
					 	(1 << 2)|	
					 	(1 << 3);		
	GPIO_PIN_IRQ->SIENF=	(1 << 0)|	
							(1 << 1)|	
							(1 << 2)|	
							(1 << 3);	
	GPIO_PIN_IRQ->IENR=(0x00);
	GPIO_PIN_IRQ->SIENR=(0x00);

}

void DAC_Config(){

	int *PTR_ENAIO2 =(int *)(ENAIO2);
	DAC->CTRL = (0x00 << 0)|(0x01 << 1)|(0x01 << 2)|(0x01 << 3);
	DAC->CNTVAL = (816);    //204MHz / 816 = 250KHz   SIGNAL UPDATE RATE
	*PTR_ENAIO2 = 1; 

}

void DMA_Config(){

int *PTR_DMA_CONFIG_GENERAL = (int *)(DMA_CONFIG_GRAL);
	*PTR_DMA_CONFIG_GENERAL = 1;	//Config. general
unsigned int DMA_CONTROL_MASK=0;	

	DMA_CONTROL_MASK =	 	( 0x80 	<<  0 )		//TRANSFER_SIZE
						|	( 0x00 	<< 12 )		//SB_SIZE
						|	( 0x00 	<< 15 )		//DB_SIZE
						|	( 0x02	<< 18 )		//S_WIDTH
						|	( 0x02	<< 21 )		//D_WIDTH
						|	( 0x00 	<< 24 )		//S	
						|	( 0x01 	<< 25 )		//D
						|	( 0x01 	<< 26 )		//SI
						|	( 0x00 	<< 27 )		//DI	
						|	( 0x00 	<< 28 )		//PROT1
						|	( 0x00 	<< 29 )		//PROT2
						|	( 0x00 	<< 30 )		//PROT3
						|	( 0x01 	<< 31 );	//I
	

	

	
	/** LLI **/
	
	LLI0.source = (unsigned int) &Buffer_0[0];
	LLI0.destination = (unsigned int) &DAC->CR;
	LLI0.next = (unsigned int) &LLI1;
	LLI0.control = DMA_CONTROL_MASK;
	
	LLI1.source = (unsigned int) &Buffer_1[0];
	LLI1.destination = (unsigned int) &DAC->CR;
	LLI1.next = (unsigned int) &LLI0;
	LLI1.control = DMA_CONTROL_MASK;
	
	DMA0->SRCADDR	= (unsigned int) &Buffer_0[0];
	DMA0->DESTADDR	= (unsigned int) &DAC->CR;
	DMA0->LLI		= (unsigned int) &LLI1;
	DMA0->CNTRL		= (unsigned int) DMA_CONTROL_MASK;
	DMA0->CONFIG 	=	( 0x01 <<  0 )	// E Channel enable
					|	( 0x0F <<  6 )	// DESTPERIPHERAL DAC
					|	( 0x01 << 11 )	// FLOWCNTRL m2p (DMA control)
					|	( 0x00 << 14 )	// IE
					|	( 0x01 << 15 )	// ITC
					|	( 0x00 << 16 )	// L		
					|	( 0x00 << 18 );	// H enable DMA request

}


void Generate_Signals(){
	float pi = 3.14159654;
	for(int i=0; i < Signal_Samples; i++){
		S0[i] = (int)(float)(DAC_MID_VALUE+(DAC_MID_VALUE*sin(( 1*2*pi*i)/Signal_Samples)));//2KHz
		S1[i] = (int)(float)(DAC_MID_VALUE+(DAC_MID_VALUE*sin(( 2*2*pi*i)/Signal_Samples)));//4KHz
		S2[i] = (int)(float)(DAC_MID_VALUE+(DAC_MID_VALUE*sin(( 4*2*pi*i)/Signal_Samples)));//8KHz
		S3[i] = (int)(float)(DAC_MID_VALUE+(DAC_MID_VALUE*sin(( 8*2*pi*i)/Signal_Samples)));//16KHz
	}
	for(int i=0; i < Signal_Samples; i++){   //Correccion ver PAG 1351
		S0[i] = (S0[i] << 6 ) | (1<<16);
		S1[i] = (S1[i] << 6 ) | (1<<16);
		S2[i] = (S2[i] << 6 ) | (1<<16);
		S3[i] = (S3[i] << 6 ) | (1<<16);
	}
}

void Led_Write(int *ptr, int Pin_N){	
	*ptr |= (1 << Pin_N);
}


