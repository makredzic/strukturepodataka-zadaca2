#include <iostream>
#include <cstddef>
#include <algorithm>
#include <stdexcept>


#include "stack_interface.h"
template<typename T>
class StackArr : public stack_interface<T> {
    public:
		
			StackArr(size_t cap = 50) : capacity_{cap}, size_{0}, data_{new T[cap]} {};

			// Copy-constructor
			StackArr(const StackArr& other) :
				capacity_{other.capacity_},
				size_{other.size_},
				data_{new T[capacity_]}
			{
				for (int i = 0; i < size_; ++i)	{
					data_[i] = other.data_[i];
				}
			}

			StackArr(StackArr&& other) : 
				capacity_{other.capacity_}, 
				size_{other.size_}, 
				data_{other.data_} {
				other.data_ = nullptr;
			}

			StackArr& operator=(const StackArr& other) {
				if (other == *this) return *this;

				if (other.size_ > capacity_) {
					delete [] data_;
					capacity_ = other.capacity_;
					data_ = new T[capacity_];
				}

				for (size_t i = 0; i < other.size_; i++) {
					data_[i] = other.data_[i];
				}
				//std::copy(other.data_, other.data_+size_, data_);

				size_ = other.size_;
				return *this;
			}

			StackArr& operator=(StackArr&& other) {
					capacity_ = other.capacity_;
					size_ = other.size_;
					std::swap(data_, other.data_);

					return *this;
			}

			~StackArr() {
				delete [] data_;
			};

			void reallocate(size_t);
			bool empty() const override {return !(size_);}
			size_t size() const override {return size_;}
			size_t capacity() const {return capacity_;}

			bool operator==(const StackArr&) const;
			bool operator!=(const StackArr&) const;

			//StackArr operator+(const StackArr&) const;
			
			template <typename U>
			StackArr& operator+(const StackArr<U>&);

			void push(const T& val) override {
				if (size_ == capacity_) reallocate(2*size_);

				data_[size_] = val;
				size_++;
			}

			void push(T&& val) override {
				if (size_ == capacity_) reallocate(2*size_);

				data_[size_] = std::move(val);
				size_++;
			}

			T& top() override { 
				if (empty()) throw std::underflow_error("The stack is currently empty.");
				return data_[size_-1];
			}

			const T& top() const override {
				if (empty()) throw std::underflow_error("The stack is currently empty.");
				return data_[size_-1];
			}

			void pop() override {
				if (empty()) throw std::underflow_error("The stack is currently empty.");
				size_--;
			}

    private:
        size_t capacity_;
        size_t size_;
        T* data_;
};

template <typename T>
void StackArr<T>::reallocate(size_t new_cap) {
	if (new_cap == capacity_) return;

		T* ptr = new T[new_cap];

		int transfer = (new_cap <= size_)? new_cap : size_;
		for (size_t i = 0; i < transfer; i++) ptr[i] = std::move(data_[i]);
		

		std::swap(data_, ptr);
		delete[] ptr;

		size_ = transfer;
		capacity_ = new_cap;

};

template <typename T>
std::ostream& operator<<(std::ostream& out, StackArr<T>& stack) {

	while (!stack.empty()) {
		out << stack.top() << " ";
		stack.pop();
	}

	out << std::endl;
	return out;
}

template <typename T>
bool StackArr<T>::operator==(const StackArr<T>& other) const {
	if (size() != other.size()) return false;

	for (size_t i = 0; i < size_; i++) {
		if (data_[i] != other.data_[i]) return false;
	}

	return true;
}

template <typename T>
bool StackArr<T>::operator!=(const StackArr<T>& other) const {
	return !(*this == other);
}

/* Implementacija 1: stack1 + stack2 = novi stack sa clanovima stack1 i onda clanovima stack2
template <typename T>
template <typename U>
StackArr<T> StackArr<T>::operator+(const StackArr<U>& other) const {
	if (!std::is_same<T,U>::value) throw std::invalid_argument("The 2 stacks are not of the same type.");

	size_t new_size = size_ + other.size_;
	size_t new_capacity = (new_size > capacity_)? 2*new_size : capacity_;

	StackArr<T> new_stack{new_capacity};

	for (size_t i = 0; i < size_; i++) new_stack.data_[i] = data_[i];
	for (size_t i = 0; i < other.size_; i++) new_stack.data_[i+size_] = other.data_[i];

	new_stack.size_ = new_size;

	
	return new_stack;	

}
*/

template<typename T>
template<typename U>
StackArr<T>& StackArr<T>::operator+(const StackArr<U>& other) {
	if (!std::is_same<T,U>::value) throw std::invalid_argument("The 2 stacks are not of the same type.");

	size_t new_size = size_ + other.size_;
	
	auto temp = data_;
	if (new_size > capacity_) reallocate(2*new_size);

	for (size_t i = 0; i < other.size_; i++) data_[i+size_] = other.data_[i];
	size_ = new_size;

	return *this;
}
