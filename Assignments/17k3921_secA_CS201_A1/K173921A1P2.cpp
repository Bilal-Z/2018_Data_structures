#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class safeArray {
	int size;
	char *dynArray;
public:
	safeArray() {
		size = 0; 
		dynArray = NULL;
	}

	safeArray(int s) {
		size = s;
		dynArray = new char[size];
	}

	safeArray(const safeArray &obj) {
		size = obj.size;
		dynArray = new char[size];
		memcpy(dynArray, obj.dynArray, sizeof(char) * size);
	}

	~safeArray() {
		size = 0;
		delete[] dynArray;
	}

	safeArray& operator=(const safeArray &rhs) {
		if (this == &rhs) {
			return *this;
		}
		this->~safeArray();

		size = rhs.size;
		dynArray = new char[size];
		memcpy(dynArray, rhs.dynArray, sizeof(char) * size);
		return *this;
	}

	safeArray& operator=(const string &rhs) {
		this->~safeArray();
		size = rhs.size();
		dynArray = new char[size];
		for (int i = 0; i < size; i++) {
			dynArray[i] = rhs[i];
		}
		return *this;
	}

	char &operator[](int i) {
		if (i < 0 || i >= size) {
			throw "out of bounds";
		}
		return dynArray[i];
	}

	void print() {
		for (int i = 0; i < size; i++) {
			cout << dynArray[i];
		}
		cout << endl;
	}

	int getSize() {
		return size;
	}

	string toString() {
		string s = "";
		for (int i = 0; i < size; i++) {
			s += dynArray[i];
		}
		return s;
	}

	int findPos(char c, int i = 0) {
		for (; i < size; i++) {
			if (dynArray[i] == c) {
				return i;
			}
		}
		return -1;
	}
};

int findFirst(safeArray &l, safeArray &s, int &is, int ls) { // l = larger, s = smaller, is = i of small, ls = i of large
	int r;
	for (; is < s.getSize(); is++) {
		r = l.findPos(s[is], ls);
		if (r != -1) {
			return r;
		}
	}
}

bool fullMatch(safeArray &l, safeArray &s) {
	string large = l.toString(), small = s.toString();
	if (large.find(small) != string::npos) {
		return true;
	}
	return false;
}

void printTofile(string sa[], int as) {
	ofstream fout;
	fout.open("output_p2.txt");
	for (int i = 0; i < as; i++) {
		if (sa[i] != "\0") {
			fout << sa[i];
			if (sa[i + 1] != "\0") {
				fout << '*';
			}
		}
	}
}

bool inArr(string sa[],int as, string s) {
	for (int i = 0; i < as; i++) {
		if (sa[i] == s) {
			return true;
		}
	}
	return false;
}

void seqMatch(safeArray &a, safeArray &b) {
	string *strArray;
	int strArray_size = a.getSize(), strArray_i = 0;
	strArray = new string[strArray_size];
	for (int i = 0; i < strArray_size; i++) {
		strArray[i] = "\0";
	}
	string temp;
	int small = 0, large = 0;
	if (b.getSize() < a.getSize() || b.getSize() == a.getSize()) {
		if (fullMatch(a, b)) {
			strArray[strArray_i] = b.toString();
			printTofile(strArray, strArray_size);
			return;
		}
		while (small < b.getSize()) {
			temp = "";
			large = findFirst(a, b, small, large);
			while (true) {
				try {
					if (a[large] == b[small]) {
						temp += a[large];
						small++;
						large++;
					}
					else {
						break;
					}
				}catch (const char *msg) {
					break;
				}
			}
			if (inArr(strArray, strArray_size, temp) == false) {
				strArray[strArray_i] = temp;
				strArray_i++;
			}
		}
		printTofile(strArray, strArray_size);
		return;
	}
	else {
		if (fullMatch(b, a)) {
			strArray[strArray_i] = a.toString();
			printTofile(strArray, strArray_size);
			return;
		}
		while (small < a.getSize()) {
			temp = "";
			large = findFirst(b, a, small, large);
			while (true) {
				try {
					if (b[large] == a[small]) {
						temp += b[large];
						small++;
						large++;
					}
					else {
						break;
					}
				}
				catch (const char *msg) {
					break;
				}
			}
			if (inArr(strArray, strArray_size, temp) == false) {
				strArray[strArray_i] = temp;
				strArray_i++;
			}
		}
		printTofile(strArray, strArray_size);
		return;
	}

}

int main() {
	safeArray s1, s2;
	ifstream fin;
	fin.open("input_p2.txt");
	string temp;
	getline(fin, temp);
	s1 = temp;
	getline(fin, temp);
	s2 = temp;
	fin.close();

	seqMatch(s1, s2);
	
	return 0;
}
