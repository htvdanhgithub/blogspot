#ifndef HAL_MATRIX7219_H
#define HAL_MATRIX7219_H

#include "max7219.h"

void hal_MATRIX16x8_to_MATRIX_MATRIX7219(const MATRIX16x8* matrix16x8, MATRIX_MATRIX7219* matrix7219)
{
    for(uint8_t col = 0; col < MATRIX_COLUMN_MAX; col++)
    {
        for(uint8_t row = 0; row < MATRIX_ROW_MAX; row++)
        {
            set_matrix_matrix7219_bit(matrix7219, row, col, get_matrix_bit(matrix16x8->row, row, col));
        }
    }
}
void hal_print_MATRIX_MATRIX7219(const MATRIX_MATRIX7219* matrix7219)
{
    DRV_MATRIX_MATRIX7219 matrix;
    
    uint8_t col;

    for (col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
    {
        for(uint8_t matrix_row = 0; matrix_row < MATRIX_MATRIX8x8_ROW_MAX; matrix_row++)
        {
            for(uint8_t matrix_col = 0; matrix_col < MATRIX_MATRIX8x8_COLUMN_MAX; matrix_col++)
            {
                matrix.data[matrix_row][matrix_col] = matrix7219->data[matrix_row][matrix_col].data[col];
            }
        }
        Write_Matrix(&matrix, 1, col);
    }
}
void hal_print_MATRIX16x8(const MATRIX16x8* matrix88)
{
    MATRIX_MATRIX7219 matrix7219;
    hal_MATRIX16x8_to_MATRIX_MATRIX7219(matrix88, &matrix7219);
    hal_print_MATRIX_MATRIX7219(&matrix7219);
}
#endif // HAL_MATRIX7219_H