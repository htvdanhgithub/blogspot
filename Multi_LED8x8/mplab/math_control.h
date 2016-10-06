#ifndef MATH_CONTROL_H
#define MATH_CONTROL_H

#if WINDOW_BASE
int div_int(char* file, int line, int x, int y)
{
    dbg_print2(DEBUG_DISABLE, "div_int x = %d, y = %d", x, y);
    if(y == 0)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: divide by ZERO (x = %d, y = %d)", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
int mod_int(char* file, int line, int x, int y)
{
    dbg_print2(DEBUG_DISABLE, "mod_int x = %d, y = %d", x, y);
    if(y == 0)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: modulo by ZERO (x = %d, y = %d)", file, line, x, y);
         exit(-1);
    }     
    return x%y;
}
float div_float(char* file, int line, float x, float y)
{
    dbg_print2(DEBUG_DISABLE, "div_float x = %f, y = %f", x, y);
    if(y == (float)0.0)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: divide by ZERO (x = %f, y = %f)", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
double div_double(char* file, int line, double x, double y)
{
    dbg_print2(DEBUG_DISABLE, "div_double x = %f, y = %f", x, y);
    if(y == (double)0.0)
    {
         dbg_print4(DEBUG_ENABLE, "%s:%d ERROR: divide by ZERO (x = %f, y = %f)", file, line, x, y);
         exit(-1);
    }     
    return x/y;
}
#define DIV_INT(x, y) div_int(__FILE__, __LINE__, x, y)
#define MOD_INT(x, y) mod_int(__FILE__, __LINE__, x, y)
#define DIV_FLOAT(x, y) div_float(__FILE__, __LINE__, x, y)
#define DIV_DOUBLE(x, y) div_double(__FILE__, __LINE__, x, y)
#else
#define DIV_INT(x, y) x/y
#define MOD_INT(x, y) x%y
#define DIV_FLOAT(x, y) x/y
#define DIV_DOUBLE(x, y) x/y
#endif
#endif // MATH_CONTROL_H