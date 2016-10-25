#include "..\Utils\Logger.h"
#include "Controller.h"

#define START_MARK "<<<<"
#define END_MARK ">>>>"

Controller::Controller(void): m_Cmd(&m_View), m_MySerial(RX_PIN, TX_PIN)
{
}
Controller::~Controller(void)
{
}

void Controller::Initiate(void)
{
	Serial.begin(9600);

	m_MySerial.begin(9600);
	
	m_View.PinArrayMode(PIN_OUT_START, PIN_OUT_END, OUTPUT);
	m_View.PinHigh(PIN_OUT_START);
	m_View.PinHigh(PIN_OUT_END);
	m_Model.SetMarks((const uint8_t*)START_MARK, (const uint8_t*)END_MARK);
	
}

void Controller::Execute()
{
	uint8_t output[CYCBUF_MAX_LEN];
	if(m_MySerial.available())
	{
		m_View.PinHigh(PIN_RX);
		Serial.write(m_MySerial.read());
		// m_MySerial.read();
/*		m_Model.PushByte((uint8_t)m_MySerial.read());
		m_Model.GetMsg(output);
#ifdef DEBUG		
		m_Model.Dump();
#endif		
		m_Cmd.Execute(output);*/
		delay(10);
		m_View.PinLow(PIN_RX);
	}
	
/*	if (Serial.available())
	{
		m_View.PinHigh(PIN_TX);
		m_MySerial.write(Serial.read());
		delay(1);
		m_View.PinLow(PIN_TX);
	} */
	m_View.PinHigh(PIN_TX);
	m_MySerial.write("H\r\n");
	delay(10);
	m_View.PinLow(PIN_TX);
//	delay(1000);
	
}