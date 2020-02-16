#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class inArray {
	int size;
	int *arr;
public:
	inArray() {
		size = 0;
		arr = NULL;
	}
	inArray(ifstream &f) {
		string temp;
		getline(f, temp);
		size = stoi(temp);
		if (size < 1 || size > 30000) {
			cout << "size error";
			exit(1);
		}
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			getline(f, temp);
			arr[i] = stoi(temp);
			if (arr[i] < 1 || arr[i] > int(pow(10, 9)) ){
				cout << "data error ai = "<< arr[i] << " line " << i +1 <<endl;
				exit(1);
			}
		}
		for (int i = 0; i < size; i++) {
			cout << arr[i] << endl;
		}
	}

	int &operator [](int i) {
		if (i<0 || i>= size) {
			cout << "out of bounds" << endl;
			exit(1);
		}
		return arr[i];
	}
	
	int getSize(){
		return size;
	}
};

class query {
	int size;
	int **arr;
public:
	query() {
		size = 0;
		arr = NULL;
	}
	query(ifstream &f) {
		string temp;
		getline(f, temp);
		size = stoi(temp);
		cout << size << endl;
		arr = new int*[size];
		for (int i = 0; i < size; i++) {
			arr[i] = new int[3];
		}
		int j;
		for (int i = 0; i < size; i++) {
			for (j = 0; j < 3; j++) {
				arr[i][j] = getInt(f);
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
	int getInt(ifstream &x) {
		char temp;
		string s = "";
		do {
			x.get(temp);
		} while (!(temp - '0' >= 0 && temp - '0' <= 9));
		while (temp >= '0' && temp <= '9') {
			s += temp;
			x.get(temp);
			if (x.eof()) {
				break;
			}
		}

		return stoi(s);
	}

	int &operator ()(int i, int j){
	if(i<0 || i>= size || j<0 || j> 2 ) {
		cout << "querry out of bounds" << endl;
		exit(1);
		}
		return arr[i][j];
	}
	
	void computeQuries(inArray &ia){
		ofstream fout;
		fout.open("output_p3.txt");
		cout << "were in" << endl;
		int ii, i, j, k, count;
		for(int io = 0; io < size; io++){
			i = arr[io][0];
			if(i < 1){
				i = 1;
			}
			j = arr[io][1];
			if(j >= ia.getSize()){
				cout << "error j > n";
				exit(1);
			}
			if(j < i){
				cout << "error j < i";
				exit(1);
			}
			k = arr[io][2];
			if (k < 1 || k > pow(10, 9)) {
				cout << "k data error";
				exit(1);
			}
			
			count = 0;
			for(ii = i; ii <= j; ii++){
				if(ia[ii] > k){
					count++;
				}
			}
			cout << count <<endl;
			fout << count << endl;
		}
		fout.close();
	}
};

int main() {
	ifstream infile;
	infile.open("input_p3.txt");
	inArray list(infile);
	query q(infile);
	infile.close();
	q.computeQuries(list);
	return 0;
}
