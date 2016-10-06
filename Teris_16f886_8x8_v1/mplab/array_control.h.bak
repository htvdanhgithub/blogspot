#if WINDOW_BASE
void* array1_at(char* file, int line, void * array, int size, int element_size, int x)
{
    dbg_print2(DEBUG_DISABLE, "array1_at size = %d, element_size = %d", size, element_size);
    dbg_print2(DEBUG_DISABLE, "x = %d, max_x = %d", x, size/element_size);
    if((x < 0) || (x >= size/element_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (x = %d, max_x = %d)", file, line, x, size/element_size);
         exit(-1);
    }     
    dbg_print1(DEBUG_DISABLE, "index = %d", x*element_size);
    return ((uint8_t*)array + x*element_size);
}

void* array2_at(char* file, int line, void * array, int size, int x_max_size, int element_size, int x, int y)
{
    dbg_print3(DEBUG_DISABLE, "array2_at size = %d, x_max_size = %d, element_size = %d", size, x_max_size, element_size);
    dbg_print2(DEBUG_DISABLE, "x = %d, max_x = %d", x, size/x_max_size);
    dbg_print2(DEBUG_DISABLE, "y = %d, max_y = %d", y, x_max_size/element_size);

    if((x < 0) || (x >= size/x_max_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (x = %d, max_x = %d)", file, line, x, size/x_max_size);
         exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/element_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (y = %d, max_y = %d)", file, line, y, x_max_size/element_size);
         exit(-1);
    }     
    dbg_print1(DEBUG_DISABLE, "index = %d", x*x_max_size + y*element_size);
    return ((uint8_t*)array + x*x_max_size + y*element_size);
}

void* array3_at(char* file, int line, void * array, int size, int x_max_size, int y_max_size, int element_size, int x, int y, int z)
{
    dbg_print4(DEBUG_DISABLE, "array3_at size = %d, x_max_size = %d, y_max_size = %d, element_size = %d", size, x_max_size, y_max_size, element_size);
    dbg_print2(DEBUG_DISABLE, "x = %d, max_x = %d", x, size/x_max_size);
    dbg_print2(DEBUG_DISABLE, "y = %d, max_y = %d", y, x_max_size/y_max_size);
    dbg_print2(DEBUG_DISABLE, "z = %d, max_z = %d", z, y_max_size/element_size);
    if((x < 0) || (x >= size/x_max_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (x = %d, max_x = %d)", file, line, x, size/x_max_size);
         exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/y_max_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (y = %d, max_y = %d)", file, line, y, x_max_size/y_max_size);
         exit(-1);
    }     
    if((z < 0) || (z >= y_max_size/element_size))
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: out of bound (z = %d, max_z = %d)", file, line, z, y_max_size/element_size);
         exit(-1);
    }     

    dbg_print1(DEBUG_DISABLE, "index = %d", x*x_max_size + y*y_max_size + z*element_size);
    return ((uint8_t*)array + x*x_max_size + y*y_max_size + z*element_size);
}
#define ARRAY1(TYPE, array, x) (*((TYPE*)array1_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), x)))
#define ARRAY2(TYPE, array, x, y) (*((TYPE*)array2_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), x, y)))
#define ARRAY3(TYPE, array, x, y, z) (*((TYPE*)array3_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), sizeof(array[0][0][0]), x, y, z)))
#endif
