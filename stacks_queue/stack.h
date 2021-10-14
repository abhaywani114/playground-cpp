#ifndef STACK_H
	#define STACK_H
#include<vector>
#include<string>

std::string UnderflowException() {
	return ("Stack is Empty");
}
template<class Obj>
class Stack {
	public:
		Stack();
		
		bool isEmpty() const;
		void makeEmpty();

		void pop();
		void push(const Obj & x);

		const Obj & top() const;	
		Obj topAndPop();

		void operator= (std::initializer_list<Obj> arr ) {
			for(auto i:arr)
				push(i);
		}

	private:
		std::vector<Obj> theArray;
		int			tos;
};

template<class Obj>
Stack<Obj>::Stack() : theArray(1) {
	tos = -1;
}

template<class Obj>
bool Stack<Obj>::isEmpty() const {
	return tos == -1;
}

template<class Obj>
void Stack<Obj>::makeEmpty(){
	tos = -1;
}

template<class Obj>
void Stack<Obj>::pop() {
	if (isEmpty())
		throw UnderflowException();
	tos--;
}


template<class Obj>
void Stack<Obj>::push( const Obj & x ) {

	if (tos == (theArray.size()-1) ) 
		theArray.resize(theArray.size() * 2 + 1 );

	theArray[++tos] = x; 
}


template<class Obj>
const Obj & Stack<Obj>::top() const {
	if (isEmpty())
		throw UnderflowException();

	return theArray[tos];
}


template<class Obj>
Obj Stack<Obj>::topAndPop() {
	if (isEmpty())
		throw UnderflowException();

	return theArray[tos--];
}
#endif
