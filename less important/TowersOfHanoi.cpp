#include <iostream>
using namespace std;

void towersOfHanoi(int n, int from, int to, int spare){
	if(n == 1){
		cout << "move from spike " << from << " to spike " << to << endl;
	}
	else{
		towersOfHanoi(n - 1, from, spare, to);
		towersOfHanoi(1, from, to, spare);
		towersOfHanoi(n - 1, spare, to, from);
	}
}

int main(){
	towersOfHanoi(3, 1, 2, 3);
	
	return 0;
}
