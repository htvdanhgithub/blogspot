/*
This file contains common debugging functions.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#if WINDOW_BASE
#include "debug_window.h"
#else
#include "debug_uart.h"
#endif

#if DEBUG
void dbg_print_MATRIX4x4(uint8_t enable, const char* lable, int8_t x, int8_t y, const MATRIX4x4* matrix)
{
    if((DEBUG) && (enable))
    {
    	if(lable != NULL)
    	{
    	    dbg_print(1, lable);
    	    dbg_print_line(1, ":");
    	}
        dbg_print_line(1, "<<<<<<<<<<<<<<<<<<<<MATRIX4x4");
        for(int8_t row = 0; row < MATRIX8x8_ROW_MAX; row++)
        {
            for(int8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
            {
                if((row - y >= 0) && (row - y < MATRIX4x4_ROW_MAX)
                && (col - x >= 0) && (col - x < MATRIX4x4_COLUMN_MAX)
                && (get_matrix_bit(matrix->row, row - y, col - x) == 1))
                {
                    dbg_print(1, "*");
                }
                else
                {
                    dbg_print(1, "_");
                }
            }
    		dbg_print_line(1, "");
        }
    	dbg_print_line(1, ">>>>>>>>>>>>>>>>>>>>");

    }
}
#define dbg_print_MATRIX4x4(enable, lable, x, y, matrix) dbg_print_MATRIX4x4(enable, lable, x, y, matrix)
#else
#define dbg_print_MATRIX4x4(enable, lable, x, y, matrix) ;
#endif

#if DEBUG
void dbg_print_MATRIX8x8(uint8_t enable, const char* lable, const MATRIX8x8* matrix)
{
    if((DEBUG) && (enable))
    {
    	if(lable != NULL)
    	{
    	    dbg_print(1, lable);
    	    dbg_print_line(1, ":");
    	}
        dbg_print_line(1, "<<<<<<<<<<<<<<<<<<<<MATRIX8x8");
        for(uint8_t row = 0; row < MATRIX8x8_ROW_MAX; row++)
        {
            for(uint8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
            {
                if(get_matrix_bit((uint8_t*)matrix->row, row, col) == 1)
                {
                    dbg_print(1, "*");
                }
                else
                {
                    dbg_print(1, "_");
                }
            }
            dbg_print_line(1, "");
        }
        dbg_print_line(1, ">>>>>>>>>>>>>>>>>>>>");
    }
}
#define dbg_print_MATRIX8x8(enable, lable, matrix) dbg_print_MATRIX8x8(enable, lable, matrix)
#else
#define dbg_print_MATRIX8x8(enable, lable, matrix) ;
#endif

#if DEBUG
void dbg_print_MATRIX7219(uint8_t enable, const char* lable, const MATRIX7219* matrix)
{
    if((DEBUG) && (enable))
    {
        uint8_t mask = 0x80;

    	if(lable != NULL)
    	{
    	    dbg_print(1, lable);
    	    dbg_print_line(1, ":");
    	}
        dbg_print_line(1, "<<<<<<<<<<<<<<<<<<<<");

        for(uint8_t row = 0; row < MATRIX8x8_ROW_MAX; row++)
        {
            for(uint8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
            {
                if((matrix->col[col] & mask) > 0)
                {
                    dbg_print(1, "*");
                }
                else
                {
                    dbg_print(1, "_");
                }
            }

            dbg_print_line(1, "");
            mask >>= 1;
        }
        dbg_print_line(1, ">>>>>>>>>>>>>>>>>>>>");

    }
}
#define dbg_print_MATRIX7219(enable, lable, matrix) dbg_print_MATRIX7219(enable, lable, matrix)
#else
#define dbg_print_MATRIX7219(enable, lable, matrix) ;
#endif

#if DEBUG
void dbg_print_Screen(uint8_t enable, const char* lable)
{
    if((DEBUG) && (enable))
    {
    	if(lable != NULL)
    	{
    	    dbg_print(1, lable);
    	    dbg_print_line(1, ":");
    	}
        dbg_print_MATRIX8x8(1, NULL, &g_matrix8x8);

    }
}
#define dbg_print_Screen(enable, lable) dbg_print_Screen(enable, lable)
#else
#define dbg_print_Screen(enable, lable) ;
#endif

#if DEBUG
void dbg_print_cur_MATRIX4x4(uint8_t enable, const char* lable, int8_t x, int8_t y)
{
    if((DEBUG) && (enable))
    {
    	if(lable != NULL)
    	{
    	    dbg_print(1, lable);
    	    dbg_print_line(1, ":");
    	}
        MATRIX4x4* matrix = &g_matrix4x4[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
        dbg_print_MATRIX4x4(1, NULL, x, y, matrix);
    }
}
#define dbg_print_cur_MATRIX4x4(enable, lable, x, y) dbg_print_cur_MATRIX4x4(enable, lable, x, y)
#else
#define dbg_print_cur_MATRIX4x4(enable, lable, x, y) ;
#endif
