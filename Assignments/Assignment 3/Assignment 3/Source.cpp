#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Header.h"
#include "lists.h"
using namespace std;

int getInt(ifstream &x) {
	char temp;
	string s = "";
	do {
		x.get(temp);
	} while (!(temp - '0' >= 0 && temp - '0' <= 9));
	while (temp >= '0' && temp <= '9' && !x.eof()) {
		s += temp;
		x.get(temp);
	}

	return stoi(s);
}

class interval {
public:
	int stime;
	int rtime;
	int ctime;
	interval() {
		stime = 0;
		rtime = 0;
		ctime = 0;
	}
	interval(const interval &obj) {
		stime = obj.stime;
		rtime = obj.rtime;
		ctime = obj.ctime;
	}

	interval(int s, int r, int c) {
		stime = s;
		rtime = r;
		ctime = c;
	}

	interval& operator=(const interval &obj) {
		stime = obj.stime;
		rtime = obj.rtime;
		ctime = obj.ctime;
		return *this;
	}

	bool operator<= (const interval& i) {
		int a = stime + rtime + ctime;
		int b = i.stime + i.rtime + i.ctime;
		if (stime < i.stime) {
			return true;
		}
		else if (stime == i.stime) {
			if (a < b) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool operator> (const interval& i) {
		int sum = stime + rtime + ctime;
		if (i.stime >= sum) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator== (const interval& i) {
		if ((stime == i.stime) && (rtime == i.rtime) && (ctime == i.ctime)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!= (const interval& i) {
		if ((stime != i.stime) || (rtime != i.rtime) || (ctime != i.ctime)) {
			return true;
		}
		else {
			return false;
		}
	}

	friend ostream &operator<<(ostream &output, const interval &i) {
		output << " " << i.stime << " " << i.rtime << " " << i.ctime << " ";
		return output;
	}

};

void swapStr(string &a, string &b) {
	string temp = a;
	a = b;
	b = temp;
 }


int main() {
	SLL<interval> list;
	string files[] = { "A3P1ProgMgr1.txt", "A3P1ProgMgr2.txt", "A3P1ProgMgr3.txt", "A3P1ProgMgr4.txt", "A3P1ProgMgr5.txt" };
	// randomly rearrange array
	int random;
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		random = rand() % 5;
		swapStr(files[i], files[random]);
	}

	ifstream inFile;
	interval temp;
	int i, j, k;
	for (k = 0; k < 5; k++) {
		cout << "reading " << files[k] << endl;
		inFile.open(files[k]);
		j = getInt(inFile);
		for (i = 0; i < j; i++) {
			temp.stime = getInt(inFile);
			temp.rtime = getInt(inFile);
			temp.ctime = getInt(inFile);
			list.appendSLL(temp);
		}
		inFile.close();
	}
	list.sort();
	list.display();

	BST<interval> tree;
	for (int i = 0; i < list.getSize(); i++) {
		tree.insertNode(list[i].data);
	}

	SLL<interval> comp = tree.maxBranch();
	tree.printMaxBranch();
	SLL<interval> conf;

	for (int i = 0; i < list.getSize(); i++) {
		temp = list[i].data;
		if (!comp.existsIn(temp)) {
			conf.appendSLL(temp);
		}
	}

	cout << endl;
	conf.display();

	ofstream fout;
	fout.open("compatible.txt");
	for (int i = 0; i < comp.getSize(); i++) {
		temp = comp[i].data;
		fout << temp << endl;
	}
	fout.close();

	fout.open("conflict.txt");
	for (int i = 0; i < conf.getSize(); i++) {
		temp = conf[i].data;
		fout << temp << endl;
	}
	fout.close();

	return 0;
}
