#include "queue.h"

int main() {
	Queue<int> q1;

	q1.status();

	q1 = {1,2,3,4,5};
	q1.status();

	q1.dequeue();
	q1.status();

	q1 = {7, 8,10,11,23,45,66,78};
	q1.status();

	
	return 0;
}
