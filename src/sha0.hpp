#pragma once

#include "algorithm.hpp"

class SHA0 : public Algorithm
{
public:
	SHA0() = default;
	virtual std::string GetHashValue(const std::string& data);

private:
	SHA0(const SHA0&) = delete;
	SHA0(const SHA0&&) = delete;
	void operator=(const SHA0&) = delete;
	virtual void PureVirtualFunction() {}

private:
	uint32_t m_H0 = 0x67452301;
	uint32_t m_H1 = 0xEFCDAB89;
	uint32_t m_H2 = 0x98BADCFE;
	uint32_t m_H3 = 0x10325476;
	uint32_t m_H4 = 0xC3D2E1F0;
};