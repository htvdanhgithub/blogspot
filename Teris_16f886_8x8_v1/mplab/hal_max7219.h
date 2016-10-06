/*
This file contains functions to drive max7219.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
typedef struct 
{
    uint8_t  col[MATRIX8x8_COLUMN_MAX];
} MATRIX7219;

void hal_MATRIX8x8_to_MATRIX7219(const MATRIX8x8* matrix8x8, MATRIX7219* matrix7219)
{
    uint8_t mask = 0x80;
    uint8_t row;

    for(uint8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
    {
        mask = 0x80;
        matrix7219->col[col] = 0;
        for(row = 0; row < MATRIX8x8_ROW_MAX; row++)
        {
            if(get_matrix_bit(matrix8x8->row, row, col) == 1)
            {
                matrix7219->col[col] |= mask;
            }
            mask >>= 1;
        }
        mask = 0x80;
    }
}
void hal_print_MATRIX7219(const MATRIX7219* matrix7219)
{
    uint8_t col;

    for (col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
    {
        Write_Byte(col + 1, matrix7219->col[col]);
    }
}
void hal_print_MATRIX8x8(const MATRIX8x8* matrix88)
{
    MATRIX7219 matrix7219;
    hal_MATRIX8x8_to_MATRIX7219(matrix88, &matrix7219);
    hal_print_MATRIX7219(&matrix7219);
}
