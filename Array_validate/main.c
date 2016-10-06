/*
This file contains example using utilities to detect memory violation in array use: NULL pointer, index out of bound.
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-memory.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 5th, 2016
*/

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include "array_validate.h"

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
//  int *p = NULL;
//  INT_ARRAY1(p, 0) = 0; // p[0] = 0;
//>>>>>>>>>>>>>Example1

//<<<<<<<<<<<<<Example2
//  int  p[3][3][3];
//  INT_ARRAY3(p, 4, 0, 0) = 0; // p[4] = 0;
//>>>>>>>>>>>>>Example2

//<<<<<<<<<<<<<Example3
  int  p[3][3][3];
  int  *q = (int*)p;
  INT_P_ARRAY3(q, 3*3*3*sizeof(int), 3*3*sizeof(int), 3*sizeof(int), sizeof(int), 4, 0, 0) = 0; // p[4] = 0;
//>>>>>>>>>>>>>Example3

  
  dbg_close();  
  system("PAUSE");	
  return 0;
}
