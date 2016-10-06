/*
This file contains functions to handle bit in a matrix.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
#ifndef BIT_MATRIX_LIB_H
#define BIT_MATRIX_LIB_H

#include "bit_lib.h"

uint8_t matrix_get_bit(const char* file, int line, const uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col)
{
     ENTER_FUNC;
//     printf("(matrix_get_bit) index out of bound (max_row = %d, max_col = %d)\n", max_row, max_col);
     if(row >= max_row)
     {
         dbg_print2(1, "ERROR: (matrix_get_bit) index out of bound (row = %d, max_row = %d)", row, max_row);
         exit(-1);
     }              
     
     if(col >= max_col)
     {
         dbg_print2(1, "ERROR: (matrix_get_bit) index out of bound (col = %d, max_col = %d)", col, max_col);
         exit(-1);
     }              

     const uint8_t *byte = &data[(row*max_col + col)/8];
     EXIT_FUNC1(get_bit(file, line, byte, col%8));
}
void matrix_set_bit(const char* file, int line, uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col, uint8_t value)
{
     ENTER_FUNC;
//     fprintf(fp, "(matrix_set_bit) index out of bound (max_row = %d, max_col = %d)\n", max_row, max_col);
     if(row >= max_row)
     {
         dbg_print2(1, "ERROR: (matrix_set_bit) index out of bound (row = %d, max_row = %d)", row, max_row);
         exit(-1);
     }              
     
     if(col >= max_col)
     {
         dbg_print2(1, "ERROR: (matrix_set_bit) index out of bound (col = %d, max_col = %d)", col, max_col);
         exit(-1);
     }              

     uint8_t *byte = &data[(row*max_col + col)/8];
     set_bit(file, line, byte, col%8, value);
     EXIT_FUNC;
}
#define MATRIX_GET_BIT(data, row, col)            matrix_get_bit(__FILE__, __LINE__, (uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8)
#define MATRIX_SET_BIT(data, row, col, value)     matrix_set_bit(__FILE__, __LINE__, (uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8, value)
#endif
