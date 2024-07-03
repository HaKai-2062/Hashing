#include <iostream>

#include "sha1.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello World." << std::endl;

	std::string myString = "The quick brown fox jumps over the lazy cog";
	
	SHA1 sha1(myString);
	std::cout << sha1.GetHashValue() << std::endl;

	return 0;
}