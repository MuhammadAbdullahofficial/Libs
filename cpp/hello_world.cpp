#include <iostream>


int main(int argc, char* argv[]) {

	std::cout << "argc : " << argc << std::endl;
	std::cout << "argv : ";
	for (size_t i = 0; i < argc; i++)
		std::cout << argv[i] << ' ';

	std::cin.get();
	return 0;
}
