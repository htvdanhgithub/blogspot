#ifndef CYCLICBUFFER_H
#define CYCLICBUFFER_H

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
#include "..\Common\Common.h"

#define CB_DEBUG true

#define CYCBUF_MAX_LEN    15
#define CYCBUF_MARK_LEN    4

class CyclicBuffer
{
	// Operations
	public:
		void SetMarks(const uint8_t *start, const uint8_t *end);
		void PushByte(uint8_t byte);
		bool GetMsg(uint8_t *output);
#ifdef DEBUG
		void Dump();
#endif
		CyclicBuffer();   // This is the constructor declaration
		~CyclicBuffer();  // This is the destructor: declaration		
	protected:
		uint8_t GetIndex(int index);
		uint8_t GetNextIndex(uint8_t index);
		void ResetBuffer();
		void MoveHead();
		void MoveTail();
		bool IsBufferOverFlow();
		
	// Attributes
	protected:
		uint8_t m_HeadIndex = 0;
		uint8_t m_TailIndex = 1;
		uint8_t m_HeadRel = 0;
		uint8_t m_TailRel = 0;

		uint8_t m_StartMarkBuf[CYCBUF_MARK_LEN + 1];
		uint8_t m_EndMarkBuf[CYCBUF_MARK_LEN + 1];

		uint8_t m_Buf[CYCBUF_MAX_LEN + 1];
	
};

#endif // CYCLICBUFFER_H