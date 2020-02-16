#include <string>
#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void getStart(int &x, int &y, dsArray &arr) {
	for (int i = 0; i < arr.getColumns(); i++) {
		if (arr(0, i) == 's') {
			x = 0;
			y = i;
			return;
		}
	}
	int fx = arr.getRows() - 1;
	for (int i = 0; i < arr.getColumns(); i++) {
		if (arr(fx, i) == 's') {
			x = fx;
			y = i;
			return;
		}
	}
	for (int i = 0; i < arr.getRows(); i++) {
		if (arr(i, 0) == 's') {
			x = i;
			y = 0;
			return;
		}
	}
	int fy = arr.getColumns() - 1;
	for (int i = 0; i < arr.getRows(); i++) {
		if (arr(i, fy) == 's') {
			x = i;
			y = fy;
			return;
		}
	}
	cout << "error: start not on bounderies. invalid maze.";
	exit(1);
}

void checkEnd(dsArray &arr) {
	for (int i = 0; i < arr.getColumns(); i++) {
		if (arr(0, i) == 'e') {
			return;
		}
	}
	int fx = arr.getRows() - 1;
	for (int i = 0; i < arr.getColumns(); i++) {
		if (arr(fx, i) == 'e') {
			return;
		}
	}
	for (int i = 0; i < arr.getRows(); i++) {
		if (arr(i, 0) == 'e') {
			return;
		}
	}
	int fy = arr.getColumns() - 1;
	for (int i = 0; i < arr.getRows(); i++) {
		if (arr(i, fy) == 'e') {
			return;
		}
	}
	cout << "error: end not on bounderies. invalid maze.";
	exit(1);
}

bool exitFlag = false, noSolFlag = false, instack; int pfound = 0;
stack<coOrds> fork;
SLL<SLL<coOrds>> LoL;
SLL<coOrds> path;
void findPath(dsArray &obj, int x, int y) {
	bool up = false, down = false, leftp = false, rightp = false;
	if (exitFlag && !instack || noSolFlag && !instack) {
		LoL.appendSLL(path);
		return;
	}
	if (exitFlag && instack || noSolFlag && instack) {
		if (exitFlag) {
			LoL.appendSLL(path);
		}
		for (int i = 1; i < fork.getSize(); i++) {
			fork.pop();
			path.delTail();
		}
		fork.pop();
		int ins = path.getSize() - 1;
		x = path[ins].data.getx();
		y = path[ins].data.gety();
		obj(x, y) = '1';
		pfound--;
		instack = false;
	}
	try {
		if (obj(x, y) == 'e') {
			path.appendSLL(coOrds(x, y));
			exitFlag = true;
			return;
		}
		if (obj(x, y) == '1') {
			path.appendSLL(coOrds(x, y));
			obj(x, y) = '!';
		}
		if (obj(x + 1, y) == '1') {
			down = true;
			pfound++;
		}
		if (obj(x - 1, y) == '1') {
			up = true;
			pfound++;
		}
		if (obj(x, y + 1) == '1') {
			rightp = true;
			pfound++;
		}
		if (obj(x, y - 1) == '1') {
			leftp = true;
			pfound++;
		}

		if (pfound > 1) {
			instack = true;
		}
		if (instack) {
			fork.push(coOrds(x, y));
		}
		if (left) {
			findPath(obj, x, y - 1);
		}
		if (right) {
			findPath(obj, x, y + 1);
		}
		if (up) {
			findPath(obj, x - 1, y);
		}
		if (down) {
			findPath(obj, x + 1, y);
		}

		noSolFlag = true;
	}
	catch (const char* msg) {
		return;
	}
}

int main() {
	ifstream fin;
	fin.open("input_p1.txt");
	dsArray maze(fin);
	fin.close();
	return 0;
}