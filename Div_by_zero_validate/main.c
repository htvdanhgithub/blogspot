/*
This file contains example using utilities to detect "divide by ZERO" error.
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-divide-by.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 5th, 2016
*/

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include "div_by_zero_validate.h"

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

int main(int argc, char *argv[])
{
    dbg_init();
    //<<<<<<<<<<<<<Example1
//    int z = 0;
//    int a = DIV_INT(10, z); // divide by ZERO
    //>>>>>>>>>>>>>Example1
    
    //<<<<<<<<<<<<<Example2
//    int z = 0;
//    int a = MOD_INT(10, z); // divide by ZERO
    //>>>>>>>>>>>>>Example2
    
    //<<<<<<<<<<<<<Example3
//    float f = 0.0;
//    float a = DIV_FLOAT(10, f); // divide by ZERO
    //>>>>>>>>>>>>>Example3
    
    //<<<<<<<<<<<<<Example4
    double d = 0.0;
    double a = DIV_DOUBLE(10, d); // divide by ZERO
    //>>>>>>>>>>>>>Example4
    
    dbg_close();  
    system("PAUSE");	
    return 0;
}
