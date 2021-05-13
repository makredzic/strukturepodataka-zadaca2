#include <iostream>
#include <stdexcept>
#include "PostfixCalc.hpp"

int main() {

	PostfixCalc calculator;


	std::cout << "----Postfix Calculator-----\n";
	std::cout << "(Supported operators: +,-,*,/)\n";
	std::cout << "\nCalculate below:\n";

	
	char* input = new char[1024];

		while	(true) {
			
			try {
				std::cin >> input;
				if(calculator.input(input)) 
					std::cout << "Result: " << calculator.result() << std::endl;

			} catch (const std::invalid_argument& e) {
				std::cout << "\nMake sure to have at least 2 numbers typed in. Try again:\n";
			}
		}

	delete [] input;

	return 0;
}
