#ifndef HAL_WINDOW_H
#define HAL_WINDOW_H

void hal_print_MATRIX16x8(const MATRIX16x8* matrix88)
{
    printf("<<<<<<<<<<<<<<<<<<<<MATRIX16x8\n");
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX16x8_COLUMN_MAX; col++)
        {
            if(get_matrix_bit((uint8_t*)matrix88->row, row, col) == 1)
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
}
#endif // HAL_WINDOW_H