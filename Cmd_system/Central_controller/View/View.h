#ifndef VIEW_H
#define VIEW_H

#define V_DEBUG true

#include <GSM.h>
#include "..\Common\Common.h"

#define PIN_OUT_START 		4
#define PIN_OUT_END 		19
#define PIN_GSM_CONNECTED 	PIN_OUT_START
#define PIN_SMS_SEND		(PIN_OUT_START + 1)
#define PIN_SMS_RECV		(PIN_OUT_START + 2)

#define PIN_SWITCH1 		8
#define PIN_SWITCH2 		9
#define PIN_SWITCH3 		10
#define PIN_SWITCH4 		11

#define PIN_MAX_NUM 		4

// PIN Number for the SIM
#define PINNUMBER ""

class View
{
	// Operations
	public:
		void Initiate(void);
		void GSMConnect();
		boolean SMSAvailable();
		int  SMSGetMsg(char* result);
		void SMSGetRemoteNumber(char *senderNumber, uint8_t len);
		void SMSSend(const char* remoteNum, const char *txtMsg);
		void SMSFlush();
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
	protected:
		GSM m_GsmAccess;
		GSM_SMS m_Sms;

};
#endif // VIEW_H

