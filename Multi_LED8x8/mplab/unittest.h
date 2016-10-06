#ifndef UNITTEST_H
#define UNITTEST_H

typedef uint8_t (*UNITTEST_F)(void);

typedef struct
{
    char* test_name;
    UNITTEST_F f;            
} UNITTEST_SUITE;
//////////////Start adding unitestcase here/////////////
uint8_t Testcase1(void)
{
    return OK;        
}        
uint8_t Testcase2(void)
{
    return OK;        
}        
UNITTEST_SUITE g_unitest[] = 
{
    {"Testcase1", Testcase1},               
    {"Testcase2", Testcase2},               
};                      
//////////////End adding unitestcase here/////////////
void testsuite_run()
{
    printf("<<<<<<<<<<<<<<<<<testsuite_run\n");              
    int len = sizeof(g_unitest)/sizeof(g_unitest[0]);
    uint8_t res;
    uint8_t passed = 0;;
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
