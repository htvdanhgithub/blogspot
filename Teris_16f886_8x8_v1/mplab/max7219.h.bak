#define DATA_PORT         A
#define DATA_POS          3
#define DATA_PIN          PIN(DATA_PORT, DATA_POS)
#define DATA              PORTBIT(DATA_PIN)

#define LOAD_PORT         A
#define LOAD_POS          2
#define LOAD_PIN          PIN(LOAD_PORT, LOAD_POS)
#define LOAD              PORTBIT(LOAD_PIN)

#define CLK_PORT          A
#define CLK_POS           1
#define CLK_PIN           PIN(CLK_PORT, CLK_POS)
#define CLK               PORTBIT(CLK_PIN)

void SPI1_write(uint8_t data) 
{
    uint8_t mask = 0b10000000;
    for(uint8_t i = 0; i < 8; i++)
    {
        if((data & mask) > 0)
        {
            DATA = 1;
//            USARTWriteLine("1");
        }
        else
        {
            DATA = 0;
//            USARTWriteLine("0");
        }
        mask >>= 1;
        CLK = 1;
        __delay_us(10);
        CLK = 0;
        __delay_us(10);

    }
}
// This is write Byte function.

void Write_Byte(uint8_t myColumn, uint8_t myValue)
{
    LOAD = 0; // select max7219.
    SPI1_write(myColumn); // send myColumn value to max7219 (digit place).
    SPI1_write(myValue); // send myValue value to max7219 (digit place).
    LOAD = 1; // deselect max7219.
}
// Here we set the configuration of max7219.
void max7219_init1()
{
    IO_OUTPUT(DATA_PIN);
    IO_OUTPUT(LOAD_PIN);
    IO_OUTPUT(CLK_PIN);
    
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 = 0;
    ANSELbits.ANS3 = 0;
    LOAD = 1;
    CLK = 0;
    
	Write_Byte(0x09, 0x00);
	Write_Byte(0x0A, 0x0F);
	Write_Byte(0x0B, 0x07);
	Write_Byte(0x0C, 0x01);
	Write_Byte(0x00, 0xFF);
}
