/*
This file contains light weight unit-test framework for C, especillay useful for embedded projects.
How to use: http://htvdanh.blogspot.com/2016/09/light-weight-unit-test-framework-for-cc.html
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 9th, 2016
*/
#ifndef UNITTEST_H
#define UNITTEST_H

#define UT_PASSED 0
#define UT_FAILED 1

#define UT_ASSERT(a, b) \
{ \
    if(a == b) \
    { \
         return UT_PASSED; \
    } \
    return UT_FAILED; \
}        
typedef uint8_t (*UT_F)(void);

typedef struct
{
    char* test_name;
    UT_F f;            
} UT_SUITE;
//////////////Start adding unitestcase here/////////////
const char* get_greeting();

uint8_t ut_testcase1(void)
{
    UT_ASSERT(0, strcmp(get_greeting(), "Hi"));        
}        
uint8_t ut_testcase2(void)
{
    UT_ASSERT(0, strcmp(get_greeting(), "Hello"));        
}        

UT_SUITE g_unitest[] = 
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
        if(res == UT_PASSED)
        {
            passed++;
        }       
        printf("%s is %s\n", g_unitest[i].test_name, (res == UT_PASSED) ? "PASSED" : "FAILED");              
    }             
    printf("--------\n");              
    printf("%d/%d testcases PASSED\n", passed, len);              
    printf(">>>>>>>>>>>>>>>>>testsuite_run\n");              
}     

#endif
