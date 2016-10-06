/*
This file contains functions to get/set an element of one bit matrix.
How to use: http://htvdanh.blogspot.com/2016/09/one-bit-matrix-for-cc-programming.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 9th, 2016
*/

#ifndef BIT_MATRIX_LIB_H
#define BIT_MATRIX_LIB_H

#include "bit_lib.h"

extern FILE* fp;
#if DEBUG
uint8_t one_bit_matrix_get_bit(const char* file, int line, const uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col)
#else
uint8_t one_bit_matrix_get_bit(const uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col)
#endif
{
//     printf("(1_bit_matrix_get_bit) index out of bound (max_row = %d, max_col = %d)\n", max_row, max_col);
     if(row >= max_row)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (1_bit_matrix_set_bit) index out of bound (row = %d, max_row = %d)\n", file, line, row, max_row);
#else
         fprintf(fp, "ERROR: (1_bit_matrix_set_bit) index out of bound (row = %d, max_row = %d)\n", row, max_row);
#endif         
         exit(-1);
     }              
     
     if(col >= max_col)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (1_bit_matrix_set_bit) index out of bound (col = %d, max_col = %d)\n", file, line, col, max_col);
#else
         fprintf(fp, "ERROR: (1_bit_matrix_set_bit) index out of bound (col = %d, max_col = %d)\n", col, max_col);
#endif         
         exit(-1);
     }              

     const uint8_t *byte = &data[(row*max_col + col)/8];
#if DEBUG
     return get_bit(file, line, byte, col%8);
#else
     return get_bit(byte, col%8);
#endif         
}
#if DEBUG
void one_bit_matrix_set_bit(const char* file, int line, uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col, uint8_t value)
#else
void one_bit_matrix_set_bit(uint8_t *data, uint8_t row, uint8_t max_row, uint8_t col, uint8_t max_col, uint8_t value)
#endif         
{
//     fprintf(fp, "(1_bit_matrix_set_bit) index out of bound (max_row = %d, max_col = %d)\n", max_row, max_col);
     if(row >= max_row)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (1_bit_matrix_set_bit) index out of bound (row = %d, max_row = %d)\n", file, line, row, max_row);
#else
         fprintf(fp, "ERROR: (1_bit_matrix_set_bit) index out of bound (row = %d, max_row = %d)\n", row, max_row);
#endif         
         exit(-1);
     }              
     
     if(col >= max_col)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (1_bit_matrix_set_bit) index out of bound (col = %d, max_col = %d)\n", file, line, col, max_col);
#else
         fprintf(fp, "ERROR: (1_bit_matrix_set_bit) index out of bound (col = %d, max_col = %d)\n", col, max_col);
#endif         
         exit(-1);
     }              

     uint8_t *byte = &data[(row*max_col + col)/8];
#if DEBUG
     set_bit(file, line, byte, col%8, value);
#else
     set_bit(byte, col%8, value);
#endif         
}
#if DEBUG
#define ONEBIT_MATRIX_GET_BIT(data, row, col)            one_bit_matrix_get_bit(__FILE__, __LINE__, (uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8)
#define ONEBIT_MATRIX_SET_BIT(data, row, col, value)     one_bit_matrix_set_bit(__FILE__, __LINE__, (uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8, value)
#else
#define ONEBIT_MATRIX_GET_BIT(data, row, col)            one_bit_matrix_get_bit((uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8)
#define ONEBIT_MATRIX_SET_BIT(data, row, col, value)     one_bit_matrix_set_bit((uint8_t *)data, row, sizeof(data)/sizeof(data[0]), col, (sizeof(data[0])/sizeof(data[0][0]))*8, value)
#endif         
#endif
