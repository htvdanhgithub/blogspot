#include "CmdAbst.h"

CmdAbst::CmdAbst(View *pView)
{
	m_pView = pView;	
}
CmdAbst::~CmdAbst(void)
{
}

uint8_t CmdAbst::Execute(const uint8_t* msg)
{
	
}
uint8_t CmdAbst::Validate(const uint8_t* msg)
{
	
}