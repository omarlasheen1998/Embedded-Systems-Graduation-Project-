#include <stm32f10x.h>

void copyContents(char *destP, char *srcP, uint16_t count)
{
	while(count > 0)
	{
		*destP = *srcP;
		destP++;
		srcP++;
		count--;
	}
}

int main()
{
	char source[10]="ABCDEDFHI";
	char dest[10];
	
	copyContents(dest, source, 10);
	
	while(1);
}

