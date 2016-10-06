/*
This file contains functions to get/set a specific bit in a byte.
How to use: http://htvdanh.blogspot.com/2016/09/one-bit-matrix-for-cc-programming.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 9th, 2016
*/

#ifndef BIT_LIB_H
#define BIT_LIB_H

#define MAX_BYTE_BIT 8

typedef struct 
{
    uint8_t b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} BYTE_t;

extern FILE* fp;
#if DEBUG

uint8_t get_bit(const char* file, int line, const uint8_t *byte, uint8_t at)
#else
uint8_t get_bit(const uint8_t *byte, uint8_t at)
#endif
{
     if(at >= MAX_BYTE_BIT)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (get_bit) bit out of bound (at = %d)\n", file, line, at);
#else
         fprintf(fp, "ERROR: (get_bit) bit out of bound (at = %d)\n", at);
#endif
         exit(-1);
     }              
     BYTE_t *temp = (BYTE_t *)byte;
     switch(at)
     {
         case 0:
              return ((uint8_t)temp->b0);
              break;                     
         case 1:
              return ((uint8_t)temp->b1);
              break;                     
         case 2:
              return ((uint8_t)temp->b2);
              break;                     
         case 3:
              return ((uint8_t)temp->b3);
              break;                     
         case 4:
              return ((uint8_t)temp->b4);
              break;                     
         case 5:
              return ((uint8_t)temp->b5);
              break;                     
         case 6:
              return ((uint8_t)temp->b6);
              break;                     
         case 7:
              return ((uint8_t)temp->b7);
              break;                     
     }  
}

#if DEBUG
void set_bit(const char* file, int line, uint8_t *byte, uint8_t at, uint8_t value)
#else
void set_bit(uint8_t *byte, uint8_t at, uint8_t value)
#endif
{
     if(at >= MAX_BYTE_BIT)
     {
#if DEBUG
         fprintf(fp, "%s:%d ERROR: (set_bit) bit out of bound (at = %d)\n", file, line, at);
#else
         fprintf(fp, "ERROR: (set_bit) bit out of bound (at = %d)\n", at);
#endif
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
}
#if DEBUG
#define GET_BIT(byte, at) get_bit(__FILE__, __LINE__, byte, at)
#define SET_BIT(byte, at, value) set_bit(__FILE__, __LINE__, byte, at, value)
#else
#define GET_BIT(byte, at) get_bit(byte, at)
#define SET_BIT(byte, at, value) set_bit(byte, at, value)
#endif
#endif
