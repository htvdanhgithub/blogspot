/*
This file contains abstract hardware layer.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#if WINDOW_BASE
#include "hal_window.h"
#else
#include "hal_max7219.h"
#endif

void hal_print_Screen()
{
	hal_print_MATRIX8x8(&g_matrix8x8);
}
