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

bool exitFlag = false, noSolFlag = false, pushStack; int pfound = 0, pathpos;
stack<coOrds> fork;
SLL<SLL<coOrds>> listOfLists;
SLL<coOrds> path, list;

void findPath(dsArray &obj, int x, int y) {
	bool up = false, down = false, leftp = false, rightp = false;
	if (exitFlag|| noSolFlag) {
		if (exitFlag) {
			list = path;
			listOfLists.appendSLL(list);
		}
		if (!fork.isEmpty()) {
			coOrds xy = fork.pop();
			x = xy.getx();
			y = xy.gety();
			obj(x, y) = '1';
			obj(path[pathpos].data.getx(), path[pathpos].data.gety()) = '0';
			int i = path.getSize() - 1;
			while(path.getSize() > pathpos + 1) {
				obj(path[i].data.getx(), path[i].data.gety()) = '1';
				path.delTail();
				i--;
			}
			path.delTail();
			path.delTail();
			if (exitFlag) {
				obj(listOfLists[listOfLists.getSize() - 1].data[listOfLists[listOfLists.getSize() - 1].data.getSize() - 1].data.getx(), listOfLists[listOfLists.getSize() - 1].data[listOfLists[listOfLists.getSize() - 1].data.getSize() - 1].data.gety()) = 'e';
			}
			path.display();
			cout << pathpos << endl;
			obj.print();
			exitFlag = false;
			noSolFlag = false;
		}
		else {
			cout << endl;
			obj.print();
			return;
		}
		//return;		
	}

	if (obj(x, y) == 'e') {
		path.appendSLL(coOrds(x, y));
		exitFlag = true;
		return;
	}
	if (obj(x, y) == '1' || obj(x, y) == 's') {
		path.appendSLL(coOrds(x, y));
		obj(x, y) = '!';
	}
	pfound = 0;
	pushStack = false;
	if (obj(x + 1, y) == '1' || obj(x + 1, y) == 'e') {
		down = true;
		pfound++;
	}
	if (obj(x - 1, y) == '1' || obj(x - 1, y) == 'e') {
		up = true;
		pfound++;
	}
	if (obj(x, y + 1) == '1' || obj(x, y + 1) == 'e') {
		rightp = true;
		pfound++;
	}
	if (obj(x, y - 1) == '1' || obj(x, y - 1) == 'e') {
		leftp = true;
		pfound++;
	}

	if (pfound > 1) {
		pathpos = path.getSize();
		pushStack = true;
	}
	if (pushStack) {
		fork.push(coOrds(x, y));
		if (obj(x + 1, y) == 'e') {
			fork.pop();
		}
		if (obj(x - 1, y) == 'e') {
			fork.pop();
		}
		if (obj(x, y + 1) == 'e') {
			fork.pop();
		}
		if (obj(x, y - 1) == 'e') {
			fork.pop();
		}
	}
	if (up) {
		findPath(obj, x - 1, y);
	}
	if (down) {
		findPath(obj, x + 1, y);
	}
	if (leftp) {
		findPath(obj, x, y - 1);
	}
	if (rightp) {
		findPath(obj, x, y + 1);
	}

	if (!exitFlag || pfound == 0) {
		noSolFlag = true;
	}
}

int main() {
	ifstream fin;
	fin.open("input.txt");
	dsArray maze(fin);
	fin.close();
	maze.print();
	int x, y;
	getStart(x, y, maze);
	checkEnd(maze);
	findPath(maze, x, y);
	int s = listOfLists.getSize();
	for (int i = 0; i < s; i++) {
		listOfLists[i].data.display();
	}

	ofstream fout;
	fout.open("output.txt");
	int si, j;
	for (int i = 0; i < s; i++) {
		fout << "Path#" << i + 1 << " = { ";
		si = listOfLists[i].data.getSize();
		for (j = 0; j < si; j++) {
			fout << listOfLists[i].data[j].data;
			fout << " ";
		}
		fout << "}" << endl;
		fout << "Cost = " << si << endl;
	}
	fout.close();

	return 0;
}