#pragma once

class Algorithm
{
protected:
	Algorithm() = default;
	~Algorithm() = default;
	void Preprocess(uint32_t paddingSize, uint32_t bitSize);

private:
	Algorithm(const Algorithm&) = delete;
	Algorithm(const Algorithm&&) = delete;
	void operator=(const Algorithm&) = delete;

protected:
	std::string m_Data;
};