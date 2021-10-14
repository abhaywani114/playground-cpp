#ifndef QUEUE_H
	#define QUEUE_H
#include<iostream>
#include<vector>
#include<string>

#define OBJ_TEMP template<typename Obj>
#define endl std::endl
std::string UnderflowException() {
	return ("Queue is empty");
}

OBJ_TEMP
class Queue {
	private:
		std::vector<Obj>	theArray;
		int					front, back, currentSize;
		void				increment(int & x) const;
		void				doubleQueue();
	
	public:
		Queue();
	
		bool isEmpty() const;
		const Obj & getFront() const;
		
		void makeEmpty();
		Obj dequeue();
		void enqueue(const Obj & x);

		void operator= (std::initializer_list<Obj> arr) {
			std::cout << "Enqueueing" << endl;
			for(auto i:arr)
				enqueue(i);
		}

		void status() {
			try {
				std::cout << "front: " << front << endl;
				std::cout << "back: " << back << endl;
				std::cout << "current size: " << currentSize << endl;
				std::cout << "getFront: " << getFront() << endl;
			} catch (std::string e) {
				std::cout << e << endl;
			}	

			std::cout << endl << endl;
		}
};

OBJ_TEMP
void Queue<Obj>::increment(int & x) const {
	if (++x == theArray.size())
		x = 0;
}

OBJ_TEMP
void Queue<Obj>::doubleQueue() {
	std::cout << "doubleQueue()" << endl;
	theArray.resize( theArray.size() * 2 + 1);
		
	if (front != 0) {
		for (int i = 0; i < front; i++)
			theArray[i + currentSize] = theArray[i];

		back += currentSize;
	}
}

OBJ_TEMP
Queue<Obj>::Queue() : theArray(1) {
	makeEmpty();
}

OBJ_TEMP
bool Queue<Obj>::isEmpty() const{
	return currentSize == 0;
}

OBJ_TEMP
void Queue<Obj>::makeEmpty() {
	currentSize = 0;
	front = 0;
	back = theArray.size() - 1;
}

OBJ_TEMP
Obj Queue<Obj>::dequeue() {
	if (isEmpty())
		throw UnderflowException();

	currentSize--;
	Obj frontItem = theArray[front];
	increment(front);

	return frontItem;
}

OBJ_TEMP
const Obj & Queue<Obj>::getFront() const {
	if (isEmpty())
		throw UnderflowException();

	return theArray[front];
}

OBJ_TEMP
void Queue<Obj>::enqueue(const Obj & x) {

	if (currentSize == theArray.size())
		doubleQueue();

	increment(back);
	theArray[back] = x;

	currentSize++;

}
#endif
