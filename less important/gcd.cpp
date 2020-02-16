#include <iostream>
using namespace std;

// greatest comon divisor
int gcd(int a, int b){
	if(a > b){
		if(a % b == 0){
			return b;
		}
		else{
			return gcd(b, a % b);
		}
	}
	else{
		if(b % a == 0){
			return a;
		}
		else{
			return gcd(a, b % a);
		}
	}
}

int main(){
	cout << gcd(256, 384) << endl;
	cout << gcd(18, 17) << endl;
	cout << gcd(300, 345) << endl;
	cout << gcd(12, 56) << endl;
	cout << gcd(80, 60) << endl;
	cout << gcd(228, 240) << endl;
	cout << gcd(44, 42) << endl;
	cout << gcd(117, 78) << endl;
	cout << gcd(56, 84) << endl;
	cout << gcd(125, 45) << endl;
	return 0;
}
