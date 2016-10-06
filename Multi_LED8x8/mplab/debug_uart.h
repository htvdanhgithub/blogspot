/*
This file contains common debugging functions for UART (micro PIC).
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#include "usart_pic16.h"

#if DEBUG
#define G_DEBUG_LEN 64
char g_debug[G_DEBUG_LEN];
#endif

#if DEBUG
#define dbg_print(enable, fmt) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print(enable, fmt) ;
#endif

#if DEBUG
#define dbg_print_line(enable, fmt) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt"\r\n"); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print_line(enable, fmt) ;
#endif

#if DEBUG
#define dbg_print1(enable, fmt, x1) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt"\r\n", x1); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print1(enable, fmt, x1) ;
#endif                          

#if DEBUG
#define dbg_print2(enable, fmt, x1, x2) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt"\r\n", x1, x2); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print2(enable, fmt, x1, x2) ;
#endif    

#if DEBUG
#define dbg_print3(enable, fmt, x1, x2, x3) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt"\r\n", x1, x2, x3); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print3(enable, fmt, x1, x2, x3) ;
#endif

#if DEBUG
#define dbg_print4(enable, fmt, x1, x2, x3, x4) \
do { \
    if(enable) \
    { \
    	int n = sprintf(g_debug, fmt"\r\n", x1, x2, x3, x4); \
    	if(n > G_DEBUG_LEN) \
		{ \
			USARTWriteString("ERROR: g_debug is overflowed\r\n"); \
			exit(-1); \
		} \
        USARTWriteString(g_debug); \
    } \
} while (0);
#else
#define dbg_print4(enable, fmt, x1, x2, x3, x4) ;
#endif
void dbg_init()
{
    USARTInit(9600);
} 
void dbg_close()
{
}                                         
#endif //DEBUG_UART_H
