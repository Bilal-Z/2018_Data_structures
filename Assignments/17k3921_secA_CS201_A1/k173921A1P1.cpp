#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class dsArray {
	int rows, columns;
	char **dynArray;

public:
	dsArray() {
		rows = 0;
		columns = 0;
		dynArray = NULL;
	}

	dsArray(ifstream &x){
		rows = getInt(x);
		columns = getInt(x);
		dynArray = new char *[rows];
		for (int i = 0; i < rows; i++) {
			dynArray[i] = new char[columns];
		}

		int j;
		for (int i = 0; i < rows; i++) {
			for (j = 0; j < columns; j++) {
				dynArray[i][j] = getChar(x);
			}
		}
	}

	dsArray(const dsArray &obj) {
		rows = obj.rows;
		columns = obj.columns;
		dynArray = new char *[rows];
		for (int i = 0; i < rows; i++) {
			dynArray[i] = new char[columns];
			memcpy(dynArray[i], obj.dynArray[i], sizeof(char) * columns);
		}
	}

	dsArray& operator=(const dsArray& rhs) {
		if (this == &rhs) {
			return *this;
		}
		for (int i = rows - 1; i >= 0; i--) {
			delete dynArray[i];
		}
		delete[] dynArray;
		rows = rhs.rows;
		columns = rhs.columns;
		for (int i = 0; i < rows; i++) {
			dynArray[i] = new char[columns];
			memcpy(dynArray[i], rhs.dynArray[i], sizeof(char) * columns);
		}
	}

	~dsArray() {
		if (dynArray != NULL) {
			for (int i = rows - 1; i >= 0; i--) {
				if (dynArray[i] != NULL) {
					delete dynArray[i];
					dynArray[i] = NULL;
				}
			}
			delete[] dynArray;
		}
		dynArray = NULL;
	}
	char& operator()(int row, int column) {
		if (row < 0 || row >= rows || column < 0 || column >= columns) {
			throw "out of bounds";
		}
		return dynArray[row][column];
		
	}

	void searchFor(char c, int &x, int &y) {
		int j;
		for (int i = 0; i < rows; i++) {
			for (j = 0; j < columns; j++) {
				if (dynArray[i][j] == c) {
					x = i;
					y = j;
					return;
				}
			}
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
		}

		return stoi(s);
	}

	char getChar(ifstream &x) {
		char temp;
		while(true) {
			x.get(temp);
			if (temp == '*' || temp == '-' || temp == 's' || temp == 'e') {
				break;
			}
		}
		return temp;
	}
	
	void print() {
		int j;
		for (int i = 0; i < rows; i++) {
			for (j = 0; j < columns; j++) {
				cout << dynArray[i][j] << " ";
			}
			cout << endl;
		}
	}

};

bool exitFlag = false, noSolFlag = false;
int xPos = -1, yPos = -1;
void findStart(dsArray &obj) {
	obj.searchFor('s', xPos, yPos);
	if (xPos != -1) {
		obj(xPos, yPos) = '-';
	}
	else {
		noSolFlag = true;
	}
}

void findPath(dsArray &obj, ofstream &f , int x, int y) {
	if (exitFlag || noSolFlag) {
		return;
	}
	try {
		if (obj(x, y) == 'e') {
			f << x << " " << y << endl;
			exitFlag = true;
			return;
		}
		if (obj(x, y) == '-') {
			f << x << " " << y << endl;
			obj(x, y) = '!';

			findPath(obj, f, x, y - 1);
			findPath(obj, f, x, y + 1);
			findPath(obj, f, x - 1, y);
			findPath(obj, f, x + 1, y);
			
			noSolFlag = true;
		}
		return;
	} catch (const char* msg){
		return;
	}
}

int main() {
	ifstream fin;
	fin.open("input_p1.txt");
	dsArray maze(fin);
	fin.close();

	ofstream fout;
	fout.open("output_p1.txt");

	findStart(maze);
	findPath(maze, fout, xPos, yPos);
	fout.close();

	if (noSolFlag && !exitFlag) {
		ofstream fout;
		fout.open("output_p1.txt");
		fout << "no solution" << endl;
		fout.close();
	}
	return 0;
}
