#include <iostream>
using namespace std;

template <class T>
class stack{
	int top;
	T arr[500];
	public:
		stack(){
			top = -1;
		}
		void push(int x){
			if(top >= 500){
				cout << "Stack Overflow" << endl;
				return;
			}
			top++;
			arr[top] =x;
		}
		
		T pop(){
			if(top < 0){
				cout << "Stack Overflow" << endl;
				return 0;
			}
			int a;
			a = arr[top];
			top--;
			return a;
		}
		
		T peek(){
			return arr[top];
		}
};

int main(){
	stack<char> s1;
	char x;
	for(int i = 0; i < 5; i++){
		cout << "push: ";
		cin >> x;
		s1.push(x);
	}
	
	cout << "peeked: " << s1.peek() << endl;
	for(int i = 0; i < 5; i++){
		cout << "poped: " << s1.pop() << endl;
	}
}
