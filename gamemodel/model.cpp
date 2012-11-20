#include <iostream>
#include <string>

#include "utils/count.h"

int main(int argc, char **argv) {
	count<std::string> ct(5);
	std::cout << ct.how_many << std::endl;
	std::cout << "test";// count <std::string> ct(5);
	return 0;
}

