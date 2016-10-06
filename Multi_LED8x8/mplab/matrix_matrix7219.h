#ifndef MATRIX_MATRIX7219_H
#define MATRIX_MATRIX7219_H

#define MATRIX_COLUMN_MAX 16
#define MATRIX_ROW_MAX    8

#define MATRIX8x8_COLUMN_MAX 8
#define MATRIX8x8_ROW_MAX 8

#define MATRIX_MATRIX8x8_COLUMN_MAX (MATRIX_COLUMN_MAX/MATRIX8x8_COLUMN_MAX)
#define MATRIX_MATRIX8x8_ROW_MAX    (MATRIX_ROW_MAX/MATRIX8x8_ROW_MAX)

typedef struct 
{
    uint8_t  data[MATRIX8x8_COLUMN_MAX];
} MATRIX7219;

typedef struct 
{
    MATRIX7219  data[MATRIX_MATRIX8x8_ROW_MAX][MATRIX_MATRIX8x8_COLUMN_MAX];
} MATRIX_MATRIX7219;

MATRIX7219* get_matrix7219(const MATRIX_MATRIX7219* matrix_matrix, uint8_t matrix_row, uint8_t matrix_col)
{
    return &matrix_matrix->data[matrix_row/MATRIX8x8_ROW_MAX][matrix_col/MATRIX8x8_COLUMN_MAX];
}
uint8_t get_matrix7219_bit(const MATRIX7219* matrix, uint8_t row, uint8_t col)
{
    uint8_t mask = 0x80 >> row;

    if((matrix->data[col] & mask) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t set_matrix7219_bit(MATRIX7219* matrix, uint8_t row, uint8_t col, uint8_t value)
{
    uint8_t mask = 0x80 >> row;
    
    if(value > 0)
    {
        matrix->data[col] |= mask;
    }
    else
    {
        mask = ~mask;
        matrix->data[col] &= mask;
    }
}

uint8_t get_matrix_matrix7219_bit(const MATRIX_MATRIX7219* matrix_matrix, uint8_t matrix_row, uint8_t matrix_col)
{
    MATRIX7219* matrix = get_matrix7219(matrix_matrix, matrix_row, matrix_col);    

    return get_matrix7219_bit(matrix, matrix_row%MATRIX8x8_ROW_MAX, matrix_col%MATRIX8x8_COLUMN_MAX);
}
void set_matrix_matrix7219_bit(MATRIX_MATRIX7219* matrix_matrix, uint8_t matrix_row, uint8_t matrix_col, uint8_t value)
{
    MATRIX7219* matrix = get_matrix7219(matrix_matrix, matrix_row, matrix_col);    

    set_matrix7219_bit(matrix, matrix_row%MATRIX8x8_ROW_MAX, matrix_col%MATRIX8x8_COLUMN_MAX, value);
}
#endif // MATRIX_MATRIX7219_H