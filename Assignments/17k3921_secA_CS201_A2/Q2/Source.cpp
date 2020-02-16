#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

char operators[] = { '-', '+', '/', '*', '^' };
bool isOp(char c) {
	for (int i = 0; i < 5; i++) {
		if (c == operators[i]) {
			return true;
		}
	}
	return false;
}

int getPriority(char c) {
	for (int i = 0; i < 5; i++) {
		if (c == operators[i]) {
			return i;
		}
	}
}

int calExp(int b, int e){
	int res = 1;
	for (int i = 0; i < e; ++i)
	{
		res *= b;
	}
	return res;
	
}

template <class T>
class stack {
	int top;
	T arr[500];
public:
	stack() {
		top = -1;
	}
	void push(T x) {
		if (top < 0) {
			top = -1;
		}
		if (top >= 500) {
			cout << "Stack Overflow" << endl;
			return;
		}
		top++;
		arr[top] = x;
	}

	T pop() {
		if (top < 0) {
			cout << "Stack underflow" << endl;
			return 0;
		}
		int a;
		a = arr[top];
		top--;
		return a;
	}

	bool isEmpty() {
		return (top < 0 ? true : false);
	}

	T peek() {
		return arr[top];
	}
};

int getInt(ifstream &x, char c) {
	char temp = c;
	string s = "";
	while ((temp >= '0' && temp <= '9') && !x.eof() ) {
		s += temp;
		x.get(temp);
	}

	return stoi(s);
}

char getElement(ifstream &x) {
	char temp;
	do {
		x.get(temp);
	} while (temp == ' ');
	return temp;
	
}

string genPostFix() {
	string output;
	stack<char> opStack;
	ifstream fin;
	fin.open("input.txt");
	int x, existing, inserting;
	char element;
	while (!fin.eof()) {
		element = getElement(fin);
		existing = 0;
		inserting = 0;
		if (element >= '0' && element <= '9') {
			x = getInt(fin, element);
			output += to_string(x);
			output += " ";
		}
		else if (element == '(') {
			opStack.push(element);
		}
		else if (isOp(element)) {
			while (true) {
				if (opStack.isEmpty()) {
					opStack.push(element);
					break;
				}
				else if (opStack.peek() == '(') {
					opStack.push(element);
					break;
				}
				else {
					existing = getPriority(opStack.peek());
					inserting = getPriority(element);
					if (inserting > existing) {
						opStack.push(element);
						break;
					}
					else {
						output += opStack.pop();
						output += " ";
					}
				}
			}
		}
		else if (element == ')') {
			while (opStack.peek() != '(') {
				output += opStack.pop();
				output += " ";
			}
			opStack.pop();
		}
	}
	fin.close();
	while (!opStack.isEmpty()) {
		output += opStack.pop();
		output += " ";
	}
	return output;
}

int solvePostFix() {
	stack<int> intStack;
	ifstream fin;
	fin.open("output.txt");
	char element;
	int x;
	while (!fin.eof()) {
		fin.get(element);
		if (element >= '0' && element <= '9') {
			x = getInt(fin, element);
			intStack.push(x);
		}
		else if (isOp(element)) {
			switch (element){
			case '-':
				x = intStack.pop() - intStack.pop();
				intStack.push(x);
				break;
			case '+':
				x = intStack.pop() + intStack.pop();
				intStack.push(x);
				break;
			case '/':
				x = intStack.pop() / intStack.pop();
				intStack.push(x);
				break;
			case '*':
				x = intStack.pop() * intStack.pop();
				intStack.push(x);
				break;
			case '^':
				x = calExp(intStack.pop(), intStack.pop());
				intStack.push(x);
				break;
			default:
				break;
			}
		}
	}
	fin.close();
	return intStack.pop();
}

int main() {
	string postFix = genPostFix();
	cout << postFix << endl;
	ofstream fout;
	fout.open("output.txt");
	fout << postFix;
	fout.close();
	int ans = solvePostFix();
	cout << ans << endl;
	fout.open("output.txt");
	fout << postFix << endl << ans;
	fout.close();
	return 0;
}