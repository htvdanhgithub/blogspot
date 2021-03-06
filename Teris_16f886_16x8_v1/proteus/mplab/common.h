#ifndef COMMON_H
#define COMMON_H

#if WINDOW_BASE
#include <stdint.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#else
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <pic16f886.h>
#include "usart_pic16.h"
#include "myutils.h"
#endif

#include "matrix_matrix7219.h"

#define OK 1
#define NG 0

#define YES 1
#define NO 0

#define TRUE 1
#define FALSE 0

#define DEBUG_ENABLE  1
#define DEBUG_DISABLE 0

#define MATRIX4x4_COLUMN_MAX 4
#define MATRIX4x4_ROW_MAX 4

#define MATRIX8x8_COLUMN_MAX 8
#define MATRIX8x8_ROW_MAX 8

#define MATRIX16x8_COLUMN_MAX 8
#define MATRIX16x8_ROW_MAX 16

#define CHARACTER_MAX 9

#if WINDOW_BASE
#define DELAY_MS(x) Sleep(x)
#else
#define DELAY_MS(x) __delay_ms(x)
#endif

#if WINDOW_BASE        
#define UINT8_T_ARRAY1(array, x) ARRAY1(uint8_t, array, x)
#define UINT8_T_ARRAY2(array, x, y) ARRAY2(uint8_t, array, x, y)
#define MATRIX4x4_ARRAY1(array, x) ARRAY1(MATRIX4x4, array, x)
#define CHARACTER_INFO_ARRAY1(array, x) ARRAY1(CHARACTER_INFO, array, x)
#define UINT8_T_P_ARRAY1(array, x) ARRAY1(uint8_t*, array, x)
#else
#define UINT8_T_ARRAY1(array, x) array[x]
#define UINT8_T_ARRAY2(array, x, y) array[x][y]
#define MATRIX4x4_ARRAY1(array, x) array[x]
#define CHARACTER_INFO_ARRAY1(array, x) array[x]
#define UINT8_T_P_ARRAY1(array, x) array[x]
#endif

typedef struct 
{
    uint8_t start_index;
    uint8_t num;
} CHARACTER_INFO;

typedef struct 
{
    uint8_t  row[MATRIX4x4_ROW_MAX];
} MATRIX4x4;
typedef struct 
{
    uint8_t  row[MATRIX16x8_ROW_MAX];
} MATRIX16x8;

CHARACTER_INFO g_char_info[CHARACTER_MAX] =
{
////////I/////////////
{0, 2},
////////s/////////////
{2, 2},
////////back s/////////////
{4, 2},
////////back L/////////////
{6, 4},
////////L/////////////
{10, 4},
////////box/////////////
{14, 1},
////////V/////////////
{15, 4},
////////+/////////////
{19, 1},
////////T/////////////
{20, 4},
};
uint8_t g_char_info_index;
uint8_t g_char_info_sub_index;
MATRIX4x4* g_cur_matrix4x4;
#if WINDOW_BASE
MATRIX4x4 g_matrix4x4[] =
#else
const MATRIX4x4 g_matrix4x4[] =
#endif
{
////////I/////////////
{0x2,
0x2,
0x2,
0x2},

{0x0,
0xF,
0x0,
0x0},

////////s/////////////
{0x6,
0x3,
0x0,
0x0},

{0x2,
0x6,
0x4,
0x0},

////////back s/////////////
{0x3,
0x6,
0x0,
0x0},

{0x2,
0x3,
0x1,
0x0},

////////back L/////////////
{0x0,
0x7,
0x4,
0x0},

{0x6,
0x2,
0x2,
0x0},

{0x1,
0x7,
0x0,
0x0},

{0x2,
0x2,
0x3,
0x0},

////////L/////////////
{0x0,
0x7,
0x1,
0x0},

{0x3,
0x2,
0x2,
0x0},

{0x4,
0x7,
0x0,
0x0},

{0x2,
0x2,
0x6,
0x0},

////////box/////////////
{0x3,
0x3,
0x0,
0x0},

////////V/////////////
{0x0,
0x6,
0x2,
0x0},

{0x0,
0x3,
0x2,
0x0},

{0x2,
0x3,
0x0,
0x0},

{0x2,
0x6,
0x0,
0x0},

////////+/////////////
{0x2,
0x7,
0x2,
0x0},

////////T/////////////
{0x7,
0x2,
0x2,
0x0},

{0x4,
0x7,
0x4,
0x0},

{0x2,
0x2,
0x7,
0x0},

{0x1,
0x7,
0x1,
0x0},
};
MATRIX16x8 g_matrix16x8 =
{
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
0x0,
};
int8_t cur_x = 2;
int8_t cur_y = 0;

#if !WINDOW_BASE
#define SEED_EEPROM_INDEX 0
unsigned Seed;
#endif
#endif // COMMON_H