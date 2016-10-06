/*
This file demonstrates using unitest framework.
How to use: http://htvdanh.blogspot.com/2016/09/light-weight-unit-test-framework-for-cc.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 9th, 2016
*/

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "unittest.h"

const char* get_greeting()
{
      return "Hello";
}        

int main(int argc, char *argv[])
{
  ut_testsuite_run();

  system("PAUSE");	
  return 0;
}
