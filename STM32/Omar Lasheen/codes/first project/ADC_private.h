#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


/*****************REGISTER DEFINITIONS*****************************/

#define ADC1_SR     *((volatile u32*)0x40012400)
#define ADC1_CR1    *((volatile u32*)0x40012404)
#define ADC1_CR2    *((volatile u32*)0x40012408)
#define ADC1_SMPR1  *((volatile u32*)0x4001240C)
#define ADC1_SMPR2  *((volatile u32*)0x40012410)
#define ADC1_JOFR1  *((volatile u32*)0x40012414)
#define ADC1_JOFR2  *((volatile u32*)0x40012418)
#define ADC1_JOFR3  *((volatile u32*)0x4001241C)
#define ADC1_JOFR4  *((volatile u32*)0x40012420)
#define ADC1_HTR    *((volatile u32*)0x40012424)
#define ADC1_LTR    *((volatile u32*)0x40012428)
#define ADC1_SQR1   *((volatile u32*)0x4001242C)
#define ADC1_SQR2   *((volatile u32*)0x40012430)
#define ADC1_SQR3   *((volatile u32*)0x40012434)
#define ADC1_JSQR   *((volatile u32*)0x40012438)
#define ADC1_JDR1   *((volatile u32*)0x4001243C)
#define ADC1_JDR2   *((volatile u32*)0x40012440)
#define ADC1_JDR3   *((volatile u32*)0x40012444)
#define ADC1_JDR4   *((volatile u32*)0x40012448)
#define ADC1_DR     *((volatile u32*)0x4001244C)




/************************prescalar of ADC ***************/
/*options : DIVIDE_BY_2
 *          DIVIDE_BY_4
 *          DIVIDE_BY_6
 *          DIVIDE_BY_8
 */
#define CLK_DIVIDE_BY_2 2
#define CLK_DIVIDE_BY_4 4
#define CLK_DIVIDE_BY_6 6
#define CLK_DIVIDE_BY_8 8

/*******SAMPLE RATE OF THE CHANNEL *******/
/*options:  1.5_CYCLES
 *          7.5_CYCLES
 *          13.5_CYCLES
 *          28.5_CYCLES
 *          41.5_CYCLES
 *          55.5_CYCLES
 *          71.5_CYCLES
 *          239.5_CYCLES
 */
 
#define SAMP_1_CYCLES 1
#define SAMP_7_CYCLES 2
#define SAMP_13_CYCLES 3
#define SAMP_28_CYCLES 4
#define SAMP_41_CYCLES 5
#define SAMP_55_CYCLES 6
#define SAMP_71_CYCLES 7
#define SAMP_239_CYCLES 8










#endif
