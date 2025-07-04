#include <iostream>

int add(int a, int b) {
	return a + b;
}

int main() {
	std::cout << "hello world!" << std::endl;
	
	std::cout << "please enter a number" << std::endl;
	
	int a = 0;
	std::cin >> a;

	std::cout << "please enter another number" << std::endl;

	int b = 0;
	std::cin >> b;
	
	std::cout << "the sum of these two numbers is " << add(a,b) << std::endl;
	
	return 0;
}
