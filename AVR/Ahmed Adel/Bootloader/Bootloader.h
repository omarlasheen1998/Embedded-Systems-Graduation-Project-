/*
 * Bootloader.h
 *
 * Created: 8/7/2020 3:21:48 AM
 *  Author: ahmed
 */ 


#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "avr/io.h"
#include "avr/boot.h"
#include "avr/interrupt.h"

/* APP_CODE that will be booted to the Micro controller */



class Boot{
	
	public:
	static void Flash_program(unsigned char app_code[], unsigned int pagesNum);
	static void Program_page (uint16_t page, uint8_t *buf);

 
	
	private:
	
	
	};




#endif /* BOOTLOADER_H_ */
