#include "LRU.h"
#include<iostream>
#include<string>

int main() {

	lru::memory<int, 3> intMem; // can store up to 3 memories of int plus high and low

	std::cout << "current: ";
	for (auto itr = intMem.begin(); itr != intMem.end(); --itr) { // empty so does nothing
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	intMem.remember(3); // remember 3 and look for high and low
	std::cout << "high and low: " << intMem.get_high() << " " << intMem.get_low() << std::endl;
	intMem.remember(4); // remember 4

	for (auto itr = intMem.begin(), end = intMem.end(); itr != end; --itr) { // print all the numbers
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	// remember two more numbers, will forget the 3
	intMem.remember(27);
	intMem.remember(37);

	std::cout << "print all the numbers: ";
	for (auto itr = intMem.begin(); itr != intMem.end(); --itr) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	// forget the most distant (4)
	intMem.forget();
	std::cout << "After a forget: ";
	for (auto itr = intMem.begin(); itr != intMem.end(); --itr) { // print all the numbers
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	std::cout << "recall highs and lows: " << intMem.get_high() << " " << intMem.get_low() << std::endl;

	auto intMem2 = intMem; // copy constructor
	std::cout << "element count: " << intMem2.size() << std::endl;
	auto intMem3 = std::move(intMem); // move constructor
	std::cout << "element count: " << intMem3.size() << std::endl;
	intMem = intMem3; // assignment operator
	std::cout << "element count: " << intMem.size() << std::endl;

	lru::memory<std::string, 2, bool(*)(const std::string&, const std::string&)> stringMem(length_comp);

	stringMem.emplace(); // emtpy string added
	stringMem.remember("hey");
	stringMem.remember("howdy");
	stringMem.remember("salutations");
	stringMem.remember("greetings");
	stringMem.forget(); // now only stores "greetings"
	stringMem.emplace(4, '$'); // also stores "$$$$"

	std::cout << "printout of strings: ";
	print(stringMem); // prints the memory
	std::cout << std::endl;

	std::cout << "size of a string: ";
	auto itr = stringMem.begin();
	std::cout << itr->size() << std::endl;
	std::cout << "highs and lows of the strings (lowest is empty): " << stringMem.get_high() << " " << stringMem.get_low() << std::endl;

	std::cin.get();


	return 0;
}