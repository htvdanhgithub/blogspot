#ifndef UNITTEST_H
#define UNITTEST_H

typedef uint8_t (*UNITTEST_F)(void);

typedef struct
{
    char* test_name;
    UNITTEST_F f;            
} UNITTEST_SUITE;
//////////////Start adding unitestcase here/////////////
uint8_t ut_testcase1(void)
{
    return OK;        
}        
uint8_t ut_testcase2(void)
{
    return OK;        
}        
void ut_lg_is_row_full(const MATRIX16x8* matrix)
{
    for(uint8_t row = 0; row < MATRIX16x8_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, lg_is_row_full(matrix, row) == 0 ? "not full" : "full");
    }
}
void ut_hit_land()
{
    int8_t x = 5, y = 6;
    MATRIX4x4* matrix4x4 = lg_get_MATRIX4x4(1, 0);
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    dbg_print_MATRIX4x4(DEBUG_DISABLE, NULL, x, y, matrix4x4);
    dbg_print_MATRIX16x8(DEBUG_DISABLE, NULL, &matrix16x8);
    lg_hit_land(x, y, matrix4x4, &matrix16x8);
}
void ut_is_valid()
{
    int8_t x = 5, y = 7;
    MATRIX4x4* matrix4x4 = lg_get_MATRIX4x4(1, 0);
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    dbg_print_MATRIX4x4(DEBUG_DISABLE, NULL, x, y, matrix4x4);
    dbg_print_MATRIX16x8(DEBUG_DISABLE, NULL, &matrix16x8);
    lg_is_valid(x, y, matrix4x4, &matrix16x8);
}
void ut_find_best_solution()
{
    g_char_info_index = 1;
    lg_find_best_solution();
}
void ut_get_holes_after_merge()
{
    MATRIX16x8 matrix16x8 =
    {
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
    };
    dbg_print_MATRIX16x8(DEBUG_DISABLE, NULL, &matrix16x8);
    lg_get_holes_after_merge(&matrix16x8);
}

UNITTEST_SUITE g_unitest[] = 
{
    {"Testcase1", ut_testcase1},               
    {"Testcase2", ut_testcase2},               
};                      
//////////////End adding unitestcase here/////////////
void ut_testsuite_run()
{
    printf("<<<<<<<<<<<<<<<<<testsuite_run\n");              
    int len = sizeof(g_unitest)/sizeof(g_unitest[0]);
    uint8_t res;
    uint8_t passed = 0;
    for(int i = 0; i < len; i++)
    {
        res = g_unitest[i].f();
        if(res == OK)
        {
            passed++;
        }       
        printf("%s is %s\n", g_unitest[i].test_name, (res == OK) ? "PASSED" : "FAILED");              
    }             
    printf("--------\n");              
    printf("%d/%d testcases PASSED\n", passed, len);              
    printf(">>>>>>>>>>>>>>>>>testsuite_run\n");              
}     

#endif // UNITTEST_H