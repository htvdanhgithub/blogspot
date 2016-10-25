#ifndef CMD_H
#define CMD_H

#include "CmdAbst.h"

#define CMD_DEBUG true

#define ON_OFF_CMD_TYPE '1'

class Cmd: public CmdAbst
{
	// Operations
	public:
		uint8_t Execute(const uint8_t* msg);
		Cmd(View *pView);   // This is the constructor declaration
		~Cmd();  // This is the destructor: declaration	
	protected:
		uint8_t Validate(const uint8_t* msg);
	
	// Attributes
};

#endif // CMD_H