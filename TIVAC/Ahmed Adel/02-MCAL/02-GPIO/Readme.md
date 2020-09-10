# Example Code:

```
void main(void)
{
   SYSCTL_voidSetClockSpeed(SYSCTL_16MHz);
   GPIO_voidEnableClock(PORTF);

   GPIO_voidSetPinDirection(PORTF, PIN3, OUTPUT);
   GPIO_voidSetPinDirection(PORTF, PIN4, INPUT_PULLUP);


   uint8 state = LOW;
   GPIO_voidSetPinValue(PORTF, PIN3, state);

   while(1)
   {
       if(!(GPIO_u8GetPinValue(PORTF, PIN4))){
           GPIO_voidSetPinValue(PORTF, PIN3, state ^= 1);
       }

   }
    //return 0;
}
```
