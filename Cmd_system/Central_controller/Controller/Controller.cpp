#include "..\Utils\Logger.h"
#include "Controller.h"

#define START_MARK "<<<<"
#define END_MARK ">>>>"

Controller::Controller(void)
{
	m_MasterNumber[0] = 0;
}
Controller::~Controller(void)
{
}

void Controller::Initiate(void)
{
	m_View.Initiate();
	LOG(C_DEBUG, "<<<<Start...>>>>\r\n");
	m_View.PinArrayMode(PIN_OUT_START, PIN_OUT_END, OUTPUT);
	m_View.PinArraySet(PIN_OUT_START, PIN_OUT_END, LOW);
#if !(UNITTEST)
	m_View.GSMConnect();
#endif	
	m_View.PinHigh(PIN_GSM_CONNECTED);
}
int8_t Controller::GetSwPin(uint8_t pin)
{
	switch(pin)
	{
		case 1:
			return PIN_SWITCH1;
			break;
		case 2:
			return PIN_SWITCH2;
			break;
		case 3:
			return PIN_SWITCH3;
			break;
		case 4:
			return PIN_SWITCH4;
			break;
		default:
			return -1;
			break;
	}
}
void Controller::ReportToMaster(const char* senderNumber, const char* m_SMSRecv)
{
	char  m_SMSSend[256];
	
	if((m_MasterNumber[0] != 0) && (strcmp(senderNumber, m_MasterNumber) != 0))
	{
		sprintf(m_SMSSend, "From %s: %s\r\n", senderNumber, m_SMSRecv);
		LOG(C_DEBUG, "m_SMSSend: %s\r\n", m_SMSSend);
		m_View.SMSSend(m_MasterNumber, m_SMSSend);
	}
	
}
boolean Controller::HandleMsg(const char* senderNumber, const char* m_SMSRecv)
{
	char  m_SMSSend[256];
	
	boolean ret = true;

	uint8_t on = HIGH;
	int8_t pin = 1;
	
	if(m_SMSRecv[0] != '#')
	{
		goto __wrong_format;
	}

	switch(m_SMSRecv[1])
	{
		case 'M':
			if(strlen(m_SMSRecv) > 3)
			{
				goto __wrong_format;
			}
			on = true;
		break;
		case 'T':
			if(strlen(m_SMSRecv) > 3)
			{
				goto __wrong_format;
			}
			on = LOW;
		break;
		case 'R':
			sprintf(m_MasterNumber, "+84%s", m_SMSRecv + 3);
			LOG(C_DEBUG, "MasterNumber: %s\r\n", m_MasterNumber);
			sprintf(m_SMSSend, "Set report number to %s\r\n", m_MasterNumber);
			goto __exit;
		break;
		default:
			goto __wrong_format;
		break;
	}

	if((!isdigit(m_SMSRecv[2])) || (m_SMSRecv[2] < '1') || (m_SMSRecv[2] > '4'))
	{
		goto __wrong_format;
	}
	pin = GetSwPin(m_SMSRecv[2] - '0');
	
	sprintf(m_SMSSend, "%d duoc %s\r\n", pin, (on == HIGH) ? "MO" : "TAT");
	m_View.PinSet(pin, on);
	goto __exit;
	
__wrong_format:
	LOG(C_DEBUG, "Wrong format\r\n");

	strcpy(m_SMSSend, "Yeu cau khong hop le. Vui long gui lai.\r\n");
	ret = false;
__exit:
		
	LOG(C_DEBUG, "Exit\r\n");
	LOG(C_DEBUG, "senderNumber: %s\r\n", senderNumber);
	LOG(C_DEBUG, "m_SMSSend: %s\r\n", m_SMSSend);
	m_View.SMSSend(senderNumber, m_SMSSend);

	ReportToMaster(senderNumber, m_SMSRecv);
	return ret;
}
int Controller::ReadSerial(char* result) 
{
	int i = 0;
	while (1) 
	{
		while (Serial.available() > 0) 
		{
			char inChar = Serial.read();
			if (inChar == '\n') 
			{
				result[i] = '\0';
				Serial.flush();
				LOG(C_DEBUG, "Message received: %s\r\n", result);
				return 0;
			}
			if (inChar != '\r') 
			{
				result[i] = inChar;
				i++;
			}
		}
	}
}
void Controller::WaitAndProcessMsg()
{
	char  m_SMSRecv[256];
	
	char c;
	char senderNumber[20];
#if !(UNITTEST)	
	// If there are any SMSs available()
	if (m_View.SMSAvailable()) 
	{
		// Get remote number
		m_View.SMSGetRemoteNumber(senderNumber, 20);
		LOG(C_DEBUG, "Message received from: %s\r\n", senderNumber);

		m_View.SMSGetMsg(m_SMSRecv);
		
		LOG(C_DEBUG, "END OF MESSAGE\r\n");

		// Delete message from modem memory
		m_View.SMSFlush();
		
		LOG(C_DEBUG, "MESSAGE DELETED\r\n");

		HandleMsg(senderNumber, m_SMSRecv);
	}
#else
		m_View.PinHigh(PIN_SMS_RECV);
		// Get remote number
		strcpy(senderNumber, "+84907710730");
		LOG(C_DEBUG, "Message received from: %s\r\n", senderNumber);
		ReadSerial(m_SMSRecv);
		LOG(C_DEBUG, "END OF MESSAGE\r\n");

		LOG(C_DEBUG, "MESSAGE DELETED\r\n");

		m_View.PinLow(PIN_SMS_RECV);
		HandleMsg(senderNumber, m_SMSRecv);
#endif	
}

void Controller::Execute()
{
	WaitAndProcessMsg();
	delay(1000);
	
}