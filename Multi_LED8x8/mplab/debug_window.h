/*
This file contains common debugging functions for simulation on Window.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

extern FILE *fp;

#if DEBUG
#define dbg_print(enable, fmt) \
do { \
    if(enable) \
    { \
        fprintf(fp, fmt); \
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
        fprintf(fp, fmt"\n"); \
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
        fprintf(fp, fmt"\n", x1); \
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
        fprintf(fp, fmt"\n", x1, x2); \
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
        fprintf(fp, fmt"\n", x1, x2, x3); \
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
        fprintf(fp, fmt"\n", x1, x2, x3, x4); \
    } \
} while (0);
#else
#define dbg_print4(enable, fmt, x1, x2, x3, x4) ;
#endif    

void dbg_init()
{
    fp = fopen("debug.txt", "w");
    if(fp==NULL)
    {
        fprintf(fp, "File Not Found");
        exit(-1);
    }     
} 
void dbg_close()
{
    fclose(fp);
}                                         
#endif // DEBUG_WINDOW_H
