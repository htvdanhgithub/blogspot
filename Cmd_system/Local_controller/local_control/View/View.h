#ifndef VIEW_H
#define VIEW_H

#define V_DEBUG true

#include "..\Common\Common.h"

#define PIN_OUT_START 	4
#define PIN_OUT_END 	19

#define RX_PIN 3
#define TX_PIN 2

#define PIN_TX 	10
#define PIN_RX 	11

class View
{
	// Operations
	public:
		void PinMode(uint8_t pin, uint8_t mode);
		void PinArrayMode(uint8_t pin_from, uint8_t pin_to, uint8_t mode);
		void PinSet(uint8_t pin, uint8_t value);
		void PinHigh(uint8_t pin);
		void PinLow(uint8_t pin);
		void PinArraySet(uint8_t pin_from, uint8_t pin_to, uint8_t value);
		void PinArrayHigh(uint8_t pin_from, uint8_t pin_to);
		void PinArrayLow(uint8_t pin_from, uint8_t pin_to);
		
		View();   // This is the constructor declaration
		~View();  // This is the destructor: declaration	
	// Attributes
};
#endif // VIEW_H

