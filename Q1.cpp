#include <iostream>
#include "lists.h"
using namespace std;

template <class T>
class stack{
	SLL<T> container;
	public:
	stack(){
	}
	void push(T x){
		container.insertAtHead(x);
	}
	
	T pop(){
		if(container.head == NULL){
			cout << "Stack Underflow " << endl;
			exit(1);
		}
		T x = container.head->data;
		container.delHead();
		return x;
	}
};

template <class T>
class queue{
	public:
		public:
		SLL<T> container;
		queue(){
		}
		void enqueue(T x){
			container.appendSLL(x);
		}
		
		T dequeue(){
			if(container.head == NULL){
			cout << "Error: Queue already empty" << endl;
			exit(1);
		}
			T x = container.head->data;
			container.delHead();
			return x;
		}
};

int main(){
	stack<int> s;
	s.push(12);
	s.push(23);
	s.push(15);
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	
	queue<int> q;
	q.enqueue(5);
	q.enqueue(16);
	q.enqueue(46);
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	return 0;
}
