#include <sstream>
#include <iomanip>
#include <format>

#include "sha1.hpp"

// https://en.wikipedia.org/wiki/SHA-1

SHA1::SHA1(const std::string& data)
{
	m_Data = std::move(data);

	// Apply padding to get consistent chunks of 512 bytes of data
	Preprocess(512);
	
	size_t dataLength = m_Data.size();

	auto leftRotate = [](uint32_t x, uint32_t n)
		{
			return (x << n) | (x >> (32 - n));
		};

	// Divide into 64-bytes chunks
	for (size_t i = 0; i < dataLength; i+=64)
	{
		uint32_t W[80*4];

		// First 16 bytes copied
		for (uint8_t j = 0; j < 16; ++j)
		{
			size_t index = i + j * 4;
			W[j] = (m_Data[index] << 24) |
				(m_Data[index + 1] << 16) |
				(m_Data[index + 2] << 8) |
				(m_Data[index + 3]);
		}

		// Message schedule: Extend 16 4-bytes into 80 4-bytes
		for (uint8_t j = 16; j < 80; j++)
		{
			if (j < 32)
			{
				W[j] = leftRotate(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
			}
			else
			{
				W[j] = leftRotate(W[j - 6] ^ W[j - 16] ^ W[j - 28] ^ W[j - 32], 2);
			}
		}

		uint32_t a = m_H0;
		uint32_t b = m_H1;
		uint32_t c = m_H2;
		uint32_t d = m_H3;
		uint32_t e = m_H4;
	
		for (uint8_t j = 0, f = 0, k = 0; j < 80; j++)
		{
			if (j >= 0 && j <= 19)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (j >= 20 && j <= 39)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (j >= 40 && j <= 59)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else if (j >= 60 && j <= 79)
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = (leftRotate(a, 5) + f + e + k + W[j]);
			e = d;
			d = c;
			c = leftRotate(b, 30);
			b = a;
			a = temp;
		}

		m_H0 += a;
		m_H1 += b;
		m_H2 += c;
		m_H3 += d;
		m_H4 += e;
	}
}

std::string SHA1::GetHashValue() const
{
	std::stringstream ss;
	ss << std::hex;

	ss << std::setw(8) << std::setfill('0') << m_H0;
	ss << std::setw(8) << std::setfill('0') << m_H1;
	ss << std::setw(8) << std::setfill('0') << m_H2;
	ss << std::setw(8) << std::setfill('0') << m_H3;
	ss << std::setw(8) << std::setfill('0') << m_H4;

	return ss.str();
}