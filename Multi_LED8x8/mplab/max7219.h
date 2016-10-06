/*
This file contains functions to control max7219.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
#ifndef MAX7219_H
#define MAX7219_H

#include "common.h"


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
void Write_Matrix(const MATRIX_MATRIX7219* matrix, uint8_t option, uint8_t column)
{
    LOAD = 0; // select max7219.
     
    uint8_t at;
    uint8_t value;
    for(uint8_t row = 0; row < MATRIX_MATRIX8x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX_MATRIX8x8_COLUMN_MAX; col++)
        {
            at = column;
            value = matrix->data[MATRIX_MATRIX8x8_ROW_MAX - 1 - row][MATRIX_MATRIX8x8_COLUMN_MAX - 1 - col];
            if(option == 1) // 0: control, 1: data
            {
                if((MATRIX_MATRIX8x8_ROW_MAX - 1 - row)%2 == 1)
                {
                    at = MATRIX8x8_COLUMN_MAX - 1 - column;
                    value = reverse(value);
                }
                at++;
            }
            SPI1_write(at);
            SPI1_write(value);
        }                 
    }     
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
    
    MATRIX_MATRIX7219 matrix;
    
    memset(&matrix, 0x00, sizeof(MATRIX_MATRIX7219));
    Write_Matrix(&matrix, 0, 0x09);
    
    memset(&matrix, 0x0F, sizeof(MATRIX_MATRIX7219));
    Write_Matrix(&matrix, 0, 0x0A);
	
    memset(&matrix, 0x07, sizeof(MATRIX_MATRIX7219));
    Write_Matrix(&matrix, 0, 0x0B);
	
    memset(&matrix, 0x01, sizeof(MATRIX_MATRIX7219));
    Write_Matrix(&matrix, 0, 0x0C);
	
    memset(&matrix, 0xFF, sizeof(MATRIX_MATRIX7219));
    Write_Matrix(&matrix, 0, 0x00);
}
#endif // MAX7219_H
