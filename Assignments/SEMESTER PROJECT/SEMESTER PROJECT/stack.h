#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>
#include "lists.h"
using namespace std;

template <class T>
class stack {
	SLL<T> container;
public:
	stack() {
	}
	void push(T x) {
		container.insertAtHead(x);
	}

	T pop() {
		if (container.getSize() == 0) {
			cout << "Stack Underflow " << endl;
			exit(1);
		}
		T x = container[0].data;
		container.delHead();
		return x;
	}
	bool isEmpty() {
		if (container.getSize() == 0) {
			return true;
		}
		return false;
	}
};

#endif