#include <iostream>

int main(int argc, char* argv[], char* envp[]) {

	std::cout << "argc : " << argc;

	std::cout << "\nargv : ";
	for (size_t i = 0; i < argc; i++)
		std::cout << argv[i] << ' ';

	std::cout << "\nenvp : ";
	for (size_t i = 0; envp[i] != NULL; i++)
		std::cout << envp[i] << '\n';

	std::cin.get();
	return 0;
}
