/*
This file contains some utilities to detect NULL pointer and buffer overflow in memcpy, memset, strcpy.
How to use: http://htvdanh.blogspot.com/2016/09/proposed-solution-to-detect-null.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 6th, 2016
*/

#ifndef MEM_VALIDATE_H
#define MEM_VALIDATE_H

#include <stdint.h>
FILE *fp;

#if DEBUG
void mem_cpy(char* file, int line, void* dst, int dst_size, const void*  src, int src_size, int size)
{
//    fprintf(fp, "mem_cpy dst = 0x%p, src = 0x%p\n", dst, src);
//    fprintf(fp, "dst_size = %d, src_size = %d, size = %d\n", dst_size, src_size, size);
    if(dst == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (dst = 0x%p)\n", file, line, dst);
         exit(-1);
    }     
    if(src == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (src = 0x%p)\n", file, line, src);
         exit(-1);
    }     
    if(size > src_size)
    {
         fprintf(fp, "%s:%d ERROR: buffer overflow (size(%d) > src_size(%d))\n", file, line, size, src_size);
         exit(-1);
    }            
    if(size > dst_size)
    {
         fprintf(fp, "%s:%d ERROR: buffer overflow (size(%d) > dst_size(%d))\n", file, line, size, dst_size);
         exit(-1);
    }            
    memcpy((uint8_t*)dst, (uint8_t*)src, size);
}
void mem_set(char* file, int line, void* dst, int size_dst, int value, int size)
{
//    fprintf(fp, "mem_set dst = 0x%p\n", dst);
//    fprintf(fp, "size_dst = %d, size = %d\n", size_dst, size);
    if(dst == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (dst = 0x%p)\n", file, line, dst);
         exit(-1);
    }     
    if(size > size_dst)
    {
         fprintf(fp, "%s:%d ERROR: buffer overflow (size(%d) > size_dst(%d))\n", file, line, size, size_dst);
         exit(-1);
    }            
    memset((uint8_t*)dst, value, size);
}
void str_cpy(char* file, int line, char* dst, int dst_size, const char*  src, int src_size)
{
//    fprintf(fp, "str_cpy dst = 0x%p, src = 0x%p\n", dst, src);
    if(dst == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (dst = 0x%p)\n", file, line, dst);
         exit(-1);
    }     
    if(src == NULL)
    {
         fprintf(fp, "%s:%d ERROR: NULL pointer (src = 0x%p)\n", file, line, src);
         exit(-1);
    }     
    int size = strlen(src);

//    fprintf(fp, "dst_size = %d, src_size = %d, size = %d\n", dst_size, src_size, size);

    if(size + 1 > src_size)
    {
         fprintf(fp, "%s:%d ERROR: buffer overflow (size(%d) > src_size(%d))\n", file, line, size + 1, src_size);
         exit(-1);
    }            
    if(size + 1 > dst_size)
    {
         fprintf(fp, "%s:%d ERROR: buffer overflow (size(%d) > dst_size(%d))\n", file, line, size + 1, dst_size);
         exit(-1);
    }            
    strcpy(dst, src);
}
#define MEMCPY(dst, size_dst, src, size_src, size)       mem_cpy(__FILE__, __LINE__, dst, size_dst, src, size_src, size)
#define MEMSET(dst, size_dst, value, size)               mem_set(__FILE__, __LINE__, dst, size_dst, value, size)
#define STRCPY(dst, size_dst, src, size_src)             str_cpy(__FILE__, __LINE__, dst, size_dst, src, size_src)
#define MEMCPY_ARRAY(dst, src, size)                     mem_cpy(__FILE__, __LINE__, dst, sizeof(dst), src, sizeof(src), size)
#define MEMSET_ARRAY(dst, value, size)                   mem_set(__FILE__, __LINE__, dst, sizeof(dst), value, size)
#define STRCPY_ARRAY(dst, src)                           str_cpy(__FILE__, __LINE__, dst, sizeof(dst), src, sizeof(src))
#else
#define MEMCPY(dst, size_dst, src, size_src, size)       memcpy(dst, src, size)
#define MEMSET(dst, size_dst, value, size)               memset(dst, value, size)
#define STRCPY(dst, size_dst, src, size_src, size)       strcpy(dst, src)
#define MEMCPY_ARRAY(dst, src, size)                     memcpy(dst, src, size)
#define MEMSET_ARRAY(dst, value, size)                   memset(dst, value, size)
#define STRCPY_ARRAY(dst, src)                           strcpy(dst, src)
#endif
#endif
