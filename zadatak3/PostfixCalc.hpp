#pragma once
#include "stack_arr.hpp"
#include <exception>
#include <stdexcept>
#include <cstdlib>

class PostfixCalc {
	private:
		const char operators[4] = {'+', '-', '*', '/'};
		StackArr<int> stack;

		bool isOperator(char i) {
			for (int j = 0; j < 4; j++) if (operators[j] == i) return true;
			return false;
		};

	public:
		PostfixCalc() = default;
		PostfixCalc(const PostfixCalc&) = delete;
		PostfixCalc(PostfixCalc&&) = delete;

		bool input(char* i) {

			int number = std::atoi(i); // pretvori niz karaktera u int reprezentaciju, npr "546" postane 546 int

			if (!isOperator(*i)) { 

				if (number == 0 && *i != '0') { // std::atoi od karaktera vraca int 0 tako da ako je on 0 a unos u terminal NIJE bio 0 znaci da je invalidan karakter unesen
					std::cout << "Invalid operator." << std::endl;
				} else stack.push(number); 

				return false; 
			}

			if (stack.empty()) throw std::invalid_argument("You must provide at least 2 operands first.");
			
			int a = stack.top();
			stack.pop();

			if (stack.empty()) throw std::invalid_argument("You must provide at least 2 operands first.");

			int b = stack.top();
			stack.pop();

			int c;
			switch(*i) {
				case 43: c =b+a;
					break;

				case 45: c = b-a;
					break;

				case 42: c = a*b;
					break;

				case 47: c = b/a;
					break;
			}
	
			stack.push(c);
			return true;

		}

		int result() {return stack.top();}

};
