#ifndef MODEL_H
#define MODEL_H
#include "..\Common\Common.h"
#include "..\Utils\CyclicBuffer.h"

class Model
{
	// Operations
	public:
		void SetMarks(const uint8_t *start, const uint8_t *end);
		void PushByte(uint8_t byte);
		bool GetMsg(uint8_t *output);
#ifdef DEBUG
		void Dump();
#endif
		
		Model();   // This is the constructor declaration
		~Model();  // This is the destructor: declaration	
	// Attributes
	protected:
		CyclicBuffer m_CyclicBuffer;
};

#endif // MODEL_H