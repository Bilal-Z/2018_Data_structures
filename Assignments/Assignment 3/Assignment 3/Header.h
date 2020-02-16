#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <iostream>
#include <fstream>
#include "lists.h"
using namespace std;

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

#endif