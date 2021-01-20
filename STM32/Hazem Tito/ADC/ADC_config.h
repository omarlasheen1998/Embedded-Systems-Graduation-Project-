#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/************************prescalar of ADC ***************/
/*options : DIVIDE_BY_2
 *          DIVIDE_BY_4
 *          DIVIDE_BY_6
 *          DIVIDE_BY_8
 */
#define ADC_PRESC  CLK_DIVIDE_BY_6

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
#define ADC_SAMP_RATE  SAMP_239_CYCLES




#endif
