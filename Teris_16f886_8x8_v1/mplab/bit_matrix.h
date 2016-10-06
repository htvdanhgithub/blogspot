/*
This file contains functions to get/set bit matrix' element.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
void set_matrix_bit(uint8_t *byte, uint8_t row, uint8_t col, uint8_t value)
{
	setbit(&byte[row], col, value);
}
uint8_t get_matrix_bit(const uint8_t *byte, uint8_t row, uint8_t col)
{
	return getbit(&byte[row], col);
}
