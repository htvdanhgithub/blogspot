#include <cstdlib>
#include <iostream>

void* array1_at(char* file, int line, void * array, int size, int element_size, int x)
{
    printf("array1_at size = %d, element_size = %d\n", size, element_size);      
    printf("x = %d, max_x = %d\n", x, size/element_size);      
    if((x < 0) || (x >= size/element_size))
    {
         printf("%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/element_size);
         //exit(-1);
    }     
    printf("index = %d\n", x*element_size);      
    return ((uint8_t*)array + x*element_size);
}

void* array2_at(char* file, int line, void * array, int size, int x_max_size, int element_size, int x, int y)
{
    printf("array2_at size = %d, x_max_size = %d, element_size = %d\n", size, x_max_size, element_size);      
    printf("x = %d, max_x = %d\n", x, size/x_max_size);      
    printf("y = %d, max_y = %d\n", y, x_max_size/element_size);      

    if((x < 0) || (x >= size/x_max_size))
    {
         printf("%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/x_max_size);
         //exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/element_size))
    {
         printf("%s:%d ERROR: out of bound (y = %d, max_y = %d)\n", file, line, y, x_max_size/element_size);
         //exit(-1);
    }     
    printf("index = %d\n", x*x_max_size + y*element_size);      
    return ((uint8_t*)array + x*x_max_size + y*element_size);
}

void* array3_at(char* file, int line, void * array, int size, int x_max_size, int y_max_size, int element_size, int x, int y, int z)
{
    printf("array3_at size = %d, x_max_size = %d, y_max_size = %d, element_size = %d\n", size, x_max_size, y_max_size, element_size);      
    printf("x = %d, max_x = %d\n", x, size/x_max_size);      
    printf("y = %d, max_y = %d\n", y, x_max_size/y_max_size);      
    printf("z = %d, max_z = %d\n", z, y_max_size/element_size);      
    if((x < 0) || (x >= size/x_max_size))
    {
         printf("%s:%d ERROR: out of bound (x = %d, max_x = %d)\n", file, line, x, size/x_max_size);
         //exit(-1);
    }     
    if((y < 0) || (y >= x_max_size/y_max_size))
    {
         printf("%s:%d ERROR: out of bound (y = %d, max_y = %d)\n", file, line, y, x_max_size/y_max_size);
         //exit(-1);
    }     
    if((z < 0) || (z >= y_max_size/element_size))
    {
         printf("%s:%d ERROR: out of bound (z = %d, max_z = %d)\n", file, line, z, y_max_size/element_size);
         //exit(-1);
    }     

    printf("index = %d\n", x*x_max_size + y*y_max_size + z*element_size);      
    return ((uint8_t*)array + x*x_max_size + y*y_max_size + z*element_size);
}
#define ARRAY1(TYPE, array, x) *((TYPE*)array1_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), x))
#define ARRAY2(TYPE, array, x, y) *((TYPE*)array2_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), x, y))
#define ARRAY3(TYPE, array, x, y, z) *((TYPE*)array3_at(__FILE__, __LINE__, array, sizeof(array), sizeof(array[0]), sizeof(array[0][0]), sizeof(array[0][0][0]), x, y, z))

int g_array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int g_array2[4][5] = 
{
1,   2,  3,  4,  5, 
6,   7,  8,  9, 10, 
11, 12, 13, 14, 15, 
16, 17, 18, 19, 20
};
int g_array3[2][4][5] = 
{
1,   2,  3,  4,  5, 
6,   7,  8,  9, 10, 
11, 12, 13, 14, 15, 
16, 17, 18, 19, 20,

21, 22, 23, 24, 25, 
26, 27, 28, 29, 30, 
31, 32, 33, 34, 35, 
36, 37, 38, 39, 40
};
#define DEBUG 1
#if(DEBUG)        
#define g_array1(x) ARRAY1(int, g_array1, x)
#define G_ARRAY2(x, y) ARRAY2(int, g_array2, x, y)
#define G_ARRAY3(x, y, z) ARRAY3(int, g_array3, x, y, z)
#else
#define G_ARRAY1(x) g_array1[x]
#define G_ARRAY2(x, y) g_array2[x][y]
#define G_ARRAY3(x, y, z) g_array3[x][y][z]
#endif

using namespace std;

int main(int argc, char *argv[])
{
    printf("value1 = %d\n", g_array1(10));
    printf("value2 = %d\n", G_ARRAY2(3, 4));
    printf("value3 = %d\n", G_ARRAY3(1, 3, 4));
    system("PAUSE");
    return EXIT_SUCCESS;
}
