#pragma once

class Algorithm;

class HMAC
{
public:
	HMAC() = default;
	std::string GetHash(const std::string& key, const std::string& message, std::shared_ptr<Algorithm> hash, uint64_t blockSize, uint64_t outputSize);

private:
	std::shared_ptr<Algorithm> algorithms;
};