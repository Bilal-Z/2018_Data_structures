#include <iostream>
#include <cstdlib>
#include <cstring> 
#include "lists.h"
using namespace std;


int main() {
	SLL<int> a = { 23, 6, 1, 19, 8, 44, 13, 50 };
	a.insert(5, 2);
	a.insert({15, 33}, 2);
	a.appendSLL(0);
	a.display();
	mergeSort(&a[0], a.getSize());
	a.display();
	return 0;
}