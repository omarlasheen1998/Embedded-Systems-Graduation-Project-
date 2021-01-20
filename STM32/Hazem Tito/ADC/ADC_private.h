#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


/*****************REGISTER DEFINITIONS*****************************/

#define ADC1_SR     *((uint32*)0x40012400)
#define ADC1_CR1    *((uint32*)0x40012404)
#define ADC1_CR2    *((uint32*)0x40012408)
#define ADC1_SMPR1  *((uint32*)0x4001240C)
#define ADC1_SMPR2  *((uint32*)0x40012410)
#define ADC1_JOFR1  *((uint32*)0x40012414)
#define ADC1_JOFR2  *((uint32*)0x40012418)
#define ADC1_JOFR3  *((uint32*)0x4001241C)
#define ADC1_JOFR4  *((uint32*)0x40012420)
#define ADC1_HTR    *((uint32*)0x40012424)
#define ADC1_LTR    *((uint32*)0x40012428)
#define ADC1_SQR1   *((uint32*)0x4001242C)
#define ADC1_SQR2   *((uint32*)0x40012430)
#define ADC1_SQR3   *((uint32*)0x40012434)
#define ADC1_JSQR   *((uint32*)0x40012438)
#define ADC1_JDR1   *((uint32*)0x4001243C)
#define ADC1_JDR2   *((uint32*)0x40012440)
#define ADC1_JDR3   *((uint32*)0x40012444)
#define ADC1_JDR4   *((uint32*)0x40012448)
#define ADC1_DR     *((uint32*)0x4001244C)




/******the prescalar of the module*******/
#define CLK_DIVIDE_BY_2 0
#define CLK_DIVIDE_BY_4 1
#define CLK_DIVIDE_BY_6 2
#define CLK_DIVIDE_BY_8 3
/*******the sample rate of the channel****/
#define SAMP_1_CYCLES   0
#define SAMP_7_CYCLES   1
#define SAMP_13_CYCLES  2
#define SAMP_28_CYCLES  3
#define SAMP_41_CYCLES  4
#define SAMP_55_CYCLES  5
#define SAMP_71_CYCLES  6
#define SAMP_239_CYCLES 7


#endif
