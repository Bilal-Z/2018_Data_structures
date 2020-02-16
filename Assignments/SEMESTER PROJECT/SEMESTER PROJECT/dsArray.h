#ifndef DSARRAY_H
#define DSARRAY_H
#include <string>
#include <iostream>
using namespace std;

template <class T>
class dsArray {
	int rows, columns;
	T **dynArray;

public:
	dsArray() {
		rows = 0;
		columns = 0;
		dynArray = NULL;
	}

	dsArray(int r, int c) {
		rows = r;
		columns = c;
		dynArray = new T *[rows];
		for (int i = 0; i < rows; i++) {
			dynArray[i] = new T[columns];
		}
	}

	dsArray(const dsArray &obj) {
		rows = obj.rows;
		columns = obj.columns;
		dynArray = new T *[rows];
		for (int i = 0; i < rows; i++) {
			dynArray[i] = new T[columns];
			memcpy(dynArray[i], obj.dynArray[i], sizeof(T) * columns);
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
			dynArray[i] = new T[columns];
			memcpy(dynArray[i], rhs.dynArray[i], sizeof(T) * columns);
		}
	}

	~dsArray() {
		if (dynArray != NULL) {
			for (int i = rows - 1; i >= 0; i--) {
				if (dynArray[i] != NULL) {
					delete[] dynArray[i];
					dynArray[i] = NULL;
				}
			}
			delete[] dynArray;
		}
		dynArray = NULL;
	}

	T& operator()(int row, int column) {
		if (row < 0 || row >= rows || column < 0 || column >= columns) {
			exit(1);
		}
		return dynArray[row][column];

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

	int getRows() {
		return rows;
	}

	int getColumns() {
		return columns;
	}

};
#endif
