/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AHB     0
#define RCC_APB1    1
#define RCC_APB2    2
/***************   APB2 BITS definition    ******************/
#define APB2_AFIO_EN         0
#define APB2_GPIOA_EN        2
#define APB2_GPIOB_EN        3
#define APB2_GPIOC_EN        4
#define APB2_GPIOD_EN        5
#define APB2_ADC1_EN         9
#define APB2_ADC2_EN         10
#define APB2_TIM1_EN         11
#define APB2_SPI1_EN         12
#define APB2_TIM8_EN         13
#define APB2_USART1_EN       14
#define APB2_ADC3_EN         15
/***************   APB1 BITS definition    ******************/
#define APB1_CAN_EN 25

/***************   Function definition    ******************/

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId);
void RCC_voidDisableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId);

#endif // RCC_INTERFACE_H
