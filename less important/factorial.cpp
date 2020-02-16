#include <iostream>
using namespace std;

int factorial(int n){
	if(n == 1){
		return 1;
	}
	else{
		return n * factorial(n - 1);
	}
}

int factorialTail(int n, int res = 1){
	if(n == 1){
		return res;
	}
	else{
		return factorialTail(n - 1, res * n);
	}
}

int main(){
	cout << factorial(4) << endl;
	cout << factorialTail(5) << endl;
	return 0;
}
