#pragma once

#include "algorithm.hpp"

class SHA1 : public Algorithm
{
public:
	SHA1() = default;
	virtual std::string GetHashValue(const std::string& data);

private:
	SHA1(const SHA1&) = delete;
	SHA1(const SHA1&&) = delete;
	void operator=(const SHA1&) = delete;

private:
	uint32_t m_H0 = 0x67452301;
	uint32_t m_H1 = 0xEFCDAB89;
	uint32_t m_H2 = 0x98BADCFE;
	uint32_t m_H3 = 0x10325476;
	uint32_t m_H4 = 0xC3D2E1F0;
};