#ifndef DEQUES_H
#define DEQUES_H

#include <iostream>
#include "Lists.h"

namespace Py {
	// Double Ended Queue
	template<typename T>
	class Deque : public __DLLBase__<T> {
		using pointer = BinaryNode<T>*;
		using value = BinaryNode<T>;

	public:
		Deque() : __DLLBase__<T>() {}
		Deque(initializer_list<T> init_l) : __DLLBase__<T>(init_l) {}

		// array based initialization
		template<size_t s>
		Deque(T(&arr)[s]) : __DLLBase__<T>(arr) {}

		// Iterator based initialization, supports iterators that have an overloaded ++ and * operator
		// i.e. supports initialization from vector<>, deque<>, list<>
		template<typename _Iter>
		Deque(_Iter begin, _Iter end) {
			_Iter it = begin;
			this->__head__ = new value{ NULL };
			this->__head__->data = *it;
			this->__head__->next = NULL;
			this->__head__->prev = NULL;
			this->__tail__ = this->__head__;
			this->__size__++;
			++it;
			while (it != end) {
				pointer temp = new value{ NULL };
				temp->data = *it;
				temp->prev = NULL;
				temp->next = NULL;

				this->__tail__->next = temp;
				temp->prev = this->__tail__;
				this->__tail__ = temp;
				temp = NULL;
				++it;
				this->__size__++;
			}
		}

		// copy, move constructors and assignments
		Deque(const Deque& obj) {
			if (obj.__size__ > 0) {
				this->__copy_values__(obj.__head__, obj.__tail__);
			}
			else {
				this->__head__ = NULL;
				this->__tail__ = NULL;
				this->__size__ = 0;
			}
		}

		Deque(Deque&& obj)noexcept {
			this->__head__ = obj.__head__;
			this->__tail__ = obj.__tail__;
			this->__size___ = obj.__size__;
			obj.null_out();
		}

		Deque& operator= (const Deque& obj) {
			// clearing the previously allocated memory
			this->clear();

			if (obj.__size__ > 0) {
				this->__copy_values__(obj.__head__, obj.__tail__);
			}
			else {
				this->__head__ = NULL;
				this->__tail__ = NULL;
				this->__size__ = 0;
			}

			return*this;
		}

		Deque& operator= (Deque&& obj) noexcept {
			// clearing the previously allocated memory
			while (this->__head__) {
				pointer temp = this->__head__;
				this->__head__ = this->__head__->next;
				delete temp;
			}

			this->null_out();

			this->__head__ = obj.__head__;
			this->__tail__ = obj.__tail__;
			this->__size__ = obj.__size__;
			obj.null_out();

			return*this;
		}

		bool operator== (const Deque& obj) {
			if (this->__size__ != obj.__size__)return false;

			pointer temp = this->__head__;
			pointer obj_temp = obj.__head__;

			while (temp or obj_temp) {
				if (temp->data != obj_temp->data) {
					return false;
				}
				temp = temp->next;
				obj_temp = obj_temp->next;
			}

			return true;
		}

		operator bool() { return this->__head__ != NULL; }

		// for concatenation
		Deque& concat(Deque<T> obj) {
			if (this->__size__ > 0) {
				// joining the two lists
				this->__concat__(obj.__head__, obj.__tail__);

				this->__size__ += obj.__size__;
				obj.null_out();
			}
			else { this->operator=(obj); }
			return *this;
		}

		~Deque() {}
	};
}

#endif // !DEQUES_H
