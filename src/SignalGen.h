/*

Electronica Digital 2
Unsam

Signal Generator

Ezequiel Pedace
V0.1  -  17/09/2018

*/

#ifndef SIGNAL_GEN_H
#define SIGNAL_GEN_H

//----------BASE REGISTERS------------


#define SCU_BASE			0x40086000	
#define GPIO_BASE			0x400F4000
#define SCU_PIN_IRQ_BASE	0x40086E00
#define GPIO_PIN_IRQ_BASE	0x40087000
#define DAC_BASE			0x400E1000
#define NVIC_BASE			0xE000E000


//--------------I/O-----------------------

#define	SFSP2_10	0x128	//LED 1
#define	SFSP2_11	0x12C	//LED 2
#define	SFSP2_12	0x130	//LED 3
#define	SFSP2_0		0x100	//LED R
#define	SFSP2_1		0x104	//LED G
#define	SFSP2_2		0x108	//LED B

#define SFSP1_0		0x080	//BUTTON 1
#define SFSP1_1		0x084	//BUTTON 2
#define SFSP1_2		0x088	//BUTTON 3
#define SFSP1_6		0x098	//BUTTON 4

#define GPIO0_4		0x004	//BUTTON 1
#define GPIO0_8		0x008	//BUTTON 2
#define GPIO0_9		0x009	//BUTTON 3
#define GPIO1_9		0x029	//BUTTON 4


#define	GPIO_PORT0_DIR_OFFSET	0x2000	
#define GPIO_PORT0_CLR_OFFSET	0x2280	//LED 1
#define GPIO_PORT0_SET_OFFSET	0x2200	

#define	GPIO_PORT1_DIR_OFFSET	0x2004	
#define GPIO_PORT1_CLR_OFFSET	0x2284	//LED 2 y 3
#define GPIO_PORT1_SET_OFFSET	0x2204	

#define	GPIO_PORT5_DIR_OFFSET	0x2014	
#define GPIO_PORT5_CLR_OFFSET	0x2294	//LED RGB
#define GPIO_PORT5_SET_OFFSET	0x2214	

#define GPIO_PIN_IRQ	((GPIO_PIN_IRQ_STRUCT *)GPIO_PIN_IRQ_BASE)

/**NVIC**/

#define ISER0_B			0x100
#define ISER1_B			0x104
#define ICER0_B			0x180
#define ICER1_B			0x184

/**DAC**/

#define ENAIO2			0x40086C90		// Analog output enable
#define DAC				((DAC_STRUCT *)DAC_BASE)

/**DMA**/

#define DMA0			((DMA_STRUCT *)DMA_SRCADDR0)

#define DMA_SRCADDR0		0x40002100	// DMA Channel 0 Source Address Register
#define DMA_CONFIG_GRAL		0x40002030	// DMA Config
#define DMA_INTSTAT_GRAL	0x40002000	// DMA Interrupt Status register
#define DMA_ENABLEDCHANELS	0x4000201C	// DMA enabled channels

#define DMA_INTSTAT			0x40002000	// DMA Interrupt Status Register
#define DMA_INTTCCLEAR		0x40002008	// DMA Interrupt Terminal Count Request Clear Register

#define Signal_Samples 		512
#define Signal_Samples_Cycle Signal_Samples/2
#define DAC_TOP_VALUE		254
#define DAC_MID_VALUE 		DAC_TOP_VALUE/2


#define DEBUGING 1

/* LEDs */

typedef struct LED{
	int *conf;
	int *dir;
	int *clr;
	int *set;
	int pin;
}LED;

/* BUTTONs */

typedef struct BUTTON{
	int *conf;
	int *dir;
	int *clr;
	int *set;
	int pin;
	int *reg;
}BUTTON;

/* NVIC */

typedef struct NVIC_T{
	int *ISER0;
	int *ISER1;
	int *ICER0;
	int *ICER1;
}NVIC_T;

/* Interrupciones */

typedef struct{
	unsigned int ISEL;
	unsigned int IENR;
	unsigned int SIENR;
	unsigned int CIENR;
	unsigned int IENF;
	unsigned int SIENF;
	unsigned int CIENF;
	unsigned int RISE;
	unsigned int FALL;
	unsigned int IST;
}GPIO_PIN_IRQ_STRUCT;

/* DAC */

typedef struct{
	unsigned int CR;
	unsigned int CTRL;
	unsigned int CNTVAL;
}DAC_STRUCT;

/* DMA structure */

typedef struct{
	unsigned int SRCADDR;
	unsigned int DESTADDR;
	unsigned int LLI;
	unsigned int CNTRL;
	unsigned int CONFIG;
}DMA_STRUCT;

/* LLI */

typedef struct LLI_T {
 unsigned int  source;		
 unsigned int  destination; 
 unsigned int  next;        
 unsigned int  control;     
}LLI_T;


#endif //SIGNAL_GEN_H