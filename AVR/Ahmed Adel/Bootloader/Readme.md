# Bootloader Driver

## Steps to use the Driver:
> - Build the code (CODE 1) you want to be uploaded on the Microcontroller.
> - Copy the ***Hex2Array.exe*** file in the Debug folder of the (CODE 1).
> - Open the Command Prompt in the previous folder direction.
> - Write the following command ```Hex2Array.exe PROJECT_NAME.hex ``` 
> - An ***output.txt*** will be generated in the same folder.
> - Copy the text generated in ***output.txt*** and paste it in ***BootConfig.h***.
> - In (CODE 2) include the 3 bootloader files.
> - Configure the linker settings.
> - Build Project.

## Example Code
```
#include <avr/io.h>
#include "BootConfig.h"
#include "Bootloader.h"

int main(){

	DDRD |= (1 << 0);
	uint8_t i = 0;
	for(i = 0; i < 3; i++){
		PORTD |= (1 << 0);
		_delay_ms(50);
		PORTD &= ~(1 << 0);
		_delay_ms(50);
	}

	Boot::Flash_program(App_Code, NO_OF_PAGES);
}

```
