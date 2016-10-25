#ifndef CMD_ABST_H
#define CMD_ABST_H

#include "..\Common\Common.h"
#include "..\Utils\Logger.h"
#include "..\View\View.h"

#define CMDABST_DEBUG true

typedef enum
{
	CMD_OK = 0,
	CMD_INVALID,
	CMD_INVALID_CRC,
	CMD_INVALID_LEN,
	CMD_INVALID_TYPE,
	CMD_INVALID_INDEX,
	CMD_INVALID_DATA_LEN,
	CMD_INVALID_DATA_FORMAT,
	CMD_INVALID_PIN,
} CMD_ERROR_t;

class CmdAbst
{
	// Operations
	public:
		virtual uint8_t Execute(const uint8_t* msg);
		CmdAbst(View *pView);   // This is the constructor declaration
		~CmdAbst();  // This is the destructor: declaration	
	protected:
		virtual uint8_t Validate(const uint8_t* msg);
	
	// Attributes
	protected:
	View *m_pView;
};
#endif // CMD_ABST_H