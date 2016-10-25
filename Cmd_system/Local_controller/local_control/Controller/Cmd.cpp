#include "Cmd.h"
#include "OnOffCmd.h"


Cmd::Cmd(View *pView): CmdAbst(pView)
{

}
Cmd::~Cmd(void)
{
}

uint8_t Cmd::Execute(const uint8_t* msg)
{
	uint8_t ret = CMD_OK;
	ret = Validate(msg);
	
	if(ret != CMD_OK)
	{
		return ret;
	}

	msg += strlen((const char*)msg)/2;
	if(msg[0] == ON_OFF_CMD_TYPE)
	{
		OnOffCmd cmd(m_pView);
		return cmd.Execute(msg + 1);
	}
	else
	{
		LOG(CMD_DEBUG, "ERROR: invalid cmd type (%c)\r\n", msg[0]);
		return CMD_INVALID_TYPE;
	}

	return ret;	
}
uint8_t Cmd::Validate(const uint8_t* msg)
{
	if(msg == NULL)
	{
		LOG(CMD_DEBUG, "ERROR: invalid cmd (0x%p)\r\n", msg);
		return CMD_INVALID;
	}
	uint8_t len = strlen((const char*)msg);
	if(len%2 == 1) // len = 0
	{
		LOG(CMD_DEBUG, "ERROR: invalid cmd len == 0\r\n");
		return CMD_INVALID_LEN;
	}
	len /=2;
	for(uint8_t i = 0; i < len; i++)
	{
		if(msg[i] != msg[i + len])
		{
			LOG(CMD_DEBUG, "ERROR: invalid cmd crc(%s)\r\n", msg);
			return CMD_INVALID_CRC;
		}
	}
	return CMD_OK;
}
