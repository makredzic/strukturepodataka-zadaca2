#include "stack_arr.hpp"
#include "stack_interface.h"
#include "stack_linked.hpp"


template<typename T>
static void printDim(const StackArr<T>& s) {
	std::cout << "Capacity: " << s.capacity() << std::endl;
	std::cout << "Size: " << s.size() << std::endl;
}

template <typename T>
static void fillNumeric(stack_interface<T>* const stack) {
	for (T i = 0; i < 50; i+=3) stack->push(i);
}


int main() {

	StackArr<int> stackArr;
	StackLinked<int> stackLinked;

	fillNumeric(&stackArr);
	fillNumeric(&stackLinked);

	std::cout << "Top Elements\n";
	std::cout << "Arr: " << stackArr.top() << std::endl;
	std::cout << "Linked: " << stackLinked.top() << std::endl;

	std::cout << "\nAll the elements\n";
	std::cout << "Arr: " << stackArr;
	std::cout << "Linked: " << stackLinked;

	stackArr.push(1);
	stackArr.push(3);
	stackArr.push(5);
	stackArr.push(7);
	
	stackLinked.push(1);
	stackLinked.push(3);
	stackLinked.push(5);
	stackLinked.push(7);

	std::cout << "\nStack Copy\n";
	StackArr<int> stackArrCpy{stackArr};
	StackLinked<int> stackLinkedCpy{stackLinked};
	std::cout << "Arr: " << stackArrCpy;	
	std::cout << "Linked: " << stackLinkedCpy;	

	StackArr<double> test1;
	StackLinked<double> test2;
	
	fillNumeric(&test1);
	fillNumeric(&test2);

	std::cout<< "\nMoved Stack\n";
	auto arr{std::move(test1)};
	auto linked{std::move(test2)};

	std::cout << "Arr: " << arr;
	std::cout << "Linked: "	<< linked;

	std::cout << "Empty moved stacks"<<std::endl;
	std::cout << "Arr: " << arr;	
	std::cout << "Linked: " << arr;	

	stackArr = StackArr<int>{};
	fillNumeric(&stackArr);

	stackLinked = StackLinked<int>{};
	fillNumeric(&stackLinked);

	StackArr<int> a;
	StackLinked<int> b;

	a = stackArr;
	b = std::move(stackLinked);
	StackLinked<int> b1;
	b1.push(55);

	if (a == stackArr) std::cout << "\na == stackArr" << std::endl;
	if (b != b1) std::cout << "b != stackLinked" << std::endl;
	

	return 0;
}
