/*
This file contains functions to drive max7219.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
#ifndef HAL_MAX7219_H
#define HAL_MAX7219_H

#include "max7219.h"

void hal_print_MATRIX_MATRIX7219(const MATRIX_MATRIX8x8* matrix88)
{
    MATRIX_MATRIX7219 matrix;
    
    uint8_t col;

    for (col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
    {
        for(uint8_t matrix_row = 0; matrix_row < MATRIX_MATRIX8x8_ROW_MAX; matrix_row++)
        {
            for(uint8_t matrix_col = 0; matrix_col < MATRIX_MATRIX8x8_COLUMN_MAX; matrix_col++)
            {
                if(matrix_row%2 == 1)
                {
                    matrix.data[matrix_row][matrix_col] = matrix88->data[matrix_row][MATRIX_MATRIX8x8_COLUMN_MAX - 1 - matrix_col].data[col];
                }
                else
                {
                    matrix.data[matrix_row][matrix_col] = matrix88->data[matrix_row][matrix_col].data[col];
                }
            }
        }
        Write_Matrix(&matrix, 1, col);
    }    
}
#endif //HAL_MAX7219_H
