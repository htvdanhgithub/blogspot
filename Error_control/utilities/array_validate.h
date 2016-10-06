/*
This file contains some utilities to detect memory violation in array use: NULL pointer, index out of bound.
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-memory.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 5th, 2016
*/

#ifndef ARRAY_VALIDATE_H
#define ARRAY_VALIDATE_H

#include <stdint.h>

#if (DEBUG)
FILE *fp;

void* array1_at(char* file, int line, void * array, int size, int element_size, int x)
{
//    fprintf(fp, "array1_at size = %d, element_size = %d\n", size, element_size);
//    fprintf(fp, "x = %d, max_x = %d\n", x, size/element_size);
    
    if(array == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (array = %p)\n", file, line, array);
         exit(-1);
    }         
    if((x < 0) || (x >= size/element_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/element_size);
         exit(-1);
    }     
//    fprintf(fp, "index = %d\n", x*element_size);
    return ((uint8_t*)array + x*element_size);
}

void* array2_at(char* file, int line, void * array, int size, int x_max_size, int element_size, int x, int y)
{
//    fprintf(fp, "array2_at size = %d, x_max_size = %d, element_size = %d\n", size, x_max_size, element_size);
//    fprintf(fp, "x = %d, max_x = %d\n", x, size/x_max_size);
//    fprintf(fp, "y = %d, max_y = %d\n", y, x_max_size/element_size);

    if(array == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (array = %p)\n", file, line, array);
         exit(-1);
    }         
    if((x < 0) || (x >= size/x_max_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/x_max_size);
         exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/element_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (y = %d, max_y = %d)\n", file, line, y, x_max_size/element_size);
         exit(-1);
    }     
//    fprintf(fp, "index = %d\n", x*x_max_size + y*element_size);
    return ((uint8_t*)array + x*x_max_size + y*element_size);
}

void* array3_at(char* file, int line, void * array, int size, int x_max_size, int y_max_size, int element_size, int x, int y, int z)
{
//    fprintf(fp, "array3_at size = %d, x_max_size = %d, y_max_size = %d, element_size = %d\n", size, x_max_size, y_max_size, element_size);
//    fprintf(fp, "x = %d, max_x = %d\n", x, size/x_max_size);
//    fprintf(fp, "y = %d, max_y = %d\n", y, x_max_size/y_max_size);
//    fprintf(fp, "z = %d, max_z = %d\n", z, y_max_size/element_size);
    if(array == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (array = %p)\n", file, line, array);
         exit(-1);
    }         
    if((x < 0) || (x >= size/x_max_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/x_max_size);
         exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/y_max_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (y = %d, max_y = %d)\n", file, line, y, x_max_size/y_max_size);
         exit(-1);
    }     
    if((z < 0) || (z >= y_max_size/element_size))
    {
         fprintf(fp, "%s:%d ERROR: out of bound (z = %d, max_z = %d)\n", file, line, z, y_max_size/element_size);
         exit(-1);
    }     

//    fprintf(fp, "index = %d\n", x*x_max_size + y*y_max_size + z*element_size);
    return ((uint8_t*)array + x*x_max_size + y*y_max_size + z*element_size);
}
#define ARRAY1(TYPE, array, x)             (*((TYPE*)array1_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), x)))
#define ARRAY2(TYPE, array, x, y)          (*((TYPE*)array2_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), x, y)))
#define ARRAY3(TYPE, array, x, y, z)       (*((TYPE*)array3_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), sizeof(array[0][0][0]), x, y, z)))

#define ARRAY1_P(TYPE, array, array_size, element_size, x)                                  (*((TYPE*)array1_at(__FILE__, __LINE__, array, array_size, element_size, x)))
#define ARRAY2_P(TYPE, array, array_size, x_size, element_size, x, y)                (*((TYPE*)array2_at(__FILE__, __LINE__, array, array_size, x_size, element_size, x, y)))
#define ARRAY3_P(TYPE, array, array_size, yz_size, y_size, element_size, x, y, z)    (*((TYPE*)array3_at(__FILE__, __LINE__, array, array_size, yz_size, y_size, element_size, x, y, z)))
#endif

#if (DEBUG)
#define CHAR_ARRAY1(array, x)                               ARRAY1(char, array, x)
#define CHAR_P_ARRAY1(array, array_size, element_size, x)   ARRAY1_P(char, array, array_size, element_size, x)
#define UCHAR_ARRAY1(array, x)                              ARRAY1(unsigned char, array, x)
#define UCHAR_P_ARRAY1(array, array_size, element_size, x)  ARRAY1_P(unsigned char, array, array_size, element_size, x)
#define INT_ARRAY1(array, x)                                ARRAY1(int, array, x)
#define INT_P_ARRAY1(array, array_size, element_size, x)    ARRAY1_P(int, array, array_size, element_size, x)
#define UINT_ARRAY1(array, x)                               ARRAY1(unsigned int, array, x)
#define UINT_P_ARRAY1(array, array_size, element_size, x)   ARRAY1_P(unsigned int, array, array_size, element_size, x)
#define LONG_ARRAY1(array, x)                               ARRAY1(long, array, x)
#define LONG_P_ARRAY1(array, array_size, element_size, x)   ARRAY1_P(long, array, array_size, element_size, x)
#define ULONG_ARRAY1(array, x)                              ARRAY1(unsigned long, array, x)
#define ULONG_P_ARRAY1(array, array_size, element_size, x)  ARRAY1_P(unsigned long, array, array_size, element_size, x)
#define FLOAT_ARRAY1(array, x)                              ARRAY1(char, array, x)
#define FLOAT_P_ARRAY1(array, array_size, element_size, x)  ARRAY1_P(char, array, array_size, element_size, x)
#define DOUBLE_ARRAY1(array, x)                             ARRAY1(char, array, x)
#define DOUBLE_P_ARRAY1(array, array_size, element_size, x) ARRAY1_P(char, array, array_size, element_size, x)
#else
#define CHAR_ARRAY1(array, x)                               (array[x])
#define CHAR_P_ARRAY1(array, array_size, element_size, x)   (array[x])
#define UCHAR_ARRAY1(array, x)                              (array[x])
#define UCHAR_P_ARRAY1(array, array_size, element_size, x)  (array[x])
#define INT_ARRAY1(array, x)                                (array[x])
#define INT_P_ARRAY1(array, array_size, element_size, x)    (array[x])
#define UINT_ARRAY1(array, x)                               (array[x])
#define UINT_P_ARRAY1(array, array_size, element_size, x)   (array[x])
#define LONG_ARRAY1(array, x)                               (array[x])
#define LONG_P_ARRAY1(array, array_size, element_size, x)   (array[x])
#define ULONG_ARRAY1(array, x)                              (array[x])
#define ULONG_P_ARRAY1(array, array_size, element_size, x)  (array[x])
#define FLOAT_ARRAY1(array, x)                              (array[x])
#define FLOAT_P_ARRAY1(array, array_size, element_size, x)  (array[x])
#define DOUBLE_ARRAY1(array, x)                             (array[x])
#define DOUBLE_P_ARRAY1(array, array_size, element_size, x) (array[x])
#endif

#if (DEBUG)
#define CHAR_ARRAY2(array, x, y)                                           ARRAY2(char, array, x, y)
#define CHAR_P_ARRAY2(array, array_size, x_size, element_size, x, y)       ARRAY2_P(char, array, array_size, x_size, element_size, x, y)
#define UCHAR_ARRAY2(array, x, y)                                          ARRAY2(unsigned char, array, x, y)
#define UCHAR_P_ARRAY2(array, array_size, x_size, element_size, x, y)      ARRAY2_P(unsigned char, array, array_size, x_size, element_size, x, y)
#define INT_ARRAY2(array, x, y)                                            ARRAY2(int, array, x, y)
#define INT_P_ARRAY2(array, array_size, x_size, element_size, x, y)        ARRAY2_P(int, array, array_size, x_size, element_size, x, y)
#define UINT_ARRAY2(array, x, y)                                           ARRAY2(unsigned int, array, x, y)
#define UINT_P_ARRAY2(array, array_size, x_size, element_size, x, y)       ARRAY2_P(unsigned int, array, array_size, x_size, element_size, x, y)
#define LONG_ARRAY2(array, x, y)                                           ARRAY2(long, array, x, y)
#define LONG_P_ARRAY2(array, array_size, x_size, element_size, x, y)       ARRAY2_P(long, array, array_size, x_size, element_size, x, y)
#define ULONG_ARRAY2(array, x, y)                                          ARRAY2(unsigned long, array, x, y)
#define ULONG_P_ARRAY2(array, array_size, x_size, element_size, x, y)      ARRAY2_P(unsigned long, array, array_size, x_size, element_size, x, y)
#define FLOAT_ARRAY2(array, x, y)                                          ARRAY2(char, array, x, y)
#define FLOAT_P_ARRAY2(array, array_size, x_size, element_size, x, y)      ARRAY2_P(char, array, array_size, x_size, element_size, x, y)
#define DOUBLE_ARRAY2(array, x, y)                                         ARRAY2(char, array, x, y)
#define DOUBLE_P_ARRAY2(array, array_size, x_size, element_size, x, y)     ARRAY2_P(char, array, array_size, x_size, element_size, x, y)
#else
#define CHAR_ARRAY2(array, x, y)                                           (array[x][y])
#define CHAR_P_ARRAY2(array, array_size, x_size, element_size, x, y)       (array[x][y])
#define UCHAR_ARRAY2(array, x, y)                                          (array[x][y])
#define UCHAR_P_ARRAY2(array, array_size, x_size, element_size, x, y)      (array[x][y])
#define INT_ARRAY2(array, x, y)                                            (array[x][y])
#define INT_P_ARRAY2(array, array_size, x_size, element_size, x, y)        (array[x][y])
#define UINT_ARRAY2(array, x, y)                                           (array[x][y])
#define UINT_P_ARRAY2(array, array_size, x_size, element_size, x, y)       (array[x][y])
#define LONG_ARRAY2(array, x, y)                                           (array[x][y])
#define LONG_P_ARRAY2(array, array_size, x_size, element_size, x, y)       (array[x][y])
#define ULONG_ARRAY2(array, x, y)                                          (array[x][y])
#define ULONG_P_ARRAY2(array, array_size, x_size, element_size, x, y)      (array[x][y])
#define FLOAT_ARRAY2(array, x, y)                                          (array[x][y])
#define FLOAT_P_ARRAY2(array, array_size, x_size, element_size, x, y)      (array[x][y])
#define DOUBLE_ARRAY2(array, x, y)                                         (array[x][y])
#define DOUBLE_P_ARRAY2(array, array_size, x_size, element_size, x, y)     (array[x][y])
#endif

#if (DEBUG)
#define CHAR_ARRAY3(array, x, y, z)                                                     ARRAY3(char, array, x, y, z)
#define CHAR_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        ARRAY3_P(char, array, array_size, yz_size, y_size, element_size, x, y, z)
#define UCHAR_ARRAY3(array, x, y, z)                                                    ARRAY3(unsigned char, array, x, y, z)
#define UCHAR_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       ARRAY3_P(unsigned char, array, array_size, yz_size, y_size, element_size, x, y, z)
#define INT_ARRAY3(array, x, y, z)                                                      ARRAY3(int, array, x, y, z)
#define INT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)         ARRAY3_P(int, array, array_size, yz_size, y_size, element_size, x, y, z)
#define UINT_ARRAY3(array, x, y, z)                                                     ARRAY3(unsigned int, array, x, y, z)
#define UINT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        ARRAY3_P(unsigned int, array, array_size, yz_size, y_size, element_size, x, y, z)
#define LONG_ARRAY3(array, x, y, z)                                                     ARRAY3(long, array, x, y, z)
#define LONG_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        ARRAY3_P(long, array, array_size, yz_size, y_size, element_size, x, y, z)
#define ULONG_ARRAY3(array, x, y, z)                                                    ARRAY3(unsigned long, array, x, y, z)
#define ULONG_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       ARRAY3_P(unsigned long, array, array_size, yz_size, y_size, element_size, x, y, z)
#define FLOAT_ARRAY3(array, x, y, z)                                                    ARRAY3(char, array, x, y, z)
#define FLOAT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       ARRAY3_P(char, array, array_size, yz_size, y_size, element_size, x, y, z)
#define DOUBLE_ARRAY3(array, x, y, z)                                                   ARRAY3(char, array, x, y, z)
#define DOUBLE_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)      ARRAY3_P(char, array, array_size, yz_size, y_size, element_size, x, y, z)
#else
#define CHAR_ARRAY3(array, x, y, z)                                                     (array[x][y][z])
#define CHAR_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        (array[x][y][z])
#define UCHAR_ARRAY3(array, x, y, z)                                                    (array[x][y][z])
#define UCHAR_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       (array[x][y][z])
#define INT_ARRAY3(array, x, y, z)                                                      (array[x][y][z])
#define INT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)         (array[x][y][z])
#define UINT_ARRAY3(array, x, y, z)                                                     (array[x][y][z])
#define UINT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        (array[x][y][z])
#define LONG_ARRAY3(array, x, y, z)                                                     (array[x][y][z])
#define LONG_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)        (array[x][y][z])
#define ULONG_ARRAY3(array, x, y, z)                                                    (array[x][y][z])
#define ULONG_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       (array[x][y][z])
#define FLOAT_ARRAY3(array, x, y, z)                                                    (array[x][y][z])
#define FLOAT_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)       (array[x][y][z])
#define DOUBLE_ARRAY3(array, x, y, z)                                                   (array[x][y][z])
#define DOUBLE_P_ARRAY3(array, array_size, yz_size, y_size, element_size, x, y, z)      (array[x][y][z])
#endif
#endif
