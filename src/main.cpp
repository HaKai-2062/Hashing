#include <iostream>
#include <string>

#include "sha0.hpp"
#include "sha1.hpp"
#include "sha256.hpp"
#include "sha224.hpp"
#include "sha512.hpp"
#include "sha384.hpp"

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

	// Discard cin buffer
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (true)
	{
		switch (choice)
		{
		case 1:
		{
			std::cout << "\nInput the string to hash: " << std::endl;

			std::string myString;
			std::getline(std::cin, myString);

			SHA0 hash0(myString);
			SHA1 hash1(myString);
			SHA256 hash256(myString);
			SHA224 hash224(myString);
			SHA512 hash512(myString);
			SHA384 hash384(myString);

			std::cout << "\nHashes: " << std::endl;
			std::cout << "SHA0: " << hash0.GetHashValue() << std::endl;
			std::cout << "SHA1: " << hash1.GetHashValue() << std::endl;
			std::cout << "SHA256: " << hash256.GetHashValue() << std::endl;
			std::cout << "SHA224: " << hash224.GetHashValue() << std::endl;
			std::cout << "SHA512: " << hash512.GetHashValue() << std::endl;
			std::cout << "SHA384: " << hash384.GetHashValue() << std::endl;
			break;
		}

		case 2:
		{
			std::cout << "This is HMAC" << std::endl;
			break;
		}

		default:
			break;
		}
	}


	return 0;
}