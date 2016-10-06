#ifndef BIT_MATRIX_H
#define BIT_MATRIX_H

void set_matrix_bit(uint8_t *byte, uint8_t row, uint8_t col, uint8_t value)
{
	setbit(&byte[row], col, value);
}
uint8_t get_matrix_bit(const uint8_t *byte, uint8_t row, uint8_t col)
{
	return getbit(&byte[row], col);
}
#endif // BIT_MATRIX_H