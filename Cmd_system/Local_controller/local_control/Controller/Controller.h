#ifndef CONTROLLER_H
#define CONTROLLER_H

#define C_DEBUG true

#include "..\Common\Common.h"
#include <SoftwareSerial.h>
#include "..\View\View.h"
#include "..\Model\Model.h"
#include "Cmd.h"

class Controller
{
	// Operations
	public:
		void Initiate(void);
		void Execute();
		
		Controller();   // This is the constructor declaration
		~Controller();  // This is the destructor: declaration	
	// Attributes
	protected:
		Model m_Model;
		View  m_View;
		Cmd   m_Cmd;
		SoftwareSerial m_MySerial; // RX, TX
};

#endif // CONTROLLER_H