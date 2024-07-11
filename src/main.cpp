#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <format>
#include <chrono>

#include "sha0.hpp"
#include "sha1.hpp"
#include "sha256.hpp"
#include "sha224.hpp"
#include "sha512.hpp"
#include "sha384.hpp"
#include "hmac.hpp"


namespace Utils
{
	std::string byteToHex(const std::string& str)
	{
		std::stringstream ss;
		ss << std::hex;
		for (unsigned char byte : str)
		{
			ss << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
		}

		return ss.str();
	}
}


int main(int argc, char** argv)
{
	uint32_t choice = 0;
	while (choice != 1 && choice != 2)
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif

		std::string input;
		std::cout << "Type 1 or 2\n1. Get HASH of a message\n2. Get HMAC of a message" << std::endl;
		std::cin >> input;
		
		choice = std::atoi(input.c_str());
	}

	// Clear cin buffer
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	const auto calculateTime = [&](std::chrono::microseconds previousTime)
		{
			std::chrono::microseconds currentTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
			auto deltaT = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;
			return deltaT.count();
		};

	while (true)
	{
		switch (choice)
		{
		case 1:
		{
			std::cout << "\nInput the string to hash: " << std::endl;

			std::string message;
			std::getline(std::cin, message);

			SHA0 hash0;
			SHA1 hash1;
			SHA256 hash256;
			SHA224 hash224;
			SHA512 hash512;
			SHA384 hash384;

			std::chrono::microseconds previousTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

			std::cout << "\nSHA0: " << Utils::byteToHex(hash0.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA1: " << Utils::byteToHex(hash1.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA256: " << Utils::byteToHex(hash256.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA224: " << Utils::byteToHex(hash224.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA512: " << Utils::byteToHex(hash512.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA384: " << Utils::byteToHex(hash384.GetHashValue(message)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			break;
		}

		case 2:
		{
			std::cout << "\nInput the string for HMAC: " << std::endl;
			std::string message;
			std::getline(std::cin, message);
			std::cout << "\nInput the key for HMAC: " << std::endl;
			std::string key;
			std::getline(std::cin, key);

			HMAC hmac;
			std::shared_ptr<SHA0> sha0 = std::make_shared<SHA0>();
			std::shared_ptr<SHA1> sha1 = std::make_shared<SHA1>();
			std::shared_ptr<SHA256> sha256 = std::make_shared<SHA256>();
			std::shared_ptr<SHA224> sha224 = std::make_shared<SHA224>();
			std::shared_ptr<SHA512> sha512 = std::make_shared<SHA512>();
			std::shared_ptr<SHA384> sha384 = std::make_shared<SHA384>();

			std::chrono::microseconds previousTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

			std::cout << "\nSHA0: " << Utils::byteToHex(hmac.GetHash(key, message, sha0, 64, 20)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA1: " << Utils::byteToHex(hmac.GetHash(key, message, sha1, 64, 20)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA256: " << Utils::byteToHex(hmac.GetHash(key, message, sha256, 64, 32)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA224: " << Utils::byteToHex(hmac.GetHash(key, message, sha224, 64, 28)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA512: " << Utils::byteToHex(hmac.GetHash(key, message, sha512, 128, 64)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			std::cout << "SHA384: " << Utils::byteToHex(hmac.GetHash(key, message, sha384, 128, 48)) << ", ";
			std::cout << "Time: " << calculateTime(previousTime) << " ms\n";
			break;
		}

		default:
			break;
		}
	}
	return 0;
}