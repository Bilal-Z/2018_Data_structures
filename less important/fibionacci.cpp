#include <iostream>
using namespace std;

int fib(int x){
	if(x == 0){
		return 0;
	}
	else if(x == 1){
		return 1;
	}
	else{
		return fib(x - 1) + fib(x - 2);
	}
}

int fibTail( int n , int next = 1, int result = 0)
{
	if (n == 0){
    	return result;
	}
	return fibTail(n - 1, next + result, next);
}


int main(){
	cout << fib(15) << endl;
	cout << fibTail(12) << endl;
	
	return 0;
}
