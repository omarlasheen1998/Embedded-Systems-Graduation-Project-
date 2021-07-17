

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

typedef struct {

	volatile u32 CR1     ;
	volatile u32 CR2     ;
	volatile u32 SR      ;
	volatile u32 DR      ;
	volatile u32 CRCPR   ;
	volatile u32 RXCRCR  ;
	volatile u32 TXCRCR  ;
	volatile u32 I2SCFGR ;
	volatile u32 I2SPR   ;

}SPI;

#define MSPI1 ( ( volatile SPI* ) 0x40013000 )
#define MSPI2 ( ( volatile SPI* ) 0x40003800 )

#endif /* SPI_PRIVATE_H_ */
