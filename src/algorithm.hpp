#pragma once

class Algorithm
{
public:
	virtual std::string GetHashValue(const std::string& data) = 0;

protected:
	Algorithm() = default;
	virtual ~Algorithm() = default;
	void Preprocess(uint32_t paddingSize, uint32_t bitSize);

private:
	Algorithm(const Algorithm&) = delete;
	Algorithm(const Algorithm&&) = delete;
	void operator=(const Algorithm&) = delete;

protected:
	std::string m_Data;
};