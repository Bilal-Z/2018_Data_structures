#ifndef HEADER_H
#define HEADER_H

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

	dsArray(ifstream &x) {
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
		while (true) {
			x.get(temp);
			if (temp == '0' || temp == '1' || temp == 's' || temp == 'e') {
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

	int getRows() {
		return rows;
	}

	int getColumns() {
		return columns;
	}

};

template <class T>
class nodeSL {
public:
	T data;
	nodeSL<T> *next;

	nodeSL() {
		next = NULL;
		data = 0;
	}

	nodeSL(int i, nodeSL<T> *n = NULL) {
		data = i;
		next = n;
	}
	friend ostream &operator<<(ostream &output, const nodeSL<T> &n) {
		output << n.data;
		return output;
	}
	nodeSL& operator=(const nodeSL<T> &obj) {
		data = obj.data;
	}
};
template <class T>
class SLL {
	nodeSL<T> *head, *tail;
	int size;
public:
	// default constructor
	SLL() {
		head = NULL;
		tail = NULL;
		size = 0;
	};
	// destructor
	~SLL() {
		nodeSL<T> *ptr;
		while (head != NULL) {
			ptr = head->next;
			delete head;
			head = ptr;
		}
	}
	// copy constructor
	SLL(const SLL<T> &obj) {
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
		nodeSL<T> *temp = obj.head;
		while (temp != NULL) {
			appendSLL(temp->data);
			temp = temp->next;
		}
	}
	SLL(initializer_list<T> arr) {
		head = NULL;
		tail = NULL;
		size = 0;
		for (T x : arr) {
			appendSLL(x);
		}
	}
	// assignment
	SLL& operator=(const SLL<T> &rhs) {
		if (this != &rhs) {
			this->~SLL();
			this->head = NULL;
			this->tail = NULL;
			this->size = 0;
			nodeSL<T> *ptr = rhs.head;
			while (ptr != NULL) {
				appendSLL(ptr->data);
				ptr = ptr->next;
			}
		}
		return *this;
	}
	SLL& operator=(initializer_list<T> arr) {
		this->~SLL();
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
		for (T x : arr) {
			appendSLL(x);
		}
		return *this;
	}
	void insertAtHead(T n) {
		if (head == NULL) {
			head = tail = new nodeSL<T>(n);
		}
		else {
			head = new nodeSL<T>(n, head);
		}
		size++;
	}
	void insertAtHead(initializer_list<T> arr) {
		int s = arr.size();
		T *a = new T[s];
		int j = 0;
		for (T x : arr) {
			a[j] = x;
			j++;
		}
		for (int i = s - 1; i >= 0; i--) {
			insertAtHead(a[i]);
		}
		delete[] a;
	}
	// insert at tail
	void appendSLL(T n) {
		if (tail != NULL) {
			tail->next = new nodeSL<T>(n);
			tail = tail->next;
		}
		else {
			head = tail = new nodeSL<T>(n);
		}
		size++;
	}
	void appendSLL(initializer_list<T> arr) {
		for (T x : arr) {
			appendSLL(x);
		}
	}
	void insert(T d, int i) {
		if (i == 0) {
			insertAtHead(d);
		}
		else if (i == size) {
			appendSLL(d);
		}
		else {
			nodeSL<T> *temp = new nodeSL<T>(d);
			nodeSL<T> *original = &this->operator[](i);
			nodeSL<T> *prev = &this->operator[](i - 1);
			temp->next = original;
			prev->next = temp;
			size++;
		}
	}
	// insert node at position
	void insertN(nodeSL<T> *n, int i) {
		if (i == 0) {
			nodeSL<T> *original = &this->operator[](i);
			n->next = original;
			head = n;
			size++;
		}
		else if (i == size) {
			tail->next = n;
			n->next = NULL;
			tail = n;
			size++;
		}
		else {
			nodeSL<T> *original = &this->operator[](i);
			nodeSL<T> *prev = &this->operator[](i - 1);
			n->next = original;
			prev->next = n;
			size++;
		}
	}
	void insert(initializer_list<T> arr, int i) {
		if (i == 0) {
			insertAtHead(arr);
		}
		else if (i == size) {
			appendSLL(arr);
		}
		else {
			for (T x : arr) {
				insert(x, i);
				i++;
			}
		}
	}
	void delHead() {
		if (head != NULL) {
			nodeSL<T> *temp = head;
			if (head == tail) {
				head = tail = NULL;
			}
			else {
				head = head->next;
			}
			delete temp;
		}
		size--;
	}
	void delTail() {
		if (head == tail) {
			delete head;
			head = tail = NULL;
		}
		else {
			nodeSL<T> *temp = head;
			while (temp->next != tail) {
				temp = temp->next;
			}
			delete tail;
			tail = temp;
			tail->next = NULL;
		}
		size--;
	}
	void delIn(int i) {
		nodeSL<T> *temp = &this->operator[](i);
		if (i == 0) {
			delHead();
		}
		else if (i == size - 1) {
			delTail();
		}
		else {
			nodeSL<T> *stich = &this->operator[](i - 1);
			stich->next = temp->next;
			delete temp;
			size--;
		}
	}
	// deletes from list but not pointer, store pointer before use
	void delInN(int i) {
		nodeSL<T> *temp = &this->operator[](i);
		if (i == 0) {
			head = head->next;
			temp->next = NULL;
		}
		else if (i == size - 1) {
			nodeSL<T> *prev = &this->operator[](i - 1);
			prev->next = NULL;
			tail = prev;
		}
		else {
			nodeSL<T> *stich = &this->operator[](i - 1);
			stich->next = temp->next;
			temp->next = NULL;
			size--;
		}
	}

	void display() {
		nodeSL<T> *temp = new nodeSL<T>;
		temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	nodeSL<T>& operator[](int x) {
		if (x >= size || x < 0) {
			cout << "ERROR: out of bounds" << endl;
			exit(1);
		}
		nodeSL<T> *temp = head;
		for (int i = 0; i < x; i++) {
			temp = temp->next;
		}
		return *temp;
	}
	bool search(int a) {
		nodeSL<T> *temp;
		int pos = 0;
		for (temp = head; temp != NULL && temp->data != a; temp = temp->next, pos++);
		if (temp != NULL) {
			cout << a << " found at position: " << pos << endl;
		}
		return temp != NULL;
	}
	void reverse() {
		nodeSL<T> *current = head;
		nodeSL<T> *prev = NULL, *next = NULL;
		while (current != NULL) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}
	void swap(int a, int b) {
		nodeSL<T> *nodeA = &this->operator[](a), *nodeB = &this->operator[](b), *temp;
		nodeSL<T> *prevA = NULL, *prevB = NULL;
		if (a >= size || a < 0 || b >= size || b < 0) {
			cout << "ERROR: out of bounds" << endl;
			exit(1);
		}
		if (a == b) {
			return;
		}
		if (a > b) {
			swap(b, a);
			return;
		}
		else {
			if (a == 0) {
				prevB = &this->operator[](b - 1);
				if (a + 1 == b) {
					nodeA->next = nodeB->next;
					nodeB->next = nodeA;
				}
				else {
					temp = nodeA->next;
					prevB->next = nodeA;
					nodeA->next = nodeB->next;
					nodeB->next = temp;
				}
				head = nodeB;
			}
			else {
				prevA = &this->operator[](a - 1); prevB = &this->operator[](b - 1);
				if (a + 1 == b) {
					nodeA->next = nodeB->next;
					nodeB->next = nodeA;
					prevA->next = nodeB;
				}
				else {
					prevA->next = nodeB;
					prevB->next = nodeA;
					temp = nodeA->next;
					nodeA->next = nodeB->next;
					nodeB->next = temp;
				}
			}
			if (b == size - 1) {
				tail = nodeA;
			}
		}
	}
	int getSize() {
		return size;
	}
};

template <class T>
class stack {
	SLL<T> container;
public:
	stack() {
	}
	void push(T x) {
		container.insertAtHead(x);
	}

	T pop() {
		if (container.head == NULL) {
			cout << "Stack Underflow " << endl;
			exit(1);
		}
		T x = container.head->data;
		container.delHead();
		return x;
	}
	int getSize() {
		return container.getSize();
	}
};

class coOrds {
	int x, y;
public:
	coOrds() {
		x = 0;
		y = 0;
	}
	coOrds(int a, int b) : x(a), y(b) {}
	int getx() {
		return x;
	}
	int gety() {
		return y;
	}

	void setcoOrds(int a, int b) {
		x = a;
		y = b;
	}

	friend ostream &operator<<(ostream &output, const coOrds &n) {
		output << "(" << n.getx() << ", " << n.gety() << ")";
		return output;
	}
};

#endif