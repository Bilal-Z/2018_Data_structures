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

void chkStr(string s){
	queue<char> q;
	for(int i = 0; i < s.length(); i++){
		q.enqueue(s[i]);
	}
	bool opening = false, closing = false;
	char temp;
	string nested = "correct";
	for(int i = 0; i < s.length(); i++){
		temp = q.dequeue();
		if(temp == '}' || temp == ']' || temp == ')'){
			closing = true;
			if(closing && !opening){
				nested = "incorrect";
				break;
			}
		}
		else if(temp == '{' || temp == '[' || temp == '('){
			opening = true;
		}
	}
	if(opening && !closing){
		nested = "incorrect";
	}
	cout << "parenthesis nesting is " << nested << endl;
}

int main(){
	chkStr("Wron)g string");
	chkStr("correct {string}");
	return 0;
}
