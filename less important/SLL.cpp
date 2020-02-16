#include <iostream>
#include <cstdlib>
#include <cstring> 
using namespace std;

class node{
	public:
		int data;
		node *next;
		
		node(){
			next = NULL;
			data = 0;
		}
		
		node(int i, node *n = NULL){
			data = i;
			next = n;
		}
};

class SLL{
	node *head, *tail;
	public:
		// default constructor
		SLL(){
			head=NULL;
			tail=NULL;
		};
		
		// destructor
		~SLL(){
			node *ptr;
			while(head != NULL){
				ptr = head->next;
				delete head;
				head = ptr;
			}
		}
		
		// copy constructor
		SLL(const SLL &obj){
			this->head = NULL;
			this->tail = NULL;
			node *temp = obj.head;
			while(temp != NULL){
				appendSLL(temp->data);
				temp = temp->next;
			}
		}
		
		// assignment
		SLL& operator=(const SLL &rhs){
			if(this != &rhs){
				this->~SLL();
				this->head = NULL;
				this->tail = NULL;
				node *ptr = rhs.head;
				while(ptr != NULL){
					appendSLL(ptr->data);
					ptr = ptr->next;
				}
			}
			return *this;
		}
		
		void insertAtHead(int n){
			if(head == NULL){
				head = tail = new node(n);
			} else{
				head = new node(n, head);
			}
		}
		
		// insert at tail
		void appendSLL(int n){
			if(tail != NULL){
				tail->next = new node(n);
				tail = tail->next;
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
		
		void reverse(){
			node *current = head;
			node *prev = NULL, *next = NULL;
			while (current != NULL) {
				next = current->next;
				current->next = prev;
				prev = current;
				current = next;
			}
			head = prev;
		}
		
};

int main(){
	SLL a;
	a.insertAtHead(1);
	a.insertAtHead(2);
	a.appendSLL(4);
	a.appendSLL(5);
	cout << endl << "A" << endl;
	a.display();
	a.delTail();
	cout << endl << "A" << endl;
	a.display();
	a.delHead();
	cout << endl << "A" << endl;
	a.display();
	a.reverse();
	cout << endl << "A" << endl;
	a.display();
	
	cout << endl << "B" << endl;
	SLL b(a);
	b.display();
	
	
	SLL c;
	c.insertAtHead(6);
	c.insertAtHead(7);
	cout << endl << "C" << endl;
	c.display();
	c = a;
	cout << endl << "C" << endl;
	c.display();
	
	cout << endl << "SEARCH RESULT" << endl;
	cout << c.search(9) << endl;
	
	return 0;
}
