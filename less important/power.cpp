#include <iostream>
using namespace std;

int power(int base,int exp){
	if(exp == 0){
		return 1;
	}
	else{
		return base * power(base, exp - 1);
	}
}

int powerTail(int base,int exp, int res = 0){
	if(exp == 0){
		return res;
	}
	else{
		return powerTail(base, exp - 1, base * base);
	}
}

int main(){
	cout << power(4, 2) << endl;
	cout << powerTail(4, 2) << endl;
	
	return 0;
}
