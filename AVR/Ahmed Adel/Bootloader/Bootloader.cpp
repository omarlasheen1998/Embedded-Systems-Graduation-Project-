/*
 * Bootloader.cpp
 *
 * Created: 8/7/2020 3:21:02 AM
 *  Author: ahmed
 */ 

#include "Bootloader.h"


void Boot::Program_page (uint16_t page, uint8_t *buf)
{
	uint16_t i;
	uint8_t sreg;
	uint32_t address;
	uint16_t word ;

	// Disable interrupts.
	sreg = SREG;
	cli();
	address = page * SPM_PAGESIZE ;


	boot_page_erase_safe (address);

	for (i=0; i<SPM_PAGESIZE; i+=2)
	{
		// Set up little Endian word.
		word  = *buf++;
		word += (*buf++) << 8;

		boot_page_fill_safe(address + i, word);
	}

	boot_page_write_safe (address);     // Store buffer in flash page.

	// Re enable RWW-section again. We need this if we want to jump back
	// to the application after boot loading.

	boot_rww_enable_safe();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}


void Boot::Flash_program(unsigned char app_code[], unsigned int pagesNum){
	uint8_t pageNum;
	
	//start at flash_start = 0x0000
	for(pageNum = 0 ; pageNum < pagesNum ; pageNum++)
	{
		Program_page( pageNum, &app_code[SPM_PAGESIZE*pageNum]);
	}
	
	//start the actual program
	asm("jmp 0");
}
