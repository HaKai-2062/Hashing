#include <iostream>

#include "sha1.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello World." << std::endl;

	std::string myString = "In cryptography, SHA-1 (Secure Hash Algorithm 1) is a hash function which takes an input and produces a 160-bit (20-byte) hash value known as a message digest – typically rendered as 40 hexadecimal digits. It was designed by the United States National Security Agency, and is a U.S. Federal Information Processing Standard.[3] The algorithm has been cryptographically broken[4][5][6][7][8][9][10] but is still widely used. ";
		
	SHA1 sha1(myString);

	return 0;
}