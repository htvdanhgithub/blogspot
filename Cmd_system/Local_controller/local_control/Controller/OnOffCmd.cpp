#include "OnOffCmd.h"

OnOffCmd::OnOffCmd(View *pView): CmdAbst(pView)
{
}
OnOffCmd::~OnOffCmd(void)
{
}

uint8_t OnOffCmd::Execute(const uint8_t* msg)
{
	LOG(OOCMD_DEBUG, "INFO: OnOffCmd::Execute (%s)\r\n", msg);
	
	uint8_t ret = CMD_OK;
	ret = Validate(msg);
	
	if(ret != CMD_OK)
	{
		return ret;
	}
	
	OnOffCmd_t cmd;
	cmd.cmd_index = msg[0];
	cmd.port = atoi((const char*)msg + 1);
	
	LOG(OOCMD_DEBUG, "INFO: cmd.cmd_index (%c)\r\n", cmd.cmd_index);
	LOG(OOCMD_DEBUG, "INFO: cmd.port (%d)\r\n", cmd.port);

	uint8_t value;
	switch(cmd.cmd_index) // cmd index
	{
		case 'M':
			value = HIGH;
		break;
		case 'T':
			value = LOW;
		break;
		default:
			LOG(OOCMD_DEBUG, "ERROR: invalid cmd index (%c)\r\n", cmd.cmd_index);
			return CMD_INVALID_INDEX;
			break;		
	}
	if((cmd.port < PIN_OUT_START) || (cmd.port > PIN_OUT_END))
	{
		LOG(OOCMD_DEBUG, "ERROR: invalid cmd pin (%d)\r\n", cmd.port);
		return CMD_INVALID_PIN;
	}

	m_pView->PinSet(cmd.port, value);
	return ret;		
}

uint8_t OnOffCmd::Validate(const uint8_t* msg)
{
	if(msg == NULL)
	{
		LOG(OOCMD_DEBUG, "ERROR: invalid cmd (0x%p)\r\n", msg);
		return CMD_INVALID;
	}

	uint8_t len = strlen((const char*)msg);
	if((len < 2) || (len > 3)) 
	{
		LOG(OOCMD_DEBUG, "ERROR: invalid cmd len (%s)\r\n", msg);
		return CMD_INVALID_LEN;
	}
	
	for(uint8_t i = 1; i < len; i++)
	{
		if(isdigit(msg[i]) == false)
		{
			LOG(OOCMD_DEBUG, "ERROR: invalid cmd format, data are not total digits (%s)\r\n", msg);
			return CMD_INVALID_DATA_FORMAT;
		}
	}
	return CMD_OK;	
}
