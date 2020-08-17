/*
 * IncFile1.h
 *
 * Created: 23-Jul-20 3:52:45 AM
 *  Author: Lasheen
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MOSI 5									/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4

void SPI_SlaveInit();							/* SPI initialize function */
void SPI_Write(unsigned char);						/* SPI write data function */
unsigned char SPI_Read();							/* SPI read data function */
void SPI_MasterInit();							/* SPI initialize function */
unsigned char SPI_returndata();
void SPI_attachInterrupt(void (*Local_ISR)(void));
void SPI_loadData(unsigned char data);
#endif /* INCFILE1_H_ */