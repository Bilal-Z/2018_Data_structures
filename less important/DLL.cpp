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
	node *head, * tail;
	public:
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

int main(){
	DLL a;
	a.insertAtHead(1);
	a.insertAtHead(2);
	a.appendDLL(4);
	a.appendDLL(5);
	cout << endl << "A" << endl;
	a.display();
	a.insertDLL(8, 5);
	cout << endl << "A" << endl;
	a.display();
	a.reverse();
	cout << endl << "A" << endl;
	a.display();
	
	DLL b(a);
	cout << endl << "B" << endl;
	b.display();
	
	DLL c;
	c = a;
	cout << endl << "C" << endl;
	c.display();
	
	return 0;
}
