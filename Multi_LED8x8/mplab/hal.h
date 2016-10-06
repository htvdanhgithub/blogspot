/*
This file contains abstract hardware layer.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
#ifndef HAL_H
#define HAL_H

#if WINDOW_BASE
#include "hal_window.h"
#else
#include "hal_max7219.h"
#endif

#endif //HAL_H
