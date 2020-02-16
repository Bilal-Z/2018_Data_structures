#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

//singly linked list & related functions
template <class T>
class nodeSL {
public:
	T data;
	nodeSL<T> *next;

	nodeSL() {
		next = NULL;
		//data = 0;
	}

	nodeSL(T i, nodeSL<T> *n = NULL) {
		data = i;
		next = n;
	}
	friend ostream &operator<<(ostream &output, const nodeSL<T> &n) {
		output << n.data;
		return output;
	}
};
template <class T>
class SLL {
	nodeSL<T> *head, *tail;
	int size;
	void split(nodeSL<T> *h, nodeSL<T> **front, nodeSL<T> **back) {
		if (h == NULL) {
			return;
		}
		nodeSL<T> *fast = h->next, *slow = h;
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = h;
		*back = slow->next;
		slow->next = NULL;
	}
	nodeSL<T>* merge(nodeSL<T> *a, nodeSL<T> *b) {
		nodeSL<T> *res;
		if (a == NULL) {
			return b;
		}
		else if (b == NULL) {
			return a;
		}

		if (a->data <= b->data) {
			res = a;
			res->next = merge(a->next, b);
		}
		else {
			res = b;
			res->next = merge(a, b->next);
		}

		return res;
	}
	void mergeSort(nodeSL<T> **headRef) {
		nodeSL<T> *a, *b, *mhead = *headRef;
		if (mhead == NULL || mhead->next == NULL) {
			return;
		}

		split(mhead, &a, &b);
		mergeSort(&a);
		mergeSort(&b);

		*headRef = merge(a, b);
	}
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
		nodeSL<T> *temp;
		temp = head;
		while (temp != NULL) {
			cout << temp->data << ", ";
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
	int search(T a) {
		nodeSL<T> *temp;
		int pos = 0;
		for (temp = head; temp != NULL && temp->data != a; temp = temp->next, pos++);
		if (temp != NULL) {
			return pos;
		}
		return -1;
	}

	bool existsIn(T a) {
		nodeSL<T> *temp;
		int pos = 0;
		for (temp = head; temp != NULL && temp->data != a; temp = temp->next, pos++);
		if (temp != NULL) {
			return true;
		}
		return false;
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
		if (a > b) {
			swap(b, a);
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

	void sort() {
		mergeSort(&head);
		nodeSL<T> *temp = head;
		if (temp != NULL) {
			while (temp->next != NULL) {
				temp = temp->next;
			}
			tail = temp;
		}
		else {
			tail = NULL;
		}
	}

};

template <class T>
void selectSort(SLL<T> &obj) {
	int j, swapIndex;
	for (int i = 0; i < obj.getSize() - 1; i++) {
		swapIndex = i;
		for (j = i + 1; j < obj.getSize(); j++) {
			if (obj[j].data <obj[swapIndex].data) {
				swapIndex = j;
			}
		}
		obj.swap(i, swapIndex);
	}
}

template <class T>
void bubbleSort(SLL<T> &obj) {
	int i, j = 1;
	bool swapped = true;
	while (swapped) {
		swapped = false;
		for (i = 0; i < obj.getSize() - j; i++) {
			if (obj[i].data > obj[i + 1].data) {
				obj.swap(i, i + 1);
				swapped = true;
			}
		}
		j++;
	}
}

int getGap(int g)
{
	g = (g * 10) / 13;

	if (g < 1)
		return 1;
	return g;
}

template <class T>
void combSort(SLL<T> &obj) {
	int i, gap = obj.getSize();
	bool swapped = true;
	while (gap != 1 || swapped) {
		gap = getGap(gap);
		swapped = false;
		for (i = 0; i < obj.getSize() - gap; i++) {
			if (obj[i].data > obj[i + gap].data) {
				obj.swap(i, i + gap);
				swapped = true;
			}
		}
	}
}

template <class T>
void insertionSort(SLL<T> &obj) {
	nodeSL<T> *key;
	int j, n = obj.getSize();
	for (int i = 1; i < n; i++) {
		key = &obj[i];
		obj.delInN(i);
		j = i - 1;
		while (j >= 0 && obj[j].data > key->data) {
			j--;
		}
		obj.insertN(key, j + 1);
	}

}

template <class T>
void insertionSort2(SLL<T> &obj) {
	T key;
	int j, n = obj.getSize();
	for (int i = 1; i < n; i++) {
		key = obj[i].data;
		obj.delIn(i);
		j = i - 1;
		while (j >= 0 && obj[j].data > key) {
			j--;
		}
		obj.insert(key, j + 1);
	}

}

template <class T>
void shellSort(SLL<T> &obj) {
	int i, n = obj.getSize(), j;
	nodeSL<T> *key;
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			key = &obj[i];
			for (j = i; j >= gap && obj[j - gap].data > key->data; j -= gap) {
				obj.swap(j - gap, j);
			}
		}
	}
}

template <class T>
void shellSort2(SLL<T> &obj) {
	int i, n = obj.getSize(), j;
	T key, jk;
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			key = obj[i].data;
			for (j = i; j >= gap && obj[j - gap].data > key; j -= gap) {
				obj.delIn(j);
				obj.insert(obj[j - gap].data, j);
			}
			obj.delIn(j);
			obj.insert(key, j);
		}
	}
}

// stack, binary search tree & related classes & functions
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
		if (container.getSize() == 0) {
			cout << "Stack Underflow " << endl;
			exit(1);
		}
		T x = container[0].data;
		container.delHead();
		return x;
	}
	bool isEmpty() {
		if (container.getSize() == 0) {
			return true;
		}
		return false;
	}
};

template <class T>
class tNode {
public:
	T data;
	tNode<T> *left;
	tNode<T> *right;
	tNode() {
		data = 0;
		left = NULL;
		right = NULL;
	}
	tNode(T d, tNode<T> *l = NULL, tNode<T> *r = NULL) {
		data = d;
		left = l;
		right = r;
	}
};

template <class T>
class BST {
	tNode<T> *root;
public:
	BST() {
		root = NULL;
	}
	void insertNode(T d) {
		if (root == NULL) {
			root = new tNode<T>(d);
			return;
		}
		tNode<T> *temp = root;
		while (true) {
			if (temp->data > d) {
				if (temp->right == NULL) {
					temp->right = new tNode<T>(d);
					return;
				}
				temp = temp->right;
			}
			else if (d == temp->data) {
				return;
			}
			else {
				if (temp->left == NULL) {
					temp->left = new tNode<T>(d);
					return;
				}
				temp = temp->left;
			}
		}
	}

	void insertNode(tNode<T>* n) {
		if (root == NULL) {
			root = n;
			return;
		}
		tNode<T> *temp = root;
		while (true) {
			if (n->data > temp->data) {
				if (temp->right == NULL) {
					temp->right = n;
					return;
				}
				temp = temp->right;
			}
			else if (n->data == temp->data) {
				return;
			}
			else {
				if (temp->left == NULL) {
					temp->left = n;
					return;
				}
				temp = temp->left;
			}
		}
	}

	void deleteNode(T d) {
		tNode<T> *Ltemp, *Rtemp, *delNode, *parent = root;
		SLL<T> lst = inorder();
		bool left = false, right = false, isRoot = false;
		delNode = search(d);
		if (delNode == root) {
			isRoot = true;
		}
		Ltemp = delNode->left;
		Rtemp = delNode->right;
		// find parent
		while (true && !isRoot) {
			if (parent->left->data == d) {
				break;
			}
			if (parent->right->data == d) {
				break;
			}
			if (d < parent->data) {
				parent = parent->left;
			}
			else if (d > parent->data) {
				parent = parent->right;
			}
		}

		if (parent->left->data == d) {
			left = true;
		}
		else if (parent->right->data == d) {
			right = true;
		}

		delete delNode;
		if (left) {
			parent->left = NULL;
		}
		if (right) {
			parent->right = NULL;
		}
		if (Ltemp != NULL && Rtemp == NULL) {
			if (isRoot) {
				isRoot = Ltemp;
			}
			else {
				insertNode(Ltemp);
			}
		}
		else if (Ltemp == NULL && Rtemp != NULL) {
			if (isRoot) {
				isRoot = Rtemp;
			}
			else {
				insertNode(Rtemp);
			}
		}

		else if (Ltemp != NULL && Rtemp != NULL) {
			T next = lst[lst.search(d) + 1].data;
			tNode<T> *nextN = Rtemp;
			//get replacement;
			while (nextN != NULL) {
				if (next == nextN->data) {
					break;
				}
				else if (next < nextN->data) {
					nextN = nextN->left;
				}
				else {
					nextN = nextN->right;
				}
			}
			// find parent of nextin inorder
			parent = Rtemp;
			while (true) {
				if (parent->left->data == next) {
					break;
				}
				if (parent->right->data == next) {
					break;
				}
				if (next < parent->data) {
					parent = parent->left;
				}
				else if (next > parent->data) {
					parent = parent->right;
				}
			}
			left = false;
			right = false;
			if (parent->left->data == next) {
				left = true;
			}
			else if (parent->right->data == next) {
				right = true;
			}

			if (left) {
				parent->left = NULL;
			}
			if (right) {
				parent->right = NULL;
			}
			nextN->left = Ltemp;
			nextN->right = Rtemp;
			if (isRoot) {
				root = nextN;
			}
		}
	}

	tNode<T>* search(T d) {
		tNode<T> *temp = root;
		while (temp != NULL) {
			if (d == temp->data) {
				return temp;
			}
			else if (d < temp->data) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		return NULL;

	}

	void printMaxBranch() {
		tNode<T> *temp = root;
		while (temp != NULL) {
			cout << temp->data << endl;
			temp = temp->right;
		}
	}

	SLL<T> maxBranch() {
		SLL<T> lst;
		tNode<T> *temp = root;
		while (temp != NULL) {
			lst.appendSLL(temp->data);
			temp = temp->right;
		}
		return lst;
	}

	SLL<T> inorder() {
		stack<tNode<T>*> s;
		SLL<T> in;
		tNode<T> *temp, *current = root;
		while (true) {
			while (current != NULL) {
				s.push(current);
				current = current->left;
			}
			if (!s.isEmpty()) {
				temp = s.pop();
				in.appendSLL(temp->data);
				current = temp->right;
			}
			if (current == NULL && s.isEmpty()) {
				return in;
			}
		}

	}

	void inorderPrint() {
		stack<tNode<T>*> s;
		tNode<T> *temp, *current = root;
		while (true) {
			while (current != NULL) {
				s.push(current);
				current = current->left;
			}
			if (!s.isEmpty()) {
				temp = s.pop();
				cout << temp->data << " ";
				current = temp->right;
			}
			if (current == NULL && s.isEmpty()) {
				cout << endl;
				return;
			}
		}

	}

	T findMin() {
		tNode<T> *temp = root;
		while (temp->left != NULL) {
			temp = temp->left;
		}
		return temp->data;
	}

	T findMax() {
		tNode<T> *temp = root;
		while (temp->right != NULL) {
			temp = temp->right;
		}
		return temp->data;
	}

	int getSize() {

	}

	int getLevels() {

	}
};

//--------------------------------------------------------------------



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
