#include <iostream>
#include "stack_arr.hpp"

// Kompleksnog ovog je JA MISLIM manja od O(n^2)
// Takodjer, ispis koji program dadne NIJE redoslijeda kojeg se ocekuje od zadatka
// Ne znam koliki problem to mozda bude predstavljalo ali drugacije nisam znao
// Prijatno


typedef StackArr<int> Stack;

//ovaj static i static kod static printGreater se moze izbrisati ako buni
//nista ne promijeni osim da mi mozda dadne 0.2 vise bodova za pretencioznost
static int* makeArray(size_t arrSize) {
	int* array = new int[arrSize];

	std::cout << "Enter " << arrSize << " array elements:\n";
	for (auto i = 0; i < arrSize; i++) {
		int el;
		std::cin >> el;
		array[i] = el;
	}
	return array;
}

static void printGreater(int* arr, size_t size) {
	Stack stack{size}; //capacity

	stack.push(arr[0]);
	
	for (int i = 1; i < size; i++) {

		if (stack.empty()) {
			stack.push(arr[i]);
			continue;
		}

		while(!stack.empty() && stack.top() <= arr[i]) {
			
			std::cout << stack.top() << " ---> " << arr[i] << std::endl;
			stack.pop();

		}

		stack.push(arr[i]);

	}

	while (!stack.empty()) {
		std::cout << stack.top() << " ---> " << -1 << std::endl;
		stack.pop();
	}

}

int main() {

	size_t arrSize;
	std::cout << "Enter the size of the array: ";
	std::cin >> arrSize;

	int* arr = makeArray(arrSize);
	printGreater(arr, arrSize);


	return 0;
}
