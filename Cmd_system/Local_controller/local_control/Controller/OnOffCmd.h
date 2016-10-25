#ifndef ONOFFCMD_H
#define ONOFFCMD_H

#include "CmdAbst.h"

#define OOCMD_DEBUG true

#define OOCMD_DATA_MAX_LEN 2
typedef struct
{
	char cmd_index;
	uint8_t port;
} OnOffCmd_t;

class OnOffCmd: public CmdAbst
{
	// Operations
	public:
		uint8_t Execute(const uint8_t* msg);
		OnOffCmd(View *pView);   // This is the constructor declaration
		~OnOffCmd();  // This is the destructor: declaration	
	protected:
		uint8_t Validate(const uint8_t* msg);
	
	// Attributes
};
#endif // ONOFFCMD_H