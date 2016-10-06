#if WINDOW_BASE
void mem_cpy(char* file, int line, void* dst, int dst_size, const void*  src, int src_size, int size)
{
    dbg_print2(DEBUG_ENABLE, "mem_cpy dst = %p, src = %p", dst, src);
    dbg_print3(DEBUG_ENABLE, "dst_size = %d, src_size = %d, size = %d", dst_size, src_size, size);
    if(dst == NULL)
    {
         dbg_print3(DEBUG_ENABLE, "%s:%d ERROR: NULL pointer (dst = %p)", file, line, dst);
         exit(-1);
    }     
    if(src == NULL)
    {
         dbg_print3(DEBUG_ENABLE, "%s:%d ERROR: NULL pointer (src = %p)", file, line, src);
         exit(-1);
    }     
    if(size > src_size)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: size(%d) > src_size(%d)", file, line, size, src_size);
         exit(-1);
    }            
    if(size > dst_size)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: size(%d) > dst_size(%d)", file, line, size, dst_size);
         exit(-1);
    }            
    memcpy((uint8_t*)dst, (uint8_t*)src, size);
}
void mem_set(char* file, int line, void* dst, int size_dst, int value, int size)
{
    dbg_print1(DEBUG_DISABLE, "mem_set dst = %p", dst);
    dbg_print2(DEBUG_DISABLE, "size_dst = %d, size = %d", size_dst, size);
    if(dst == NULL)
    {
         dbg_print3(DEBUG_ENABLE, "%s:%d ERROR: NULL pointer (dst = %p)", file, line, dst);
         exit(-1);
    }     
    if(size > size_dst)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: size(%d) > size_dst(%d)", file, line, size, size_dst);
         exit(-1);
    }            
    memset((uint8_t*)dst, value, size);
}
#define MEMCPY(dst, src, size) mem_cpy(__FILE__, __LINE__, dst, sizeof(*dst), src, sizeof(*src), size)
#define MEMSET(dst, value, size) mem_set(__FILE__, __LINE__, dst, sizeof(*dst), value, size)
#define MEMCPY_ARRAY(dst, src, size) mem_cpy(__FILE__, __LINE__, dst, sizeof(dst), src, sizeof(src), size)
#define MEMSET_ARRAY(dst, value, size) mem_set(__FILE__, __LINE__, dst, sizeof(dst), value, size)
#else
#define MEMCPY(dst, src, size) memcpy(dst, src, size)
#define MEMSET(dst, value, size) memset(dst, value, size)
#define MEMCPY_ARRAY(dst, src, size) memcpy(dst, src, size)
#define MEMSET_ARRAY(dst, value, size) memset(dst, value, size)
#endif
