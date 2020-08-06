#define SET_BIT(Reg,Bit_num) Reg |= 1 << Bit_num
#define CLR_BIT(Reg,Bit_num) Reg &= ~(1 << Bit_num)
#define TOG_BIT(Reg,Bit_num) Reg ^= (1 << Bit_num)
#define GET_BIT(Reg,Bit_num) ((Reg >> Bit_num) & (0x01))
