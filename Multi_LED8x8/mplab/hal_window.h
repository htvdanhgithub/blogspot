/*
This file contains functions to simulate output on LED matrix on Window.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
#ifndef HAL_WINDOW_H
#define HAL_WINDOW_H

void printf_matrix(const MATRIX_t *matrix)
{
     ENTER_FUNC;
     printf("<<<<<<<<<<<<<<<<<<<<\n");
     for(uint8_t row = 0; row < MATRIX_WIDTH_MAX; row++)
     {
         for(uint8_t col = 0; col < MATRIX_HEIGHT_MAX; col++)
         {
                if(MATRIX_GET_BIT(matrix->data, row, col) == 1)     
                {
                    printf("*");                          
                }
                else
                {
                    printf("_");
                }                                                                            
         }                 
         printf("\n");
     }                                  
     printf(">>>>>>>>>>>>>>>>>>>>\n");
     EXIT_FUNC;
}
#endif // HAL_WINDOW_H
