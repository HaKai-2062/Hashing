#pragma once

#include "algorithm.hpp"

class SHA0 : public Algorithm
{
public:
	SHA0(const std::string& data);
	std::string GetHashValue() const;

private:
	SHA0() = delete;
	SHA0(const SHA0&) = delete;
	SHA0(const SHA0&&) = delete;
	void operator=(const SHA0&) = delete;

private:
	uint32_t m_H0 = 0x67452301;
	uint32_t m_H1 = 0xEFCDAB89;
	uint32_t m_H2 = 0x98BADCFE;
	uint32_t m_H3 = 0x10325476;
	uint32_t m_H4 = 0xC3D2E1F0;
};