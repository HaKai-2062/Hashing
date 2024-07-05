#include <iostream>

#include "algorithm.hpp"

void Algorithm::Preprocess(uint32_t paddingSize)
{
	uint64_t messageBits = m_Data.size() * 8;

	m_Data.push_back(0b1000'0000);

	while ((m_Data.size() * 8) % paddingSize != (paddingSize - 64))
	{
		m_Data.push_back(0x00);
	}

	// Account for big endian
	for (int i = 7; i >= 0; i--)
	{
		m_Data.push_back((messageBits >> (i * 8)) & 0xFF);
	}
}