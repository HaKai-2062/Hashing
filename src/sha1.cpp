#include <iostream>

#include "sha1.hpp"

SHA1::SHA1(const std::string& data)
{
	m_Data = std::move(data);

	// Apply padding to get consistent chunks of 512 bytes of data
	Preprocess(512);
	
	size_t dataLength = m_Data.size();
}