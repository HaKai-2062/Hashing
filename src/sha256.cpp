#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>

#include "sha256.hpp"

// https://en.wikipedia.org/wiki/SHA-2

std::string SHA256::GetHashValue(const std::string& data)
{
	m_Data = data;

	// Apply padding to get consistent chunks of 512 bytes of data
	Preprocess(512, 64);

	m_H0 = 0x6a09e667;
	m_H1 = 0xbb67ae85;
	m_H2 = 0x3c6ef372;
	m_H3 = 0xa54ff53a;
	m_H4 = 0x510e527f;
	m_H5 = 0x9b05688c;
	m_H6 = 0x1f83d9ab;
	m_H7 = 0x5be0cd19;

	size_t dataLength = m_Data.size();

	// Divide into 64-bytes chunks
	for (uint64_t i = 0; i < dataLength; i += 64)
	{
		uint32_t W[64] = { 0 };

		// 16 4-bytes
		for (uint8_t j = 0; j < 16; j++)
		{
			W[j] = 0;

			// 4-byte word
			for (uint8_t k = 0; k < 4; k++)
			{
				W[j] = (W[j] << 8) + static_cast<uint8_t>(m_Data[i + j * 4 + k]);
			}
		}

		// Message schedule: Extend 16 4-bytes into 80 4-bytes
		for (uint8_t k = 16; k < 64; k++)
		{
			uint32_t S0 = std::rotr(W[k - 15], 7) ^ std::rotr(W[k - 15], 18) ^ (W[k - 15] >> 3);
			uint32_t S1 = std::rotr(W[k - 2], 17) ^ std::rotr(W[k - 2], 19) ^ (W[k - 2] >> 10);
			W[k] = W[k - 16] + S0 + W[k - 7] + S1;
		}

		uint32_t a = m_H0;
		uint32_t b = m_H1;
		uint32_t c = m_H2;
		uint32_t d = m_H3;
		uint32_t e = m_H4;
		uint32_t f = m_H5;
		uint32_t g = m_H6;
		uint32_t h = m_H7;

		// Compression function
		for (uint8_t j = 0; j < 64; j++)
		{
			uint32_t S1 = std::rotr(e, 6) ^ std::rotr(e, 11) ^ std::rotr(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + S1 + ch + m_RoundConstant[j] + W[j];
			uint32_t S0 = std::rotr(a, 2) ^ std::rotr(a, 13) ^ std::rotr(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;

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
		m_H6 += g;
		m_H7 += h;
	}

	std::string result;

	auto appendBytes = [](std::string& str, uint32_t value)
		{
			str += static_cast<char>((value >> 24) & 0xFF);
			str += static_cast<char>((value >> 16) & 0xFF);
			str += static_cast<char>((value >> 8) & 0xFF);
			str += static_cast<char>(value & 0xFF);
		};

	appendBytes(result, m_H0);
	appendBytes(result, m_H1);
	appendBytes(result, m_H2);
	appendBytes(result, m_H3);
	appendBytes(result, m_H4);
	appendBytes(result, m_H5);
	appendBytes(result, m_H6);
	appendBytes(result, m_H7);

	return result;
}
