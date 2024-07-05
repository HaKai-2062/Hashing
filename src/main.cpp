#include <iostream>

#include "sha0.hpp"
#include "sha1.hpp"
#include "sha256.hpp"
#include "sha224.hpp"
#include "sha512.hpp"
#include "sha384.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello World." << std::endl;

	std::string myString = "The quick brown fox jumps over the lazy dog";
	
	SHA384 hash(myString);
	std::cout << hash.GetHashValue() << std::endl;

	return 0;
}