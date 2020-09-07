/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 3 SEP 2020                   */
/* Version  : V01                           */
/********************************************/



#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/* PORT LOCK */
#define PORT_LOCK   0x4C4F434B


/* BUS ID */

#define APB     0
#define AHB     1

/* Operation Modes */

#define RUN_MODE            0
#define SLEEP_MODE          1
#define DEEP_SLEEP_MODE     2



/* Clock Gating for GPIO Registers Definition */

#define  SYSCTL_RCGCGPIO            *((volatile uint32 *) 0x400FE608)
#define  SYSCTL_SCGCGPIO            *((volatile uint32 *) 0x400FE708)
#define  SYSCTL_DCGCGPIO            *((volatile uint32 *) 0x400FE808)


/* Registers Definition */

// GPIO PORTA APB Registers --> Base Address = 0x40004000

#define  GPIO_APB_PORTA_GPIODATA            *((volatile uint32 *) 0x400043FC)
#define  GPIO_APB_PORTA_GPIODIR             *((volatile uint32 *) 0x40004400)
#define  GPIO_APB_PORTA_GPIOIS              *((volatile uint32 *) 0x40004404)
#define  GPIO_APB_PORTA_GPIOIBE             *((volatile uint32 *) 0x40004408)
#define  GPIO_APB_PORTA_GPIOIEV             *((volatile uint32 *) 0x4000440C)
#define  GPIO_APB_PORTA_GPIOIM              *((volatile uint32 *) 0x40004410)
#define  GPIO_APB_PORTA_GPIORIS             *((volatile uint32 *) 0x40004414)
#define  GPIO_APB_PORTA_GPIOMIS             *((volatile uint32 *) 0x40004418)
#define  GPIO_APB_PORTA_GPIOICR             *((volatile uint32 *) 0x4000441C)
#define  GPIO_APB_PORTA_GPIOAFSEL           *((volatile uint32 *) 0x40004420)
#define  GPIO_APB_PORTA_GPIODR2R            *((volatile uint32 *) 0x40004500)
#define  GPIO_APB_PORTA_GPIODR4R            *((volatile uint32 *) 0x40004504)
#define  GPIO_APB_PORTA_GPIODR8R            *((volatile uint32 *) 0x40004508)
#define  GPIO_APB_PORTA_GPIOODR             *((volatile uint32 *) 0x4000450C)
#define  GPIO_APB_PORTA_GPIOPUR             *((volatile uint32 *) 0x40004510)
#define  GPIO_APB_PORTA_GPIOPDR             *((volatile uint32 *) 0x40004514)
#define  GPIO_APB_PORTA_GPIOSLR             *((volatile uint32 *) 0x40004518)
#define  GPIO_APB_PORTA_GPIODEN             *((volatile uint32 *) 0x4000451C)
#define  GPIO_APB_PORTA_GPIOLOCK            *((volatile uint32 *) 0x40004520)
#define  GPIO_APB_PORTA_GPIOCR              *((volatile uint32 *) 0x40004524)
#define  GPIO_APB_PORTA_GPIOAMSEL           *((volatile uint32 *) 0x40004528)
#define  GPIO_APB_PORTA_GPIOPCTL            *((volatile uint32 *) 0x4000452C)
#define  GPIO_APB_PORTA_GPIOADCCTL          *((volatile uint32 *) 0x40004530)
#define  GPIO_APB_PORTA_GPIODMACTL          *((volatile uint32 *) 0x40004534)
#define  GPIO_APB_PORTA_GPIOPeriphlD4       *((volatile uint32 *) 0x40004FD0)
#define  GPIO_APB_PORTA_GPIOPeriphlD5       *((volatile uint32 *) 0x40004FD4)
#define  GPIO_APB_PORTA_GPIOPeriphlD6       *((volatile uint32 *) 0x40004FD8)
#define  GPIO_APB_PORTA_GPIOPeriphlD7       *((volatile uint32 *) 0x40004FDC)
#define  GPIO_APB_PORTA_GPIOPeriphlD0       *((volatile uint32 *) 0x40004FE0)
#define  GPIO_APB_PORTA_GPIOPeriphlD1       *((volatile uint32 *) 0x40004FE4)
#define  GPIO_APB_PORTA_GPIOPeriphlD2       *((volatile uint32 *) 0x40004FE8)
#define  GPIO_APB_PORTA_GPIOPeriphlD3       *((volatile uint32 *) 0x40004FEC)
#define  GPIO_APB_PORTA_GPIOPCellID0        *((volatile uint32 *) 0x40004FF0)
#define  GPIO_APB_PORTA_GPIOPCellID1        *((volatile uint32 *) 0x40004FF4)
#define  GPIO_APB_PORTA_GPIOPCellID2        *((volatile uint32 *) 0x40004FF8)
#define  GPIO_APB_PORTA_GPIOPCellID3        *((volatile uint32 *) 0x40004FFC)


// GPIO PORTB APB Registers --> Base Address = 0x40005000

#define  GPIO_APB_PORTB_GPIODATA            *((volatile uint32 *) 0x400053FC)
#define  GPIO_APB_PORTB_GPIODIR             *((volatile uint32 *) 0x40005400)
#define  GPIO_APB_PORTB_GPIOIS              *((volatile uint32 *) 0x40005404)
#define  GPIO_APB_PORTB_GPIOIBE             *((volatile uint32 *) 0x40005408)
#define  GPIO_APB_PORTB_GPIOIEV             *((volatile uint32 *) 0x4000540C)
#define  GPIO_APB_PORTB_GPIOIM              *((volatile uint32 *) 0x40005410)
#define  GPIO_APB_PORTB_GPIORIS             *((volatile uint32 *) 0x40005414)
#define  GPIO_APB_PORTB_GPIOMIS             *((volatile uint32 *) 0x40005418)
#define  GPIO_APB_PORTB_GPIOICR             *((volatile uint32 *) 0x4000541C)
#define  GPIO_APB_PORTB_GPIOAFSEL           *((volatile uint32 *) 0x40005420)
#define  GPIO_APB_PORTB_GPIODR2R            *((volatile uint32 *) 0x40005500)
#define  GPIO_APB_PORTB_GPIODR4R            *((volatile uint32 *) 0x40005504)
#define  GPIO_APB_PORTB_GPIODR8R            *((volatile uint32 *) 0x40005508)
#define  GPIO_APB_PORTB_GPIOODR             *((volatile uint32 *) 0x4000550C)
#define  GPIO_APB_PORTB_GPIOPUR             *((volatile uint32 *) 0x40005510)
#define  GPIO_APB_PORTB_GPIOPDR             *((volatile uint32 *) 0x40005514)
#define  GPIO_APB_PORTB_GPIOSLR             *((volatile uint32 *) 0x40005518)
#define  GPIO_APB_PORTB_GPIODEN             *((volatile uint32 *) 0x4000551C)
#define  GPIO_APB_PORTB_GPIOLOCK            *((volatile uint32 *) 0x40005520)
#define  GPIO_APB_PORTB_GPIOCR              *((volatile uint32 *) 0x40005524)
#define  GPIO_APB_PORTB_GPIOAMSEL           *((volatile uint32 *) 0x40005528)
#define  GPIO_APB_PORTB_GPIOPCTL            *((volatile uint32 *) 0x4000552C)
#define  GPIO_APB_PORTB_GPIOADCCTL          *((volatile uint32 *) 0x40005530)
#define  GPIO_APB_PORTB_GPIODMACTL          *((volatile uint32 *) 0x40005534)
#define  GPIO_APB_PORTB_GPIOPeriphlD4       *((volatile uint32 *) 0x40005FD0)
#define  GPIO_APB_PORTB_GPIOPeriphlD5       *((volatile uint32 *) 0x40005FD4)
#define  GPIO_APB_PORTB_GPIOPeriphlD6       *((volatile uint32 *) 0x40005FD8)
#define  GPIO_APB_PORTB_GPIOPeriphlD7       *((volatile uint32 *) 0x40005FDC)
#define  GPIO_APB_PORTB_GPIOPeriphlD0       *((volatile uint32 *) 0x40005FE0)
#define  GPIO_APB_PORTB_GPIOPeriphlD1       *((volatile uint32 *) 0x40005FE4)
#define  GPIO_APB_PORTB_GPIOPeriphlD2       *((volatile uint32 *) 0x40005FE8)
#define  GPIO_APB_PORTB_GPIOPeriphlD3       *((volatile uint32 *) 0x40005FEC)
#define  GPIO_APB_PORTB_GPIOPCellID0        *((volatile uint32 *) 0x40005FF0)
#define  GPIO_APB_PORTB_GPIOPCellID1        *((volatile uint32 *) 0x40005FF4)
#define  GPIO_APB_PORTB_GPIOPCellID2        *((volatile uint32 *) 0x40005FF8)
#define  GPIO_APB_PORTB_GPIOPCellID3        *((volatile uint32 *) 0x40005FFC)


// GPIO PORTC APB Registers --> Base Address = 0x40006000

#define  GPIO_APB_PORTC_GPIODATA            *((volatile uint32 *) 0x400063FC)
#define  GPIO_APB_PORTC_GPIODIR             *((volatile uint32 *) 0x40006400)
#define  GPIO_APB_PORTC_GPIOIS              *((volatile uint32 *) 0x40006404)
#define  GPIO_APB_PORTC_GPIOIBE             *((volatile uint32 *) 0x40006408)
#define  GPIO_APB_PORTC_GPIOIEV             *((volatile uint32 *) 0x4000640C)
#define  GPIO_APB_PORTC_GPIOIM              *((volatile uint32 *) 0x40006410)
#define  GPIO_APB_PORTC_GPIORIS             *((volatile uint32 *) 0x40006414)
#define  GPIO_APB_PORTC_GPIOMIS             *((volatile uint32 *) 0x40006418)
#define  GPIO_APB_PORTC_GPIOICR             *((volatile uint32 *) 0x4000641C)
#define  GPIO_APB_PORTC_GPIOAFSEL           *((volatile uint32 *) 0x40006420)
#define  GPIO_APB_PORTC_GPIODR2R            *((volatile uint32 *) 0x40006500)
#define  GPIO_APB_PORTC_GPIODR4R            *((volatile uint32 *) 0x40006504)
#define  GPIO_APB_PORTC_GPIODR8R            *((volatile uint32 *) 0x40006508)
#define  GPIO_APB_PORTC_GPIOODR             *((volatile uint32 *) 0x4000650C)
#define  GPIO_APB_PORTC_GPIOPUR             *((volatile uint32 *) 0x40006510)
#define  GPIO_APB_PORTC_GPIOPDR             *((volatile uint32 *) 0x40006514)
#define  GPIO_APB_PORTC_GPIOSLR             *((volatile uint32 *) 0x40006518)
#define  GPIO_APB_PORTC_GPIODEN             *((volatile uint32 *) 0x4000651C)
#define  GPIO_APB_PORTC_GPIOLOCK            *((volatile uint32 *) 0x40006520)
#define  GPIO_APB_PORTC_GPIOCR              *((volatile uint32 *) 0x40006524)
#define  GPIO_APB_PORTC_GPIOAMSEL           *((volatile uint32 *) 0x40006528)
#define  GPIO_APB_PORTC_GPIOPCTL            *((volatile uint32 *) 0x4000652C)
#define  GPIO_APB_PORTC_GPIOADCCTL          *((volatile uint32 *) 0x40006530)
#define  GPIO_APB_PORTC_GPIODMACTL          *((volatile uint32 *) 0x40006534)
#define  GPIO_APB_PORTC_GPIOPeriphlD4       *((volatile uint32 *) 0x40006FD0)
#define  GPIO_APB_PORTC_GPIOPeriphlD5       *((volatile uint32 *) 0x40006FD4)
#define  GPIO_APB_PORTC_GPIOPeriphlD6       *((volatile uint32 *) 0x40006FD8)
#define  GPIO_APB_PORTC_GPIOPeriphlD7       *((volatile uint32 *) 0x40006FDC)
#define  GPIO_APB_PORTC_GPIOPeriphlD0       *((volatile uint32 *) 0x40006FE0)
#define  GPIO_APB_PORTC_GPIOPeriphlD1       *((volatile uint32 *) 0x40006FE4)
#define  GPIO_APB_PORTC_GPIOPeriphlD2       *((volatile uint32 *) 0x40006FE8)
#define  GPIO_APB_PORTC_GPIOPeriphlD3       *((volatile uint32 *) 0x40006FEC)
#define  GPIO_APB_PORTC_GPIOPCellID0        *((volatile uint32 *) 0x40006FF0)
#define  GPIO_APB_PORTC_GPIOPCellID1        *((volatile uint32 *) 0x40006FF4)
#define  GPIO_APB_PORTC_GPIOPCellID2        *((volatile uint32 *) 0x40006FF8)
#define  GPIO_APB_PORTC_GPIOPCellID3        *((volatile uint32 *) 0x40006FFC)


// GPIO PORTD APB Registers --> Base Address = 0x40007000

#define  GPIO_APB_PORTD_GPIODATA            *((volatile uint32 *) 0x400073FC)
#define  GPIO_APB_PORTD_GPIODIR             *((volatile uint32 *) 0x40007400)
#define  GPIO_APB_PORTD_GPIOIS              *((volatile uint32 *) 0x40007404)
#define  GPIO_APB_PORTD_GPIOIBE             *((volatile uint32 *) 0x40007408)
#define  GPIO_APB_PORTD_GPIOIEV             *((volatile uint32 *) 0x4000740C)
#define  GPIO_APB_PORTD_GPIOIM              *((volatile uint32 *) 0x40007410)
#define  GPIO_APB_PORTD_GPIORIS             *((volatile uint32 *) 0x40007414)
#define  GPIO_APB_PORTD_GPIOMIS             *((volatile uint32 *) 0x40007418)
#define  GPIO_APB_PORTD_GPIOICR             *((volatile uint32 *) 0x4000741C)
#define  GPIO_APB_PORTD_GPIOAFSEL           *((volatile uint32 *) 0x40007420)
#define  GPIO_APB_PORTD_GPIODR2R            *((volatile uint32 *) 0x40007500)
#define  GPIO_APB_PORTD_GPIODR4R            *((volatile uint32 *) 0x40007504)
#define  GPIO_APB_PORTD_GPIODR8R            *((volatile uint32 *) 0x40007508)
#define  GPIO_APB_PORTD_GPIOODR             *((volatile uint32 *) 0x4000750C)
#define  GPIO_APB_PORTD_GPIOPUR             *((volatile uint32 *) 0x40007510)
#define  GPIO_APB_PORTD_GPIOPDR             *((volatile uint32 *) 0x40007514)
#define  GPIO_APB_PORTD_GPIOSLR             *((volatile uint32 *) 0x40007518)
#define  GPIO_APB_PORTD_GPIODEN             *((volatile uint32 *) 0x4000751C)
#define  GPIO_APB_PORTD_GPIOLOCK            *((volatile uint32 *) 0x40007520)
#define  GPIO_APB_PORTD_GPIOCR              *((volatile uint32 *) 0x40007524)
#define  GPIO_APB_PORTD_GPIOAMSEL           *((volatile uint32 *) 0x40007528)
#define  GPIO_APB_PORTD_GPIOPCTL            *((volatile uint32 *) 0x4000752C)
#define  GPIO_APB_PORTD_GPIOADCCTL          *((volatile uint32 *) 0x40007530)
#define  GPIO_APB_PORTD_GPIODMACTL          *((volatile uint32 *) 0x40007534)
#define  GPIO_APB_PORTD_GPIOPeriphlD4       *((volatile uint32 *) 0x40007FD0)
#define  GPIO_APB_PORTD_GPIOPeriphlD5       *((volatile uint32 *) 0x40007FD4)
#define  GPIO_APB_PORTD_GPIOPeriphlD6       *((volatile uint32 *) 0x40007FD8)
#define  GPIO_APB_PORTD_GPIOPeriphlD7       *((volatile uint32 *) 0x40007FDC)
#define  GPIO_APB_PORTD_GPIOPeriphlD0       *((volatile uint32 *) 0x40007FE0)
#define  GPIO_APB_PORTD_GPIOPeriphlD1       *((volatile uint32 *) 0x40007FE4)
#define  GPIO_APB_PORTD_GPIOPeriphlD2       *((volatile uint32 *) 0x40007FE8)
#define  GPIO_APB_PORTD_GPIOPeriphlD3       *((volatile uint32 *) 0x40007FEC)
#define  GPIO_APB_PORTD_GPIOPCellID0        *((volatile uint32 *) 0x40007FF0)
#define  GPIO_APB_PORTD_GPIOPCellID1        *((volatile uint32 *) 0x40007FF4)
#define  GPIO_APB_PORTD_GPIOPCellID2        *((volatile uint32 *) 0x40007FF8)
#define  GPIO_APB_PORTD_GPIOPCellID3        *((volatile uint32 *) 0x40007FFC)


// GPIO PORTE APB Registers --> Base Address = 0x40024000

#define  GPIO_APB_PORTE_GPIODATA            *((volatile uint32 *) 0x400243FC)
#define  GPIO_APB_PORTE_GPIODIR             *((volatile uint32 *) 0x40024400)
#define  GPIO_APB_PORTE_GPIOIS              *((volatile uint32 *) 0x40024404)
#define  GPIO_APB_PORTE_GPIOIBE             *((volatile uint32 *) 0x40024408)
#define  GPIO_APB_PORTE_GPIOIEV             *((volatile uint32 *) 0x4002440C)
#define  GPIO_APB_PORTE_GPIOIM              *((volatile uint32 *) 0x40024410)
#define  GPIO_APB_PORTE_GPIORIS             *((volatile uint32 *) 0x40024414)
#define  GPIO_APB_PORTE_GPIOMIS             *((volatile uint32 *) 0x40024418)
#define  GPIO_APB_PORTE_GPIOICR             *((volatile uint32 *) 0x4002441C)
#define  GPIO_APB_PORTE_GPIOAFSEL           *((volatile uint32 *) 0x40024420)
#define  GPIO_APB_PORTE_GPIODR2R            *((volatile uint32 *) 0x40024500)
#define  GPIO_APB_PORTE_GPIODR4R            *((volatile uint32 *) 0x40024504)
#define  GPIO_APB_PORTE_GPIODR8R            *((volatile uint32 *) 0x40024508)
#define  GPIO_APB_PORTE_GPIOODR             *((volatile uint32 *) 0x4002450C)
#define  GPIO_APB_PORTE_GPIOPUR             *((volatile uint32 *) 0x40024510)
#define  GPIO_APB_PORTE_GPIOPDR             *((volatile uint32 *) 0x40024514)
#define  GPIO_APB_PORTE_GPIOSLR             *((volatile uint32 *) 0x40024518)
#define  GPIO_APB_PORTE_GPIODEN             *((volatile uint32 *) 0x4002451C)
#define  GPIO_APB_PORTE_GPIOLOCK            *((volatile uint32 *) 0x40024520)
#define  GPIO_APB_PORTE_GPIOCR              *((volatile uint32 *) 0x40024524)
#define  GPIO_APB_PORTE_GPIOAMSEL           *((volatile uint32 *) 0x40024528)
#define  GPIO_APB_PORTE_GPIOPCTL            *((volatile uint32 *) 0x4002452C)
#define  GPIO_APB_PORTE_GPIOADCCTL          *((volatile uint32 *) 0x40024530)
#define  GPIO_APB_PORTE_GPIODMACTL          *((volatile uint32 *) 0x40024534)
#define  GPIO_APB_PORTE_GPIOPeriphlD4       *((volatile uint32 *) 0x40024FD0)
#define  GPIO_APB_PORTE_GPIOPeriphlD5       *((volatile uint32 *) 0x40024FD4)
#define  GPIO_APB_PORTE_GPIOPeriphlD6       *((volatile uint32 *) 0x40024FD8)
#define  GPIO_APB_PORTE_GPIOPeriphlD7       *((volatile uint32 *) 0x40024FDC)
#define  GPIO_APB_PORTE_GPIOPeriphlD0       *((volatile uint32 *) 0x40024FE0)
#define  GPIO_APB_PORTE_GPIOPeriphlD1       *((volatile uint32 *) 0x40024FE4)
#define  GPIO_APB_PORTE_GPIOPeriphlD2       *((volatile uint32 *) 0x40024FE8)
#define  GPIO_APB_PORTE_GPIOPeriphlD3       *((volatile uint32 *) 0x40024FEC)
#define  GPIO_APB_PORTE_GPIOPCellID0        *((volatile uint32 *) 0x40024FF0)
#define  GPIO_APB_PORTE_GPIOPCellID1        *((volatile uint32 *) 0x40024FF4)
#define  GPIO_APB_PORTE_GPIOPCellID2        *((volatile uint32 *) 0x40024FF8)
#define  GPIO_APB_PORTE_GPIOPCellID3        *((volatile uint32 *) 0x40024FFC)


// GPIO PORTF APB Registers --> Base Address = 0x40025000

#define  GPIO_APB_PORTF_GPIODATA            *((volatile uint32 *) 0x400253FC)
#define  GPIO_APB_PORTF_GPIODIR             *((volatile uint32 *) 0x40025400)
#define  GPIO_APB_PORTF_GPIOIS              *((volatile uint32 *) 0x40025404)
#define  GPIO_APB_PORTF_GPIOIBE             *((volatile uint32 *) 0x40025408)
#define  GPIO_APB_PORTF_GPIOIEV             *((volatile uint32 *) 0x4002540C)
#define  GPIO_APB_PORTF_GPIOIM              *((volatile uint32 *) 0x40025410)
#define  GPIO_APB_PORTF_GPIORIS             *((volatile uint32 *) 0x40025414)
#define  GPIO_APB_PORTF_GPIOMIS             *((volatile uint32 *) 0x40025418)
#define  GPIO_APB_PORTF_GPIOICR             *((volatile uint32 *) 0x4002541C)
#define  GPIO_APB_PORTF_GPIOAFSEL           *((volatile uint32 *) 0x40025420)
#define  GPIO_APB_PORTF_GPIODR2R            *((volatile uint32 *) 0x40025500)
#define  GPIO_APB_PORTF_GPIODR4R            *((volatile uint32 *) 0x40025504)
#define  GPIO_APB_PORTF_GPIODR8R            *((volatile uint32 *) 0x40025508)
#define  GPIO_APB_PORTF_GPIOODR             *((volatile uint32 *) 0x4002550C)
#define  GPIO_APB_PORTF_GPIOPUR             *((volatile uint32 *) 0x40025510)
#define  GPIO_APB_PORTF_GPIOPDR             *((volatile uint32 *) 0x40025514)
#define  GPIO_APB_PORTF_GPIOSLR             *((volatile uint32 *) 0x40025518)
#define  GPIO_APB_PORTF_GPIODEN             *((volatile uint32 *) 0x4002551C)
#define  GPIO_APB_PORTF_GPIOLOCK            *((volatile uint32 *) 0x40025520)
#define  GPIO_APB_PORTF_GPIOCR              *((volatile uint32 *) 0x40025524)
#define  GPIO_APB_PORTF_GPIOAMSEL           *((volatile uint32 *) 0x40025528)
#define  GPIO_APB_PORTF_GPIOPCTL            *((volatile uint32 *) 0x4002552C)
#define  GPIO_APB_PORTF_GPIOADCCTL          *((volatile uint32 *) 0x40025530)
#define  GPIO_APB_PORTF_GPIODMACTL          *((volatile uint32 *) 0x40025534)
#define  GPIO_APB_PORTF_GPIOPeriphlD4       *((volatile uint32 *) 0x40025FD0)
#define  GPIO_APB_PORTF_GPIOPeriphlD5       *((volatile uint32 *) 0x40025FD4)
#define  GPIO_APB_PORTF_GPIOPeriphlD6       *((volatile uint32 *) 0x40025FD8)
#define  GPIO_APB_PORTF_GPIOPeriphlD7       *((volatile uint32 *) 0x40025FDC)
#define  GPIO_APB_PORTF_GPIOPeriphlD0       *((volatile uint32 *) 0x40025FE0)
#define  GPIO_APB_PORTF_GPIOPeriphlD1       *((volatile uint32 *) 0x40025FE4)
#define  GPIO_APB_PORTF_GPIOPeriphlD2       *((volatile uint32 *) 0x40025FE8)
#define  GPIO_APB_PORTF_GPIOPeriphlD3       *((volatile uint32 *) 0x40025FEC)
#define  GPIO_APB_PORTF_GPIOPCellID0        *((volatile uint32 *) 0x40025FF0)
#define  GPIO_APB_PORTF_GPIOPCellID1        *((volatile uint32 *) 0x40025FF4)
#define  GPIO_APB_PORTF_GPIOPCellID2        *((volatile uint32 *) 0x40025FF8)
#define  GPIO_APB_PORTF_GPIOPCellID3        *((volatile uint32 *) 0x40025FFC)


// GPIO PORTA AHB Registers --> Base Address = 0x40058000

#define  GPIO_AHB_PORTA_GPIODATA            *((volatile uint32 *) 0x40058000)
#define  GPIO_AHB_PORTA_GPIODIR             *((volatile uint32 *) 0x40058400)
#define  GPIO_AHB_PORTA_GPIOIS              *((volatile uint32 *) 0x40058404)
#define  GPIO_AHB_PORTA_GPIOIBE             *((volatile uint32 *) 0x40058408)
#define  GPIO_AHB_PORTA_GPIOIEV             *((volatile uint32 *) 0x4005840C)
#define  GPIO_AHB_PORTA_GPIOIM              *((volatile uint32 *) 0x40058410)
#define  GPIO_AHB_PORTA_GPIORIS             *((volatile uint32 *) 0x40058414)
#define  GPIO_AHB_PORTA_GPIOMIS             *((volatile uint32 *) 0x40058418)
#define  GPIO_AHB_PORTA_GPIOICR             *((volatile uint32 *) 0x4005841C)
#define  GPIO_AHB_PORTA_GPIOAFSEL           *((volatile uint32 *) 0x40058420)
#define  GPIO_AHB_PORTA_GPIODR2R            *((volatile uint32 *) 0x40058500)
#define  GPIO_AHB_PORTA_GPIODR4R            *((volatile uint32 *) 0x40058504)
#define  GPIO_AHB_PORTA_GPIODR8R            *((volatile uint32 *) 0x40058508)
#define  GPIO_AHB_PORTA_GPIOODR             *((volatile uint32 *) 0x4005850C)
#define  GPIO_AHB_PORTA_GPIOPUR             *((volatile uint32 *) 0x40058510)
#define  GPIO_AHB_PORTA_GPIOPDR             *((volatile uint32 *) 0x40058514)
#define  GPIO_AHB_PORTA_GPIOSLR             *((volatile uint32 *) 0x40058518)
#define  GPIO_AHB_PORTA_GPIODEN             *((volatile uint32 *) 0x4005851C)
#define  GPIO_AHB_PORTA_GPIOLOCK            *((volatile uint32 *) 0x40058520)
#define  GPIO_AHB_PORTA_GPIOCR              *((volatile uint32 *) 0x40058524)
#define  GPIO_AHB_PORTA_GPIOAMSEL           *((volatile uint32 *) 0x40058528)
#define  GPIO_AHB_PORTA_GPIOPCTL            *((volatile uint32 *) 0x4005852C)
#define  GPIO_AHB_PORTA_GPIOADCCTL          *((volatile uint32 *) 0x40058530)
#define  GPIO_AHB_PORTA_GPIODMACTL          *((volatile uint32 *) 0x40058534)
#define  GPIO_AHB_PORTA_GPIOPeriphlD4       *((volatile uint32 *) 0x40058FD0)
#define  GPIO_AHB_PORTA_GPIOPeriphlD5       *((volatile uint32 *) 0x40058FD4)
#define  GPIO_AHB_PORTA_GPIOPeriphlD6       *((volatile uint32 *) 0x40058FD8)
#define  GPIO_AHB_PORTA_GPIOPeriphlD7       *((volatile uint32 *) 0x40058FDC)
#define  GPIO_AHB_PORTA_GPIOPeriphlD0       *((volatile uint32 *) 0x40058FE0)
#define  GPIO_AHB_PORTA_GPIOPeriphlD1       *((volatile uint32 *) 0x40058FE4)
#define  GPIO_AHB_PORTA_GPIOPeriphlD2       *((volatile uint32 *) 0x40058FE8)
#define  GPIO_AHB_PORTA_GPIOPeriphlD3       *((volatile uint32 *) 0x40058FEC)
#define  GPIO_AHB_PORTA_GPIOPCellID0        *((volatile uint32 *) 0x40058FF0)
#define  GPIO_AHB_PORTA_GPIOPCellID1        *((volatile uint32 *) 0x40058FF4)
#define  GPIO_AHB_PORTA_GPIOPCellID2        *((volatile uint32 *) 0x40058FF8)
#define  GPIO_AHB_PORTA_GPIOPCellID3        *((volatile uint32 *) 0x40058FFC)


// GPIO PORTB AHB Registers --> Base Address = 0x40059000

#define  GPIO_AHB_PORTB_GPIODATA            *((volatile uint32 *) 0x40059000)
#define  GPIO_AHB_PORTB_GPIODIR             *((volatile uint32 *) 0x40059400)
#define  GPIO_AHB_PORTB_GPIOIS              *((volatile uint32 *) 0x40059404)
#define  GPIO_AHB_PORTB_GPIOIBE             *((volatile uint32 *) 0x40059408)
#define  GPIO_AHB_PORTB_GPIOIEV             *((volatile uint32 *) 0x4005940C)
#define  GPIO_AHB_PORTB_GPIOIM              *((volatile uint32 *) 0x40059410)
#define  GPIO_AHB_PORTB_GPIORIS             *((volatile uint32 *) 0x40059414)
#define  GPIO_AHB_PORTB_GPIOMIS             *((volatile uint32 *) 0x40059418)
#define  GPIO_AHB_PORTB_GPIOICR             *((volatile uint32 *) 0x4005941C)
#define  GPIO_AHB_PORTB_GPIOAFSEL           *((volatile uint32 *) 0x40059420)
#define  GPIO_AHB_PORTB_GPIODR2R            *((volatile uint32 *) 0x40059500)
#define  GPIO_AHB_PORTB_GPIODR4R            *((volatile uint32 *) 0x40059504)
#define  GPIO_AHB_PORTB_GPIODR8R            *((volatile uint32 *) 0x40059508)
#define  GPIO_AHB_PORTB_GPIOODR             *((volatile uint32 *) 0x4005950C)
#define  GPIO_AHB_PORTB_GPIOPUR             *((volatile uint32 *) 0x40059510)
#define  GPIO_AHB_PORTB_GPIOPDR             *((volatile uint32 *) 0x40059514)
#define  GPIO_AHB_PORTB_GPIOSLR             *((volatile uint32 *) 0x40059518)
#define  GPIO_AHB_PORTB_GPIODEN             *((volatile uint32 *) 0x4005951C)
#define  GPIO_AHB_PORTB_GPIOLOCK            *((volatile uint32 *) 0x40059520)
#define  GPIO_AHB_PORTB_GPIOCR              *((volatile uint32 *) 0x40059524)
#define  GPIO_AHB_PORTB_GPIOAMSEL           *((volatile uint32 *) 0x40059528)
#define  GPIO_AHB_PORTB_GPIOPCTL            *((volatile uint32 *) 0x4005952C)
#define  GPIO_AHB_PORTB_GPIOADCCTL          *((volatile uint32 *) 0x40059530)
#define  GPIO_AHB_PORTB_GPIODMACTL          *((volatile uint32 *) 0x40059534)
#define  GPIO_AHB_PORTB_GPIOPeriphlD4       *((volatile uint32 *) 0x40059FD0)
#define  GPIO_AHB_PORTB_GPIOPeriphlD5       *((volatile uint32 *) 0x40059FD4)
#define  GPIO_AHB_PORTB_GPIOPeriphlD6       *((volatile uint32 *) 0x40059FD8)
#define  GPIO_AHB_PORTB_GPIOPeriphlD7       *((volatile uint32 *) 0x40059FDC)
#define  GPIO_AHB_PORTB_GPIOPeriphlD0       *((volatile uint32 *) 0x40059FE0)
#define  GPIO_AHB_PORTB_GPIOPeriphlD1       *((volatile uint32 *) 0x40059FE4)
#define  GPIO_AHB_PORTB_GPIOPeriphlD2       *((volatile uint32 *) 0x40059FE8)
#define  GPIO_AHB_PORTB_GPIOPeriphlD3       *((volatile uint32 *) 0x40059FEC)
#define  GPIO_AHB_PORTB_GPIOPCellID0        *((volatile uint32 *) 0x40059FF0)
#define  GPIO_AHB_PORTB_GPIOPCellID1        *((volatile uint32 *) 0x40059FF4)
#define  GPIO_AHB_PORTB_GPIOPCellID2        *((volatile uint32 *) 0x40059FF8)
#define  GPIO_AHB_PORTB_GPIOPCellID3        *((volatile uint32 *) 0x40059FFC)


// GPIO PORTC AHB Registers --> Base Address = 0x4005A000

#define  GPIO_AHB_PORTC_GPIODATA            *((volatile uint32 *) 0x4005A000)
#define  GPIO_AHB_PORTC_GPIODIR             *((volatile uint32 *) 0x4005A400)
#define  GPIO_AHB_PORTC_GPIOIS              *((volatile uint32 *) 0x4005A404)
#define  GPIO_AHB_PORTC_GPIOIBE             *((volatile uint32 *) 0x4005A408)
#define  GPIO_AHB_PORTC_GPIOIEV             *((volatile uint32 *) 0x4005A40C)
#define  GPIO_AHB_PORTC_GPIOIM              *((volatile uint32 *) 0x4005A410)
#define  GPIO_AHB_PORTC_GPIORIS             *((volatile uint32 *) 0x4005A414)
#define  GPIO_AHB_PORTC_GPIOMIS             *((volatile uint32 *) 0x4005A418)
#define  GPIO_AHB_PORTC_GPIOICR             *((volatile uint32 *) 0x4005A41C)
#define  GPIO_AHB_PORTC_GPIOAFSEL           *((volatile uint32 *) 0x4005A420)
#define  GPIO_AHB_PORTC_GPIODR2R            *((volatile uint32 *) 0x4005A500)
#define  GPIO_AHB_PORTC_GPIODR4R            *((volatile uint32 *) 0x4005A504)
#define  GPIO_AHB_PORTC_GPIODR8R            *((volatile uint32 *) 0x4005A508)
#define  GPIO_AHB_PORTC_GPIOODR             *((volatile uint32 *) 0x4005A50C)
#define  GPIO_AHB_PORTC_GPIOPUR             *((volatile uint32 *) 0x4005A510)
#define  GPIO_AHB_PORTC_GPIOPDR             *((volatile uint32 *) 0x4005A514)
#define  GPIO_AHB_PORTC_GPIOSLR             *((volatile uint32 *) 0x4005A518)
#define  GPIO_AHB_PORTC_GPIODEN             *((volatile uint32 *) 0x4005A51C)
#define  GPIO_AHB_PORTC_GPIOLOCK            *((volatile uint32 *) 0x4005A520)
#define  GPIO_AHB_PORTC_GPIOCR              *((volatile uint32 *) 0x4005A524)
#define  GPIO_AHB_PORTC_GPIOAMSEL           *((volatile uint32 *) 0x4005A528)
#define  GPIO_AHB_PORTC_GPIOPCTL            *((volatile uint32 *) 0x4005A52C)
#define  GPIO_AHB_PORTC_GPIOADCCTL          *((volatile uint32 *) 0x4005A530)
#define  GPIO_AHB_PORTC_GPIODMACTL          *((volatile uint32 *) 0x4005A534)
#define  GPIO_AHB_PORTC_GPIOPeriphlD4       *((volatile uint32 *) 0x4005AFD0)
#define  GPIO_AHB_PORTC_GPIOPeriphlD5       *((volatile uint32 *) 0x4005AFD4)
#define  GPIO_AHB_PORTC_GPIOPeriphlD6       *((volatile uint32 *) 0x4005AFD8)
#define  GPIO_AHB_PORTC_GPIOPeriphlD7       *((volatile uint32 *) 0x4005AFDC)
#define  GPIO_AHB_PORTC_GPIOPeriphlD0       *((volatile uint32 *) 0x4005AFE0)
#define  GPIO_AHB_PORTC_GPIOPeriphlD1       *((volatile uint32 *) 0x4005AFE4)
#define  GPIO_AHB_PORTC_GPIOPeriphlD2       *((volatile uint32 *) 0x4005AFE8)
#define  GPIO_AHB_PORTC_GPIOPeriphlD3       *((volatile uint32 *) 0x4005AFEC)
#define  GPIO_AHB_PORTC_GPIOPCellID0        *((volatile uint32 *) 0x4005AFF0)
#define  GPIO_AHB_PORTC_GPIOPCellID1        *((volatile uint32 *) 0x4005AFF4)
#define  GPIO_AHB_PORTC_GPIOPCellID2        *((volatile uint32 *) 0x4005AFF8)
#define  GPIO_AHB_PORTC_GPIOPCellID3        *((volatile uint32 *) 0x4005AFFC)


// GPIO PORTD AHB Registers --> Base Address = 0x4005B000

#define  GPIO_AHB_PORTD_GPIODATA            *((volatile uint32 *) 0x4005B000)
#define  GPIO_AHB_PORTD_GPIODIR             *((volatile uint32 *) 0x4005B400)
#define  GPIO_AHB_PORTD_GPIOIS              *((volatile uint32 *) 0x4005B404)
#define  GPIO_AHB_PORTD_GPIOIBE             *((volatile uint32 *) 0x4005B408)
#define  GPIO_AHB_PORTD_GPIOIEV             *((volatile uint32 *) 0x4005B40C)
#define  GPIO_AHB_PORTD_GPIOIM              *((volatile uint32 *) 0x4005B410)
#define  GPIO_AHB_PORTD_GPIORIS             *((volatile uint32 *) 0x4005B414)
#define  GPIO_AHB_PORTD_GPIOMIS             *((volatile uint32 *) 0x4005B418)
#define  GPIO_AHB_PORTD_GPIOICR             *((volatile uint32 *) 0x4005B41C)
#define  GPIO_AHB_PORTD_GPIOAFSEL           *((volatile uint32 *) 0x4005B420)
#define  GPIO_AHB_PORTD_GPIODR2R            *((volatile uint32 *) 0x4005B500)
#define  GPIO_AHB_PORTD_GPIODR4R            *((volatile uint32 *) 0x4005B504)
#define  GPIO_AHB_PORTD_GPIODR8R            *((volatile uint32 *) 0x4005B508)
#define  GPIO_AHB_PORTD_GPIOODR             *((volatile uint32 *) 0x4005B50C)
#define  GPIO_AHB_PORTD_GPIOPUR             *((volatile uint32 *) 0x4005B510)
#define  GPIO_AHB_PORTD_GPIOPDR             *((volatile uint32 *) 0x4005B514)
#define  GPIO_AHB_PORTD_GPIOSLR             *((volatile uint32 *) 0x4005B518)
#define  GPIO_AHB_PORTD_GPIODEN             *((volatile uint32 *) 0x4005B51C)
#define  GPIO_AHB_PORTD_GPIOLOCK            *((volatile uint32 *) 0x4005B520)
#define  GPIO_AHB_PORTD_GPIOCR              *((volatile uint32 *) 0x4005B524)
#define  GPIO_AHB_PORTD_GPIOAMSEL           *((volatile uint32 *) 0x4005B528)
#define  GPIO_AHB_PORTD_GPIOPCTL            *((volatile uint32 *) 0x4005B52C)
#define  GPIO_AHB_PORTD_GPIOADCCTL          *((volatile uint32 *) 0x4005B530)
#define  GPIO_AHB_PORTD_GPIODMACTL          *((volatile uint32 *) 0x4005B534)
#define  GPIO_AHB_PORTD_GPIOPeriphlD4       *((volatile uint32 *) 0x4005BFD0)
#define  GPIO_AHB_PORTD_GPIOPeriphlD5       *((volatile uint32 *) 0x4005BFD4)
#define  GPIO_AHB_PORTD_GPIOPeriphlD6       *((volatile uint32 *) 0x4005BFD8)
#define  GPIO_AHB_PORTD_GPIOPeriphlD7       *((volatile uint32 *) 0x4005BFDC)
#define  GPIO_AHB_PORTD_GPIOPeriphlD0       *((volatile uint32 *) 0x4005BFE0)
#define  GPIO_AHB_PORTD_GPIOPeriphlD1       *((volatile uint32 *) 0x4005BFE4)
#define  GPIO_AHB_PORTD_GPIOPeriphlD2       *((volatile uint32 *) 0x4005BFE8)
#define  GPIO_AHB_PORTD_GPIOPeriphlD3       *((volatile uint32 *) 0x4005BFEC)
#define  GPIO_AHB_PORTD_GPIOPCellID0        *((volatile uint32 *) 0x4005BFF0)
#define  GPIO_AHB_PORTD_GPIOPCellID1        *((volatile uint32 *) 0x4005BFF4)
#define  GPIO_AHB_PORTD_GPIOPCellID2        *((volatile uint32 *) 0x4005BFF8)
#define  GPIO_AHB_PORTD_GPIOPCellID3        *((volatile uint32 *) 0x4005BFFC)


// GPIO PORTE AHB Registers --> Base Address = 0x4005C000

#define  GPIO_AHB_PORTE_GPIODATA            *((volatile uint32 *) 0x4005C000)
#define  GPIO_AHB_PORTE_GPIODIR             *((volatile uint32 *) 0x4005C400)
#define  GPIO_AHB_PORTE_GPIOIS              *((volatile uint32 *) 0x4005C404)
#define  GPIO_AHB_PORTE_GPIOIBE             *((volatile uint32 *) 0x4005C408)
#define  GPIO_AHB_PORTE_GPIOIEV             *((volatile uint32 *) 0x4005C40C)
#define  GPIO_AHB_PORTE_GPIOIM              *((volatile uint32 *) 0x4005C410)
#define  GPIO_AHB_PORTE_GPIORIS             *((volatile uint32 *) 0x4005C414)
#define  GPIO_AHB_PORTE_GPIOMIS             *((volatile uint32 *) 0x4005C418)
#define  GPIO_AHB_PORTE_GPIOICR             *((volatile uint32 *) 0x4005C41C)
#define  GPIO_AHB_PORTE_GPIOAFSEL           *((volatile uint32 *) 0x4005C420)
#define  GPIO_AHB_PORTE_GPIODR2R            *((volatile uint32 *) 0x4005C500)
#define  GPIO_AHB_PORTE_GPIODR4R            *((volatile uint32 *) 0x4005C504)
#define  GPIO_AHB_PORTE_GPIODR8R            *((volatile uint32 *) 0x4005C508)
#define  GPIO_AHB_PORTE_GPIOODR             *((volatile uint32 *) 0x4005C50C)
#define  GPIO_AHB_PORTE_GPIOPUR             *((volatile uint32 *) 0x4005C510)
#define  GPIO_AHB_PORTE_GPIOPDR             *((volatile uint32 *) 0x4005C514)
#define  GPIO_AHB_PORTE_GPIOSLR             *((volatile uint32 *) 0x4005C518)
#define  GPIO_AHB_PORTE_GPIODEN             *((volatile uint32 *) 0x4005C51C)
#define  GPIO_AHB_PORTE_GPIOLOCK            *((volatile uint32 *) 0x4005C520)
#define  GPIO_AHB_PORTE_GPIOCR              *((volatile uint32 *) 0x4005C524)
#define  GPIO_AHB_PORTE_GPIOAMSEL           *((volatile uint32 *) 0x4005C528)
#define  GPIO_AHB_PORTE_GPIOPCTL            *((volatile uint32 *) 0x4005C52C)
#define  GPIO_AHB_PORTE_GPIOADCCTL          *((volatile uint32 *) 0x4005C530)
#define  GPIO_AHB_PORTE_GPIODMACTL          *((volatile uint32 *) 0x4005C534)
#define  GPIO_AHB_PORTE_GPIOPeriphlD4       *((volatile uint32 *) 0x4005CFD0)
#define  GPIO_AHB_PORTE_GPIOPeriphlD5       *((volatile uint32 *) 0x4005CFD4)
#define  GPIO_AHB_PORTE_GPIOPeriphlD6       *((volatile uint32 *) 0x4005CFD8)
#define  GPIO_AHB_PORTE_GPIOPeriphlD7       *((volatile uint32 *) 0x4005CFDC)
#define  GPIO_AHB_PORTE_GPIOPeriphlD0       *((volatile uint32 *) 0x4005CFE0)
#define  GPIO_AHB_PORTE_GPIOPeriphlD1       *((volatile uint32 *) 0x4005CFE4)
#define  GPIO_AHB_PORTE_GPIOPeriphlD2       *((volatile uint32 *) 0x4005CFE8)
#define  GPIO_AHB_PORTE_GPIOPeriphlD3       *((volatile uint32 *) 0x4005CFEC)
#define  GPIO_AHB_PORTE_GPIOPCellID0        *((volatile uint32 *) 0x4005CFF0)
#define  GPIO_AHB_PORTE_GPIOPCellID1        *((volatile uint32 *) 0x4005CFF4)
#define  GPIO_AHB_PORTE_GPIOPCellID2        *((volatile uint32 *) 0x4005CFF8)
#define  GPIO_AHB_PORTE_GPIOPCellID3        *((volatile uint32 *) 0x4005CFFC)


// GPIO PORTF AHB Registers --> Base Address = 0x4005D000

#define  GPIO_AHB_PORTF_GPIODATA            *((volatile uint32 *) 0x4005D000)
#define  GPIO_AHB_PORTF_GPIODIR             *((volatile uint32 *) 0x4005D400)
#define  GPIO_AHB_PORTF_GPIOIS              *((volatile uint32 *) 0x4005D404)
#define  GPIO_AHB_PORTF_GPIOIBE             *((volatile uint32 *) 0x4005D408)
#define  GPIO_AHB_PORTF_GPIOIEV             *((volatile uint32 *) 0x4005D40C)
#define  GPIO_AHB_PORTF_GPIOIM              *((volatile uint32 *) 0x4005D410)
#define  GPIO_AHB_PORTF_GPIORIS             *((volatile uint32 *) 0x4005D414)
#define  GPIO_AHB_PORTF_GPIOMIS             *((volatile uint32 *) 0x4005D418)
#define  GPIO_AHB_PORTF_GPIOICR             *((volatile uint32 *) 0x4005D41C)
#define  GPIO_AHB_PORTF_GPIOAFSEL           *((volatile uint32 *) 0x4005D420)
#define  GPIO_AHB_PORTF_GPIODR2R            *((volatile uint32 *) 0x4005D500)
#define  GPIO_AHB_PORTF_GPIODR4R            *((volatile uint32 *) 0x4005D504)
#define  GPIO_AHB_PORTF_GPIODR8R            *((volatile uint32 *) 0x4005D508)
#define  GPIO_AHB_PORTF_GPIOODR             *((volatile uint32 *) 0x4005D50C)
#define  GPIO_AHB_PORTF_GPIOPUR             *((volatile uint32 *) 0x4005D510)
#define  GPIO_AHB_PORTF_GPIOPDR             *((volatile uint32 *) 0x4005D514)
#define  GPIO_AHB_PORTF_GPIOSLR             *((volatile uint32 *) 0x4005D518)
#define  GPIO_AHB_PORTF_GPIODEN             *((volatile uint32 *) 0x4005D51C)
#define  GPIO_AHB_PORTF_GPIOLOCK            *((volatile uint32 *) 0x4005D520)
#define  GPIO_AHB_PORTF_GPIOCR              *((volatile uint32 *) 0x4005D524)
#define  GPIO_AHB_PORTF_GPIOAMSEL           *((volatile uint32 *) 0x4005D528)
#define  GPIO_AHB_PORTF_GPIOPCTL            *((volatile uint32 *) 0x4005D52C)
#define  GPIO_AHB_PORTF_GPIOADCCTL          *((volatile uint32 *) 0x4005D530)
#define  GPIO_AHB_PORTF_GPIODMACTL          *((volatile uint32 *) 0x4005D534)
#define  GPIO_AHB_PORTF_GPIOPeriphlD4       *((volatile uint32 *) 0x4005DFD0)
#define  GPIO_AHB_PORTF_GPIOPeriphlD5       *((volatile uint32 *) 0x4005DFD4)
#define  GPIO_AHB_PORTF_GPIOPeriphlD6       *((volatile uint32 *) 0x4005DFD8)
#define  GPIO_AHB_PORTF_GPIOPeriphlD7       *((volatile uint32 *) 0x4005DFDC)
#define  GPIO_AHB_PORTF_GPIOPeriphlD0       *((volatile uint32 *) 0x4005DFE0)
#define  GPIO_AHB_PORTF_GPIOPeriphlD1       *((volatile uint32 *) 0x4005DFE4)
#define  GPIO_AHB_PORTF_GPIOPeriphlD2       *((volatile uint32 *) 0x4005DFE8)
#define  GPIO_AHB_PORTF_GPIOPeriphlD3       *((volatile uint32 *) 0x4005DFEC)
#define  GPIO_AHB_PORTF_GPIOPCellID0        *((volatile uint32 *) 0x4005DFF0)
#define  GPIO_AHB_PORTF_GPIOPCellID1        *((volatile uint32 *) 0x4005DFF4)
#define  GPIO_AHB_PORTF_GPIOPCellID2        *((volatile uint32 *) 0x4005DFF8)
#define  GPIO_AHB_PORTF_GPIOPCellID3        *((volatile uint32 *) 0x4005DFFC)




// RCGCGPIO Register Pins
#define RCGCGPIO_PORTA        (uint8) 0
#define RCGCGPIO_PORTB        (uint8) 1
#define RCGCGPIO_PORTC        (uint8) 2
#define RCGCGPIO_PORTD        (uint8) 3
#define RCGCGPIO_PORTE        (uint8) 4
#define RCGCGPIO_PORTF        (uint8) 5


// SCGCGPIO Register Pins
#define SCGCGPIO_PORTA        (uint8) 0
#define SCGCGPIO_PORTB        (uint8) 1
#define SCGCGPIO_PORTC        (uint8) 2
#define SCGCGPIO_PORTD        (uint8) 3
#define SCGCGPIO_PORTE        (uint8) 4
#define SCGCGPIO_PORTF        (uint8) 5



// DCGCGPIO Register Pins
#define DCGCGPIO_PORTA        (uint8) 0
#define DCGCGPIO_PORTB        (uint8) 1
#define DCGCGPIO_PORTC        (uint8) 2
#define DCGCGPIO_PORTD        (uint8) 3
#define DCGCGPIO_PORTE        (uint8) 4
#define DCGCGPIO_PORTF        (uint8) 5


#endif /* GPIO_PRIVATE_H */
