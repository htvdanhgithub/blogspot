/*
This file contains example using utilities to detect NULL pointer and buffer overflow in memcpy, memset, strcpy.
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-null.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 5th, 2016
*/

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include "mem_validate.h"

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
//  int* a = NULL;
//  int b = 123; 
//  MEMCPY(a, sizeof(*a), &b, sizeof(b), sizeof(int)); // NULL pointer error
//>>>>>>>>>>>>>Example1

//<<<<<<<<<<<<<Example2
//  int* a = NULL;
//  MEMSET(a, sizeof(*a), 0, sizeof(int)); // NULL pointer error
//>>>>>>>>>>>>>Example2

//<<<<<<<<<<<<<Example3
//  int a = 123;
//  int b = 456; 
//  MEMCPY(&a, sizeof(a), &b, sizeof(b), 10); // buffer overflow, sizeof(a) = sizeof(int) and sizeof(b) = sizeof(int) less than 10
//>>>>>>>>>>>>>Example3

//<<<<<<<<<<<<<Example4
//  int a[3];
//  int b[4]; 
//  MEMCPY_ARRAY(a, b, 10*sizeof(int)); // buffer overflow, sizeof(a) = 3*sizeof(int) and sizeof(b) = 4*sizeof(int) less than 10*sizeof(int)//>>>>>>>>>>>>>Example4
//>>>>>>>>>>>>>Example4

//<<<<<<<<<<<<<Example5
//  int a;
//  MEMSET(&a, sizeof(a), 0, 10*sizeof(int)); // buffer overflow, sizeof(a) = sizeof(int) less than 10*sizeof(int)
//>>>>>>>>>>>>>Example5

//<<<<<<<<<<<<<Example6
//  int a[3];
//  MEMSET_ARRAY(a, 0, 10*sizeof(int)); // buffer overflow, sizeof(a) = 3*sizeof(int) less than 10*sizeof(int)
//>>>>>>>>>>>>>Example6

//<<<<<<<<<<<<<Example7
//  char a[3] = "12";
//  char *b = NULL;
//  STRCPY(a, 3, b, 0); // NULL pointer
//>>>>>>>>>>>>>Example7
  
//<<<<<<<<<<<<<Example8
  char a[3] = "12";
  char b[4]= "123";
  STRCPY_ARRAY(a, b); // buffer overflow as len of b is greater than a
//>>>>>>>>>>>>>Example8

  dbg_close();  
  system("PAUSE");	
  return 0;
}
