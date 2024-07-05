#include <iostream>

#include "sha0.hpp"
#include "sha1.hpp"
#include "sha256.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello World." << std::endl;

	std::string myString = "The quick brown fox jumps over the lazy dog";
	
	SHA256 sha256(myString);
	std::cout << sha256.GetHashValue() << std::endl;

	return 0;
}