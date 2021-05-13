#include <iostream>
#include <cstddef>
#include <algorithm>
#include <stdexcept>


#include "stack_interface.h"
template<typename T>
class StackLinked : public stack_interface<T> {
    public:
		
			// Memberi stack klase su vec inicijalizirani
			StackLinked() = default;

			// Copy-constructor
			StackLinked(const StackLinked& other) {
				
				head_ = new Node{other.head_->element_};
				
				Node* temp1 = head_;
				Node* temp2 = other.head_->next_;
				while(temp2 != other.tail_) {

					temp1->next_ = new Node{temp2->element_};

					temp1 = temp1->next_;
					temp2 = temp2->next_;

				}

				size_ = other.size_;
			}

			StackLinked(StackLinked&& other) : 
				head_{other.head_}, tail_{other.tail_}, size_(other.size_) {
			
					other.head_ = nullptr;
					other.tail_ = nullptr;
					other.size_ = 0;
			
			}

			StackLinked& operator=(const StackLinked& other) {
				if (this == &other) return *this;

				if (!empty())	clear();

				
				Node* temp1 = head_;
				Node* temp2 = other.head_->next_;
				while(temp2 != other.tail_) {

					temp1->next_ = new Node{temp2->element_};

					temp1 = temp1->next_;
					temp2 = temp2->next_;

				}

				size_ = other.size_;
				return *this;

			}

			StackLinked& operator=(StackLinked&& other) {
				if (this == &other) return *this;

				if (!empty()) clear();

				head_ = other.head_;
				tail_ = other.tail_;
				size_ = other.size_;
				
				other.head_ = nullptr;
				other.tail_ = nullptr;
				other.size_ = 0;

				return *this;
			}

			~StackLinked() {clear();}
			
			void clear() {

				while (head_ != nullptr) {
					Node* temp = head_;
					head_ = (head_== tail_)? nullptr : head_->next_;
						
					delete temp;

				}

				size_ = 0;

			}

			bool empty() const override {return head_ == nullptr;}
			size_t size() const override {return size_;}

			bool operator==(const StackLinked&) const;
			bool operator!=(const StackLinked&) const;

			
			template <typename U>
			StackLinked& operator+(const StackLinked<U>&);

			void push(const T& val) override {
				
				auto temp = head_;
				head_ = new Node{val};
				head_->next_ = temp;

			}

			void push(T&& val) override {

				auto temp = head_;
				head_ = new Node{std::move(val)};
				head_->next_ = temp;

			}

			T& top() override { 
				if (empty()) throw std::underflow_error("The Stack is currently empty.");
				return head_->element_;
			}

			const T& top() const override {
				if (empty()) throw std::underflow_error("The Stack is currently empty.");
				return head_->element_;
			}

			void pop() override {
				if (empty()) throw std::underflow_error("The stack is currently empty.");
				
				auto temp = head_;
				head_ = (head_== tail_)? nullptr : head_->next_;
					
				delete temp;
				size_--;

			}

    private:
				struct Node {
					T element_;
					Node* next_{nullptr};

					Node(const T& el, Node* n = nullptr) : element_{el}, next_{n} {}
					Node(T&& el, Node* n = nullptr) : element_{std::move(el)}, next_{n} {}
				};

				Node* head_{nullptr};
				Node* tail_{nullptr};
        size_t size_{0};
};

template <typename T>
std::ostream& operator<<(std::ostream& out, StackLinked<T>& stack) {

	while (!stack.empty()) {
		out << stack.top() << " ";
		stack.pop();
	}

	out << std::endl;
	return out;
}

template <typename T>
bool StackLinked<T>::operator==(const StackLinked<T>& other) const {
	if (size() != other.size()) return false;
	if (empty()) return true;

	Node* temp1 = head_;
	Node* temp2 = other.head_;

	while (temp1 != tail_) {
		if (temp1->element_ != temp2->element_) return false;

		temp1 = temp1->next_;
		temp2 = temp2->next_;
	}

	return true;
}

template <typename T>
bool StackLinked<T>::operator!=(const StackLinked<T>& other) const {
	return !(*this == other);
}

template<typename T>
template<typename U>
StackLinked<T>& StackLinked<T>::operator+(const StackLinked<U>& other) {
	if (!std::is_same<T,U>::value) throw std::invalid_argument("The 2 stacks are not of the same type.");

	tail_->next_ = other.head_;	
	return *this;
}
