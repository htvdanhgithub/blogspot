#include "..\Utils\Logger.h"
#include "Model.h"

Model::Model(void)
{
}
Model::~Model(void)
{
}

void Model::SetMarks(const uint8_t *start, const uint8_t *end)
{
	m_CyclicBuffer.SetMarks(start, end);
}
void Model::PushByte(uint8_t byte)
{
	m_CyclicBuffer.PushByte(byte);
}
bool Model::GetMsg(uint8_t *output)
{
	return m_CyclicBuffer.GetMsg(output);
}
#ifdef DEBUG
void Model::Dump()
{
	m_CyclicBuffer.Dump();
}
#endif
