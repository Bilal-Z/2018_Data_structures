#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
using namespace std;

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
			if (d < temp->data) {
				if (temp->left == NULL) {
					temp->left = new tNode<T>(d);
					return;
				}
				temp = temp->left;
			}
			else if (d > temp->data) {
				if (temp->right == NULL) {
					temp->right = new tNode<T>(d);
					return;
				}
				temp = temp->right;
			}
			else {
				return;
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
			if (n->data < temp->data) {
				if (temp->left == NULL) {
					temp->left = n;
					return;
				}
				temp = temp->left;
			}
			else if (n->data > temp->data) {
				if (temp->right == NULL) {
					temp->right = n;
					return;
				}
				temp = temp->right;
			}
			else {
				return;
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
		else if(parent->right->data == d) {
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
				root = Ltemp;
			}
			else {
				insertNode(Ltemp);
			}
		}
		else if (Ltemp == NULL && Rtemp != NULL) {
			if (isRoot) {
				root = Rtemp;
			}
			else {
				insertNode(Rtemp);
			}
		}

		else if (Ltemp != NULL && Rtemp != NULL) {
			T next = lst[lst.search(d) + 1 ].data;
			tNode<T> *nextN = Rtemp, *nextPar;
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
			if (nextN == Rtemp) {
				nextN->left = Ltemp;
			}
			else {
				// find parent of nextin inorder
				nextPar = Rtemp;
				while (true) {
					if (nextPar->left->data == next) {
						break;
					}
					if (nextPar->right->data == next) {
						break;
					}
					if (next < nextPar->data) {
						nextPar = nextPar->left;
					}
					else if (next > nextPar->data) {
						nextPar = nextPar->right;
					}
				}
				left = false;
				right = false;
				if (nextPar->left->data == next) {
					left = true;
				}
				else if (nextPar->right->data == next) {
					right = true;
				}

				if (left) {
					nextPar->left = NULL;
				}
				if (right) {
					nextPar->right = NULL;
				}
				nextN->left = Ltemp;
				nextN->right = Rtemp;
			}
			if (isRoot) {
				root = nextN;
			}
			else {
				insertNode(nextN);
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
		cout << "root: " << root->data << endl;
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


int main() {

	BST<int> tr;
	tr.insertNode(50);
	tr.insertNode(30);
	tr.insertNode(70);
	tr.insertNode(60);
	tr.insertNode(80);
	tr.insertNode(20);
	tr.insertNode(40);

	tr.inorderPrint();
	tr.deleteNode(30);
	tr.inorderPrint();
	tr.deleteNode(50);
	tr.inorderPrint();
	tr.deleteNode(20);
	tr.inorderPrint();



	return 0;
}
