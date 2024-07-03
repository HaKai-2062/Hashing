#include <iostream>

#include "sha0.hpp"
#include "sha1.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello World." << std::endl;

	std::string myString = "The quick brown fox jumps over the lazy dog";
	
	SHA0 sha0(myString);
	std::cout << sha0.GetHashValue() << std::endl;

	return 0;
}