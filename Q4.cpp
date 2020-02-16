#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

class node{
	public:
		int data;
		node *next, *prev;
		
		node(){
			next = NULL;
			prev = NULL;
			data = 0;
		}
		
		node(int i, node *n = NULL, node *p = NULL){
			data = i;
			next = n;
			prev = p;
		}
};

class DLL{
	public:
		node *head, * tail;
		// constructor
		DLL(){
			head = NULL;
			tail = NULL;
		}
		
		// destructor
		~DLL(){
			node *ptr;
			while(head != NULL){
				ptr = head->next;
				delete head;
				head = ptr;
			}
		}
		
		// copy constructor
		DLL(const DLL &obj){
			this->head = NULL;
			this->tail = NULL;
			node *temp = obj.head;
			while(temp != NULL){
				appendDLL(temp->data);
				temp = temp->next;
			}
		}
		
		// assignment
		DLL& operator=(const DLL &rhs){
			if(this != &rhs){
				this->~DLL();
				this->head = NULL;
				this->tail = NULL;
				node *ptr = rhs.head;
				while(ptr != NULL){
					appendDLL(ptr->data);
					ptr = ptr->next;
				}
			}
			return *this;
		}
		
		void insertAtHead(int n){
			if (head == NULL){
				head = tail = new node(n);
			} else {
				head = new node(n, head, NULL);
				head->next->prev = head;
			}
		}
		
		void appendDLL(int n){
			if (tail != NULL){
				tail = new node(n, NULL, tail);
				tail->prev->next = tail;
			} else {
				head = tail = new node(n);
			}
		}
		
		void delHead(){
			if (head != NULL){
				node *temp = head;
				if(head == tail){
					head = tail = NULL;
				} else {
					head = head->next;
				}
				delete temp;
			}
		}
		
		void delTail(){
			if(head == tail){
				delete head;
				head = tail = NULL;
			} else {
				node *temp = head;
				while(temp -> next != tail){
					temp = temp -> next;
				}
				delete tail;
				tail = temp;
				tail->next = NULL;	
			}
		}
		
		void display(){
			node *temp = new node;
			temp = head;
			while (temp != NULL){
				cout << temp->data << endl;
				temp = temp->next;
			}
		}
		
		bool search(int a){
			node *temp;
			for(temp=head; temp!=NULL && temp->data!=a; temp=temp->next);
			return temp!=NULL;
		}
		
		int getSize(){
			node *temp;
			int size = 0;
			for(temp=head; temp!=NULL; temp=temp->next, size++);
		}
		
		void insertDLL(int n, int a) {
			if(head == tail){
				head = tail = new node(n);
			} else {
				node *temp, *place;
				for(temp = head; temp != NULL; temp = temp->next){
					if(temp->data == a){
						place = new node(n, temp->next, temp);
						if(temp->next != NULL){
							temp->next->prev = place;
						} else {
							tail = place;
						}
						temp->next = place;
					}
				}
			}
		}
		
		void reverse(){
			node *temp = NULL;
			node *current = head;
			while (current != NULL){
				temp = current->prev;
				current->prev = current->next;
				current->next = temp;
				current = current->prev;
			}
			if(temp != NULL ) {
			head = temp->prev;
			}
		}
};

class arrDeque{
	int arr[100];
	int front, back, size;
	public:
		arrDeque(){
			front = back = size = 0;
		}
		void addFirst(int x){
			if(size >= 100){
				cout << "deque overflow" << endl;
				return;
			}
			if(size == 0){
				arr[front] = x;
				size = 1;
			}
			else{
				front--;
				if(front == -1){
					front = 99;
				}
				arr[front] = x;
				size++;
			}
		}
		
		void addLast(int x){
			if(size >= 100){
				cout << "deque overflow" << endl;
				return;
			}
			if(size == 0){
				arr[back] = x;
				size = 1;
			}
			else{
				back++;
				if(back == 100){
					back = 0;
				}
				arr[back] = x;
				size++;
			}
		}
		
		void removeFirst(){
			front++;
		}
		
		void removeLast(){
			back--;
		}
		
		int getFirst(){
			return arr[front];
		}
		
		int getLast(){
			return arr[back];
		}
		
		int getsize(){
			return size;
		}
		
		bool isEmpty(){
			return size;
		}
};

class dllDeque{
	DLL lst;
	public:
		void addFirst(int x){
			lst.insertAtHead(x);
		}
		void addLast(int x){
			lst.appendDLL(x);
		}
		
		void removeFirst(){
			lst.delHead();
		}
		
		void removeLast(){
			lst.delTail();
		}
		
		int getFirst(){
			return lst.head->data;
		}
		
		int getLast(){
			return lst.head->data;
		}
		
		int size(){
			return lst.getSize();
		}
		
		bool isEmpty(){
			return lst.getSize();
		}
};

int main(){
	return 0;
}
