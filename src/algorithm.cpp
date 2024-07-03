#include <iostream>

#include "algorithm.hpp"

void Algorithm::Preprocess(uint32_t paddingSize)
{
	size_t messageBits = m_Data.size() * 8;
	// 64 bit is size of our left over data and 8 bit because 0x80 added
	uint32_t zeroBitsToAdd = (paddingSize - 64 - (messageBits + 8) % paddingSize) % paddingSize;

	uint32_t totalBytesToAdd = zeroBitsToAdd / 8;
	
	m_Data.push_back(0b1000'0000);

	for (uint32_t i = 0; i < totalBytesToAdd; i++)
	{
		m_Data.push_back(0x00);
	}

	for (uint32_t i = 0; i < 8; i++)
	{
		uint8_t byte = (totalBytesToAdd >> (i * 8)) & 0xFF;
		m_Data.push_back(byte);
	}
}