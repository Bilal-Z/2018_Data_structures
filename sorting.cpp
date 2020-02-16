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
			return lst.tail->data;
		}
		
		int size(){
			return lst.getSize();
		}
		
		bool isEmpty(){
			return lst.getSize();
		}
};