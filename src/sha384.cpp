#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>

#include "sha384.hpp"

// https://en.wikipedia.org/wiki/SHA-2

SHA384::SHA384(const std::string& data)
{
	m_Data = std::move(data);

	// Apply padding to get consistent chunks of 512 bytes of data
	Preprocess(1024, 128);

	size_t dataLength = m_Data.size();

	// Divide into 64-bytes chunks
	for (uint64_t i = 0; i < dataLength; i += 128)
	{
		uint64_t W[80] = { 0 };

		// 8 16-bytes
		for (uint8_t j = 0; j < 16; j++)
		{
			W[j] = 0;

			// 8-byte word
			for (uint8_t k = 0; k < 8; k++)
			{
				W[j] = (W[j] << 8) + static_cast<uint8_t>(m_Data[i * 64 + j * 8 + k]);
			}
		}

		// Message schedule: Extend 16 4-bytes into 80 4-bytes
		for (uint8_t k = 16; k < 80; k++)
		{
			uint64_t S0 = std::rotr(W[k - 15], 1) ^ std::rotr(W[k - 15], 8) ^ (W[k - 15] >> 7);
			uint64_t S1 = std::rotr(W[k - 2], 19) ^ std::rotr(W[k - 2], 61) ^ (W[k - 2] >> 6);
			W[k] = W[k - 16] + S0 + W[k - 7] + S1;
		}

		uint64_t a = m_H0;
		uint64_t b = m_H1;
		uint64_t c = m_H2;
		uint64_t d = m_H3;
		uint64_t e = m_H4;
		uint64_t f = m_H5;
		uint64_t g = m_H6;
		uint64_t h = m_H7;

		// Compression function
		for (uint8_t j = 0; j < 80; j++)
		{
			uint64_t S1 = std::rotr(e, 14) ^ std::rotr(e, 18) ^ std::rotr(e, 41);
			uint64_t ch = (e & f) ^ ((~e) & g);
			uint64_t temp1 = h + S1 + ch + m_RoundConstant[j] + W[j];
			uint64_t S0 = std::rotr(a, 28) ^ std::rotr(a, 34) ^ std::rotr(a, 39);
			uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint64_t temp2 = S0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		m_H0 += a;
		m_H1 += b;
		m_H2 += c;
		m_H3 += d;
		m_H4 += e;
		m_H5 += f;
		//m_H6 += g;
		//m_H7 += h;
	}
}

std::string SHA384::GetHashValue() const
{
	std::stringstream ss;
	ss << std::hex;

	ss << std::setw(16) << std::setfill('0') << m_H0;
	ss << std::setw(16) << std::setfill('0') << m_H1;
	ss << std::setw(16) << std::setfill('0') << m_H2;
	ss << std::setw(16) << std::setfill('0') << m_H3;
	ss << std::setw(16) << std::setfill('0') << m_H4;
	ss << std::setw(16) << std::setfill('0') << m_H5;
	//ss << std::setw(16) << std::setfill('0') << m_H6;
	//ss << std::setw(16) << std::setfill('0') << m_H7;

	return ss.str();
}