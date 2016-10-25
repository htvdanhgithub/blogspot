#ifndef CONTROLLER_H
#define CONTROLLER_H

#define C_DEBUG true

#include "..\Common\Common.h"
#include "..\View\View.h"
#include "..\Model\Model.h"

class Controller
{
	// Operations
	public:
		void Initiate(void);
		void Execute();
		
		Controller();   // This is the constructor declaration
		~Controller();  // This is the destructor: declaration	
	protected:
		void WaitAndProcessMsg();
		boolean HandleMsg(const char* senderNumber, const char* msg);
		int8_t GetSwPin(uint8_t pin);
		int ReadSerial(char* result);
		void ReportToMaster(const char* senderNumber, const char* msg);
	// Attributes
	protected:
		Model m_Model;
		View  m_View;
		char  m_MasterNumber[20];
};

#endif // CONTROLLER_H