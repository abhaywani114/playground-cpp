#ifndef CHAR_COUNTER_CLASS
#define CHAR_COUNTER_CLASS
#include<iostream>
#include<map>

using namespace std;

class charCounter {
	private:
		map<char, int, less<int> > theCount;
	
	public:
		charCounter();
		charCounter(istream & input);

		int getCount(char ch);
		void setCount(char ch, int val);
		~charCounter() {
			#ifdef DEBUG
			map<char, int, less<int> >::iterator itr;
			for(itr = theCount.begin(); itr != theCount.end(); itr++)
				cout << "DEBUG: charCounter()" << itr->first << " -> " << itr->second << endl;
			#endif
		}
};

charCounter::charCounter() {}
charCounter::charCounter(istream & input) {
	char ch;
	while(!input.get(ch).eof())
		theCount[ch]++;
}

int charCounter::getCount(char ch) {
	map<char, int, less<int> >::const_iterator itr;
	itr = theCount.find(ch);
	return (itr != theCount.end()) ? (*itr).second:0;
}

void charCounter::setCount(char ch, int val) {
	theCount[ch] = val;
}

#endif
