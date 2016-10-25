#include "..\Utils\Logger.h"
#include "View.h"

View::View(void)
{
}
View::~View(void)
{
}

void View::PinMode(uint8_t pin, uint8_t mode)
{
	LOG(V_DEBUG, "INFO: PinMode (%d, %d)\r\n", pin, mode);	
	pinMode(pin, mode);
}
void View::PinArrayMode(uint8_t pin_from, uint8_t pin_to, uint8_t mode)
{
	for(uint8_t i = pin_from; i <= pin_to; i++)
	{
		PinMode(i, mode);
	}
}
void View::PinSet(uint8_t pin, uint8_t value)
{
	LOG(V_DEBUG, "INFO: PinSet (%d, %d)\r\n", pin, value);	
	digitalWrite(pin, value);
}
void View::PinHigh(uint8_t pin)
{
	PinSet(pin, HIGH);
}
void View::PinLow(uint8_t pin)
{
	PinSet(pin, LOW);
}
void View::PinArraySet(uint8_t pin_from, uint8_t pin_to, uint8_t value)
{
	for(uint8_t i = pin_from; i <= pin_to; i++)
	{
		PinSet(i, value);
	}
}
void View::PinArrayHigh(uint8_t pin_from, uint8_t pin_to)
{
	PinArraySet(pin_from, pin_to, HIGH);
}
void View::PinArrayLow(uint8_t pin_from, uint8_t pin_to)
{
	PinArraySet(pin_from, pin_to, LOW);
}
