/*
This file contains common definition and data structure.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
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
#include <stdint.h>
#include <stdarg.h>
#include "myutils.h"
#include "myutils.h"
#include <pic16f886.h>
#endif

#define OK 1
#define NG 0

#define YES 1
#define NO 0

#define TRUE 1
#define FALSE 0

#define ENTER_FUNC \
{ \
    g_debug_tab++; \
    dbg_print1(1, "%s<<<<%s(%s:%d):\n", debug_tab[g_debug_tab]); \
}        
#define EXIT_FUNC \
{ \
    dbg_print1(1, "%s>>>>%s(%d)\n", debug_tab[g_debug_tab]); \
    g_debug_tab--; \
    return; \
}        
#define EXIT_FUNC1(x) \
{ \
    dbg_print1(1, "%s>>>>%s(%d): return = %d\n", debug_tab[g_debug_tab]); \
    g_debug_tab--; \
    return x; \
}        
#if WINDOW_BASE

#define MATRIX_WIDTH_MAX 32
#define MATRIX_HEIGHT_MAX 32

typedef struct 
{
    uint8_t data[MATRIX_HEIGHT_MAX][MATRIX_WIDTH_MAX/8];
} MATRIX_t;
#if WINDOW_BASE
    FILE *fp;
#endif

#endif
char *debug_tab[] = 
{
    "",
    "\t",
    "\t\t",
    "\t\t\t",
    "\t\t\t\t",
    "\t\t\t\t\t",
    "\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t",
};
int g_debug_tab = -1;

#define MATRIX8x8_COLUMN_MAX 8
#define MATRIX8x8_ROW_MAX 8

#define MATRIX_MATRIX8x8_COLUMN_MAX 4
#define MATRIX_MATRIX8x8_ROW_MAX    3

typedef struct 
{
    uint8_t  data[MATRIX8x8_COLUMN_MAX];
} MATRIX8x8;

typedef struct 
{
    MATRIX8x8  data[MATRIX_MATRIX8x8_ROW_MAX][MATRIX_MATRIX8x8_COLUMN_MAX];
} MATRIX_MATRIX8x8;

typedef struct 
{
    uint8_t  data[MATRIX_MATRIX8x8_ROW_MAX][MATRIX_MATRIX8x8_COLUMN_MAX];
} MATRIX_MATRIX7219;

MATRIX_MATRIX8x8 g_matrix_matrix8x8 =
{
0x0, 0x7F, 0x90, 0x90, 0x90, 0x7F, 0x0,	0x0, 0x0, 0xFF,	0x91, 0x91,	0x91, 0x6E,	0x0, 0x0, 0x0, 0x7E, 0x81, 0x81, 0x81, 0x42, 0x0, 0x0,		0x0,	0xFF,	0x81,	0x81,	0x81,	0x7E,	0x0,	0x0,
0x0, 0xFF, 0x91, 0x91, 0x91, 0x91, 0x0,	0x0, 0x0, 0xFF,	0x90, 0x90,	0x90, 0x90,	0x0, 0x0, 0x0, 0x7E, 0x81, 0x81, 0x89, 0x4E, 0x8, 0x0,		0x0,	0xFF,	0x10,	0x10,	0x10,	0xFF,	0x0,	0x0,
0x0, 0xFF, 0x18, 0x24, 0x42, 0x81, 0x0,	0x0, 0x0, 0xFF,	0x1,  0x1,	0x1,  0x1,	0x0, 0x0, 0x0, 0xFF, 0x40, 0x20, 0x10, 0x20, 0x40, 0xFF,		0x0,	0xFF,	0x40,	0x20,	0x10,	0x8,	0xFF,	0x0,
};
#endif //COMMON_H
