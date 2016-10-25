// Init:
//       _ _ _ _ _ _ _ _ _ _ _ _ _
//      |_|_|_|_|_|_|_|_|_|_|_|_|_|
// 	     ^ ^
//	 head   tail
// Normal:
//       _ _ _ _ _ _ _ _ _ _ _ _ _
//      |_|_|a|b|c|_|_|_|_|_|_|_|_|
// 	         ^     ^
//		   head   tail

#include "Logger.h"
#include "CyclicBuffer.h"

CyclicBuffer::CyclicBuffer(void)
{
}
CyclicBuffer::~CyclicBuffer(void)
{
}

//////////////Interface/////////////
void CyclicBuffer::SetMarks(const uint8_t *start, const uint8_t *end)
{
	memcpy(m_StartMarkBuf, start, CYCBUF_MARK_LEN);
	memcpy(m_EndMarkBuf, end, CYCBUF_MARK_LEN);
}
void CyclicBuffer::PushByte(uint8_t byte)
{
	LOG(CB_DEBUG, "push (%c)\r\n", byte);
	if(IsBufferOverFlow() == true)
	{
		LOG(CB_DEBUG, "IsBufferOverFlow\r\n");
		ResetBuffer();
	}
	
	if(m_HeadRel < CYCBUF_MARK_LEN)
	{
		m_Buf[GetIndex(m_HeadIndex + m_HeadRel)] = byte;
		
		if(byte == m_StartMarkBuf[m_HeadRel])
		{
			m_HeadRel++;
			m_TailIndex = GetIndex(m_HeadIndex + m_HeadRel);
			m_TailRel = 0;
		}
		else
		{
			MoveHead();
		}
	}
	else
	{
		if(m_TailRel < CYCBUF_MARK_LEN)
		{
			m_Buf[GetIndex(m_TailIndex + m_TailRel)] = byte;
			if(byte == m_EndMarkBuf[m_TailRel])
			{
				m_TailRel++;;
			}
			else
			{
				MoveTail();
			}
		}		
		else
		{
			// Match a msg
		}
		
	}
}
bool CyclicBuffer::GetMsg(uint8_t *output)
{
	if((m_HeadRel == CYCBUF_MARK_LEN) && (m_TailRel == CYCBUF_MARK_LEN))
	{
		LOG(CB_DEBUG, "###################################Msg matched\r\n");
		uint8_t index = 0;
		uint8_t temp;
		while(1)
		{
			temp = GetIndex(m_HeadIndex + CYCBUF_MARK_LEN + index);
			if(temp == m_TailIndex)
			{
				output[index] = 0;
				LOG(CB_DEBUG, "cb_get_cmd = %d, len = %d\r\n", true, index);
				LOG(CB_DEBUG, "output = %s, len = %d\r\n", output, index);
				ResetBuffer();
				return true;
			}
			output[index] = m_Buf[temp];
			index++;
		}
	}
	else
	{
		LOG(CB_DEBUG, "Msg not matched\r\n");
		return false;
	}
}
uint8_t CyclicBuffer::GetIndex(int index)
{
	return (index + CYCBUF_MAX_LEN)%CYCBUF_MAX_LEN;
}

uint8_t CyclicBuffer::GetNextIndex(uint8_t index)
{
	if(index == (CYCBUF_MAX_LEN - 1))
	{
		return 0;
	}
	return (index + 1);
}
void CyclicBuffer::ResetBuffer()
{
	memset(m_Buf, 0, CYCBUF_MAX_LEN + 1);
	LOG(CB_DEBUG, "ResetBuffer\r\n");
	m_HeadIndex = 0;
	m_TailIndex = 1;
	m_HeadRel = 0;
	m_TailRel = 0;	
}
void CyclicBuffer::MoveHead()
{
	m_HeadIndex = GetNextIndex(m_HeadIndex + m_HeadRel);
	m_TailIndex = GetNextIndex(m_HeadIndex);
	m_HeadRel = 0;
}
void CyclicBuffer::MoveTail()
{
	m_TailIndex = GetNextIndex(m_TailIndex + m_TailRel);
	m_TailRel = 0;
}
bool CyclicBuffer::IsBufferOverFlow()
{
	return (m_HeadIndex == m_TailIndex) ? true : false;
}
///////////////dump//////////////////
#ifdef DEBUG
void CyclicBuffer::Dump()
{
	LOG(CB_DEBUG, "<<<<<<<<<<<<<<<<<<<\r\n");
//	LOG(CB_DEBUG, "m_StartMarkBuf = %s\r\n", m_StartMarkBuf);
//	LOG(CB_DEBUG, "m_EndMarkBuf = %s\r\n", m_EndMarkBuf);
	
	LOG(CB_DEBUG, "m_Buf = %s\r\n", m_Buf);
	if(m_HeadRel == CYCBUF_MARK_LEN)
	{
		LOG(CB_DEBUG, "Head matched\r\n");
	}
	else
	{
		LOG(CB_DEBUG, "Head not matched\r\n");
	}
	LOG(CB_DEBUG, "m_HeadIndex = %s\r\n", &m_Buf[m_HeadIndex]);
	LOG(CB_DEBUG, "m_HeadIndex = %d\r\n", m_HeadIndex);
	LOG(CB_DEBUG, "m_HeadRel = %d\r\n", m_HeadRel);

	if(m_TailRel == CYCBUF_MARK_LEN)
	{
		LOG(CB_DEBUG, "Tail matched\r\n");
	}
	else
	{
		LOG(CB_DEBUG, "Tail not matched\r\n");
	}
	LOG(CB_DEBUG, "m_TailIndex = %d\r\n", m_TailIndex);
	LOG(CB_DEBUG, "m_TailRel = %d\r\n", m_TailRel);
	uint8_t output[CYCBUF_MAX_LEN + 1];
	memset(output, 0, CYCBUF_MAX_LEN + 1);
	GetMsg(output);
	LOG(CB_DEBUG, ">>>>>>>>>>>>>>>>>>>\r\n");
}
#endif