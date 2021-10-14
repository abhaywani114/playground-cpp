#include "stack.h"
#include<iostream>
#include<typeinfo>

using namespace std;

int main() {
	Stack<int>  myStack;
	myStack = {1,2,7};
	cout << myStack.top()  << endl;
	cout << "pop:"   << endl; 
	myStack.pop();
	cout << myStack.top()  << endl;
	return 0;
}
