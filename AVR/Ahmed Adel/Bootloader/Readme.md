# Bootloader Driver

## Steps to use the Driver:
> Build the code (CODE 1) you want to be uploaded on the Microcontroller.
> Copy the ***Hex2Array.exe*** file in the Debug folder of the (CODE 1).
> Open the Command Prompt in the previous folder direction.
> Write the following command ```Hex2Array.exe PROJECT_NAME.hex ``` 
> An ***output.txt*** will be generated in the same folder.
> Copy the text generated in ***output.txt*** and paste it in ***BootConfig.h***.








### **1. LCD Constructor: LCD(uint8_t config)**

***Definition:***

> This is the constructor of the LCD object.It defines the configuration in which the LCD will operate.

***Arguments:***

> The Configuration of the LCD.
> - LCD_8_BIT
> - LCD_4_BIT
> - LCD_I2C

### **2. void Init(void)**

***Definition:***

> This function Initializes the LCD and makes it ready to receive commands.

### **3. void printString(char *str)**

***Definition:***

> This function prints a string on the LCD.

***Arguments:***

> - The string to be printed.

### **4. void gotoXY(uint8_t x, uint8_t y)**

***Definition:***

> This function sets the cursor at point(x, y).

***Arguments:***

> X Point ( 1 -> 16 )
> Y Point ( 1 -> 2 )

### **5. void command(uint8_t cmd)**

***Definition:***

> This function sends a specific command to the LCD. all commands of the LCD can be found in the LCD's datasheet.

***Arguments:***

> Command to be sent.


### **6. void printData(uint8_t data)**

***Definition:***

> This function prints a single data byte on the LCD.

***Arguments:***

> The data byte to be printed.

### **7. void clear(void)**

***Definition:***

> This function clears the LCD and return the cursor to Home.


# Example:
## 8-BIT LCD.

```
#include <stdio.h>

int main(void)
{
	
	LCD lcd(LCD_8_BIT);
	lcd.Init();

	char str[20];

	sprintf(str, "Hello World");
	lcd.gotoXY(1,1);
	lcd.printString(str);

	while (1)
	{
	}
}

```
![8_BIT_LCD](8_BIT_LCD.png)

## 4-BIT LCD.

```
#include <stdio.h>

int main(void)
{
	
	LCD lcd(LCD_4_BIT);
	lcd.Init();

	char str[20];

	sprintf(str, "Hello World");
	lcd.gotoXY(1,1);
	lcd.printString(str);

	while (1)
	{
	}
}

```
![4_BIT_LCD](4_BIT_LCD.png)

## I2C LCD.

```
#include <stdio.h>

int main(void)
{
	
	LCD lcd(LCD_I2C);
	lcd.Init();

	char str[20];

	sprintf(str, "Hello World");
	lcd.gotoXY(1,1);
	lcd.printString(str);

	while (1)
	{
	}
}

```
![I2C_LCD](I2C_LCD.png)
