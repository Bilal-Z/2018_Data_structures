#include <iostream>
using namespace std;
#define arrsize(a) (sizeof(a) / sizeof(a[0]))

void mergeSort(int arr[], int size){
	if(size < 2){
		return;
	}
}

int main(){
	int arr[] = {12,40, 19, 0, 65, 42, 10, 6, 2, 100};
	mergeSort(arr, arrsize(arr));
	return 0;
}
