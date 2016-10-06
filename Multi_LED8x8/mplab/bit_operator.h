#ifndef BIT_OPERATOR_H
#define BIT_OPERATOR_H

typedef struct
{
    uint8_t b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} t_byte;
void setbit(uint8_t *byte, uint8_t at, uint8_t value)
{
	t_byte *temp = (t_byte *)byte;
	switch(at)
	{
	case 0:
		temp->b0 = value;
		break;
	case 1:
		temp->b1 = value;
		break;
	case 2:
		temp->b2 = value;
		break;
	case 3:
		temp->b3 = value;
		break;
	case 4:
		temp->b4 = value;
		break;
	case 5:
		temp->b5 = value;
		break;
	case 6:
		temp->b6 = value;
		break;
	case 7:
		temp->b7 = value;
		break;
	}
}
uint8_t getbit(const uint8_t *byte, uint8_t at)
{
	t_byte *temp = (t_byte *)byte;
	switch(at)
	{
	case 0:
		return (uint8_t)temp->b0;
		break;
	case 1:
		return (uint8_t)temp->b1;
		break;
	case 2:
		return (uint8_t)temp->b2;
		break;
	case 3:
		return (uint8_t)temp->b3;
		break;
	case 4:
		return (uint8_t)temp->b4;
		break;
	case 5:
		return (uint8_t)temp->b5;
		break;
	case 6:
		return (uint8_t)temp->b6;
		break;
	case 7:
		return (uint8_t)temp->b7;
		break;
	}
}
uint8_t reverse(uint8_t byte)
{
	t_byte *temp = (t_byte *)&byte;
	t_byte res;

    res.b0 = temp->b7;
    res.b1 = temp->b6;
    res.b2 = temp->b5;
    res.b3 = temp->b4;
    res.b4 = temp->b3;
    res.b5 = temp->b2;
    res.b6 = temp->b1;
    res.b7 = temp->b0;
    
    return *((uint8_t *)&res);
}
#endif // BIT_OPERATOR_H