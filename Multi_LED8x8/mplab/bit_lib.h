/*
This file contains functions to handle bit in a byte.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 24th, 2016
*/
#ifndef BIT_LIB_H
#define BIT_LIB_H

#include "common.h"
#include "debug.h"

#define MAX_BYTE_BIT 8

typedef struct 
{
    uint8_t b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} BYTE_t;

uint8_t get_bit(const char* file, int line, const uint8_t *byte, uint8_t at)
{
     ENTER_FUNC;        
     if(at >= MAX_BYTE_BIT)
     {
         dbg_print1(1, "ERROR: (get_bit) bit out of bound (at = %d)", at);
         exit(-1);
     }              
     BYTE_t *temp = (BYTE_t *)byte;
     switch(at)
     {
         case 0:
              EXIT_FUNC1((uint8_t)temp->b0);
              break;                     
         case 1:
              EXIT_FUNC1((uint8_t)temp->b1);
              break;                     
         case 2:
              EXIT_FUNC1((uint8_t)temp->b2);
              break;                     
         case 3:
              EXIT_FUNC1((uint8_t)temp->b3);
              break;                     
         case 4:
              EXIT_FUNC1((uint8_t)temp->b4);
              break;                     
         case 5:
              EXIT_FUNC1((uint8_t)temp->b5);
              break;                     
         case 6:
              EXIT_FUNC1((uint8_t)temp->b6);
              break;                     
         case 7:
              EXIT_FUNC1((uint8_t)temp->b7);
              break;                     
     }  
}

void set_bit(const char* file, int line, uint8_t *byte, uint8_t at, uint8_t value)
{
     ENTER_FUNC;
     if(at >= MAX_BYTE_BIT)
     {
         dbg_print1(1, "ERROR: (set_bit) bit out of bound (at = %d)", at);
         exit(-1);
     }              
     BYTE_t *temp = (BYTE_t *)byte;
     
     switch(at)
     {
         case 0:
              temp->b0 = value;
              break;                     
         case 1:
              temp->b1 = value;
              break;                     
         case 2:
              temp->b2 = value;
              break;                     
         case 3:
              temp->b3 = value;
              break;                     
         case 4:
              temp->b4 = value;
              break;                     
         case 5:
              temp->b5 = value;
              break;                     
         case 6:
              temp->b6 = value;
              break;                     
         case 7:
              temp->b7 = value;
              break;                     
     }  
     EXIT_FUNC;      
}
uint8_t reverse(uint8_t byte)
{
	BYTE_t *temp = (BYTE_t *)&byte;
	BYTE_t res;

    res.b0 = temp->b7;
    res.b1 = temp->b6;
    res.b2 = temp->b5;
    res.b3 = temp->b4;
    res.b4 = temp->b3;
    res.b5 = temp->b2;
    res.b6 = temp->b1;
    res.b7 = temp->b0;
    
    return *((uint8_t *)&res);
}

#define GET_BIT get_bit(__FILE__, __LINE__, byte, at)
#define SET_BIT set_bit(__FILE__, __LINE__, byte, at, value)
#endif
