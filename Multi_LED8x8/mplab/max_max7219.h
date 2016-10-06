/*
This file contains functions to control max7219.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#ifndef MAX_MAX7219_H
#define MAX_MAX7219_H

#include "max7219.h"

// This is write Byte function.

void Write_Matrix(const MATRIX_MATRIX7219* matrix, uint8_t column)
{
     uint8_t at;
     for(uint8_t row = 0; row < MATRIX_MATRIX8x8_ROW_MAX; row++)
     {
         for(uint8_t col = 0; col < MATRIX_MATRIX8x8_COLUMN_MAX; col++)
         {
             if(row%2 == 1)
             {
                 at = MATRIX8x8_COLUMN_MAX + 1 - column;
             }
             else
             {
                 at = column;
             }
             Write_Byte(column, uint8_t myValue);
         }                 
     }     
}
#endif // MAX_MAX7219_H
