/*
This file contains some utilities to detect "divide by ZERO" errors
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-divide-by.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 5th, 2016
*/
#ifndef DIV_BY_ZERO_VALIDATE_H
#define DIV_BY_ZERO_VALIDATE_H

#include <stdint.h>

#if DEBUG
FILE *fp;

long long div_long_long(char* file, int line, long long x, long long y)
{
    fprintf(fp, "div x = %d, y = %d\n", x, y);
    if(y == 0)
    {
         fprintf(fp, "%s:%d ERROR: divide by ZERO (x = %d, y = %d)\n", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
long long mod_long_long(char* file, int line, long long x, long long y)
{
    fprintf(fp, "mod_int x = %d, y = %d\n", x, y);
    if(y == 0)
    {
         fprintf(fp, "%s:%d ERROR: modulo by ZERO (x = %d, y = %d)\n", file, line, x, y);
         exit(-1);
    }     
    return x%y;
}
float div_float(char* file, int line, float x, float y)
{
    fprintf(fp, "div_float x = %f, y = %f\n", x, y);
    if(y == (float)0.0)
    {
         fprintf(fp, "%s:%d ERROR: divide by ZERO (x = %f, y = %f)\n", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
double div_double(char* file, int line, double x, double y)
{
    fprintf(fp, "div_double x = %f, y = %f\n", x, y);
    if(y == (double)0.0)
    {
         fprintf(fp, "%s:%d ERROR: divide by ZERO (x = %f, y = %f)\n", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
#define DIV_TYPE(TYPE, x, y) (TYPE)div_long_long(__FILE__, __LINE__, (TYPE)x, (TYPE)y)
#define MOD_TYPE(TYPE, x, y) (TYPE)mod_long_long(__FILE__, __LINE__, (TYPE)x, (TYPE)y)

#define DIV_CHAR(x, y)    DIV_TYPE(char, x, y)
#define MOD_CHAR(x, y)    MOD_TYPE(char, x, y)
#define DIV_UCHAR(x, y)   DIV_TYPE(unsigned char, x, y)
#define MOD_UCHAR(x, y)   MOD_TYPE(unsigned char, x, y)
#define DIV_INT(x, y)     DIV_TYPE(int, x, y)
#define MOD_INT(x, y)     MOD_TYPE(int, x, y)
#define DIV_UINT(x, y)    DIV_TYPE(unsigned int, x, y)
#define MOD_UINT(x, y)    MOD_TYPE(unsigned int, x, y)
#define DIV_LONG(x, y)    DIV_TYPE(long, x, y)
#define MOD_LONG(x, y)    MOD_TYPE(long, x, y)
#define DIV_ULONG(x, y)   DIV_TYPE(unsigned long, x, y)
#define MOD_ULONG(x, y)   MOD_TYPE(unsigned long, x, y)
#define DIV_FLOAT(x, y)   div_float(__FILE__, __LINE__, x, y)
#define DIV_DOUBLE(x, y)  div_double(__FILE__, __LINE__, x, y)
#else
#define DIV_CHAR(x, y)    (x/y)
#define MOD_CHAR(x, y)    (x%y)
#define DIV_UCHAR(x, y)   (x/y)
#define MOD_UCHAR(x, y)   (x%y)
#define DIV_INT(x, y)     (x/y)
#define MOD_INT(x, y)     (x%y)
#define DIV_UINT(x, y)    (x/y)
#define MOD_UINT(x, y)    (x%y)
#define DIV_LONG(x, y)    (x/y)
#define MOD_LONG(x, y)    (x%y)
#define DIV_ULONG(x, y)   (x/y)
#define MOD_ULONG(x, y)   (x%y)
#define DIV_FLOAT(x, y)   (x/y)
#define DIV_DOUBLE(x, y)  (x/y)
#endif
#endif
