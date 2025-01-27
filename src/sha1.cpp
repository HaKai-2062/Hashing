#include <iostream>
#include <sstream>
#include <iomanip>
#include <format>

#include "sha1.hpp"

// https://en.wikipedia.org/wiki/SHA-1

std::string SHA1::GetHashValue(const std::string& data)
{
	m_Data = data;

	// Apply padding to get consistent chunks of 512 bytes of data
	Preprocess(512, 64);
	
	m_H0 = 0x67452301;
	m_H1 = 0xEFCDAB89;
	m_H2 = 0x98BADCFE;
	m_H3 = 0x10325476;
	m_H4 = 0xC3D2E1F0;

	size_t dataLength = m_Data.size();

	uint32_t W[80] = { 0 };

	// Divide into 64-bytes chunks
	for (uint64_t i = 0; i < dataLength; i+=64)
	{
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
		for (uint8_t k = 16; k < 80; k++)
		{
			W[k] = std::rotl(W[k - 3] ^ W[k - 8] ^ W[k - 14] ^ W[k - 16], 1);
		}

		uint32_t a = m_H0;
		uint32_t b = m_H1;
		uint32_t c = m_H2;
		uint32_t d = m_H3;
		uint32_t e = m_H4;
	
		for (uint8_t j = 0; j < 80; j++)
		{
			uint32_t f = 0;
			uint32_t k = 0;

			if (j < 20)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (j < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (j < 60)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = (std::rotl(a, 5) + f + e + k + W[j]);
			e = d;
			d = c;
			c = std::rotl(b, 30);
			b = a;
			a = temp;
		}

		m_H0 += a;
		m_H1 += b;
		m_H2 += c;
		m_H3 += d;
		m_H4 += e;
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

	return result;
}
