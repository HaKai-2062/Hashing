#include <iostream>

#include "algorithm.hpp"

void Algorithm::Preprocess(uint32_t paddingSize, uint32_t bitSize)
{
	uint64_t messageBits = m_Data.size() * 8;

	m_Data.push_back(0b1000'0000);

	while ((m_Data.size() * 8) % paddingSize != (paddingSize - bitSize))
	{
		m_Data.push_back(0x00);
	}

	if (bitSize > 64)
	{
		// Append 64 bits of zero because 128 bit should be the total size
		for (int i = 0; i < 8; i++)
		{
			m_Data.push_back(0x00);
		}
	}

	// Account for big endian
	for (int i = 7; i >= 0; i--)
	{
		m_Data.push_back((messageBits >> (i * 8)) & 0xFF);
	}
}