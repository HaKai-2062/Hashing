#include <memory>
#include <string>

#include "hmac.hpp"
#include "algorithm.hpp"

std::string computeBlockSizedKey(const std::string& key, std::shared_ptr<Algorithm> hash, uint64_t& blockSize, uint64_t outputSize);

std::string HMAC::GetHash(const std::string& key, const std::string& message, std::shared_ptr<Algorithm> hash, uint64_t blockSize, uint64_t outputSize)
{
	std::string blockSizedKey = computeBlockSizedKey(key, hash, blockSize, outputSize);

	std::string outerKeyPad(blockSize, 0x5c);
	std::string innerKeyPad(blockSize, 0x36);
	
	for (uint64_t i = 0; i < blockSize; i++)
	{
		outerKeyPad[i] ^= blockSizedKey[i];
		innerKeyPad[i] ^= blockSizedKey[i];
	}

	std::string innerData = innerKeyPad + message;
	std::string innerHash = hash->GetHashValue(innerData);

	std::string outerData = outerKeyPad + innerHash;
	std::string finalHash = hash->GetHashValue(outerData);
	
	return finalHash;
}

std::string computeBlockSizedKey(const std::string& key, std::shared_ptr<Algorithm> hash, uint64_t& blockSize, uint64_t outputSize)
{
	std::string paddedKey;
	if (key.size() > blockSize)
	{
		paddedKey = hash->GetHashValue(key);
		if (paddedKey.size() > blockSize)
		{
			paddedKey.resize(blockSize);
		}
	}
	else
	{
		paddedKey = key;
	}

	paddedKey.resize(blockSize, 0x00);
	return paddedKey;
}
