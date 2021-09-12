#include<iostream>
#include<list>

using namespace std;

int josephus(int people, int passes) {
	list<int> theList;
	list<int>::iterator itr, next;
	int i;

	//construct list
	for(i = 1; i <= people; i++)
		theList.push_back(i);

	for(itr = theList.begin(); people-- != 1; itr = next) {
		for (int i =0; i < passes; i++) {
			++itr;
			if (itr == theList.end())
				itr = theList.begin();
		}

		next = itr;
		++next;
		cout << "Player " << *itr << " is eleminated" << endl;
		theList.erase(itr);
		if (next == theList.end())
			next = theList.begin();
	}
	
	cout << "The winner player is: " <<  *itr << endl;
	return *itr;
}

int main() {
	int people, passes;
	cout << "Enter people and passes: ";
	cin >> people;
	cin >> passes;
	josephus(people, passes);

	return 0;
}
