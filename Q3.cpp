#include <iostream>
#include "lists.h"
using namespace std;

template <class T>
class queue{
	SLL<T> container;
	public:
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

void plndrme(string s){
	queue<char> q;
	bool drme = true;
	for(int i = s.length() - 1; i > - 1 ; i--){
		q.enqueue(s[i]);
	}
	for(int i = 0; i < s.length() / 2; i++){
		if(s[i] != q.dequeue()){
			drme = false;
		}
	}
	if(drme){
		cout << "is palindrome" << endl;
	}
	else{
	cout << "not palindrome"<< endl;
	}
}

int main(){
	plndrme("backwords");
	plndrme("radar");
	return 0;
}
