#include<iostream>
#include "compressor.h"

/*
 * BUG: compreessor class has 4 bugs related to file opening
 *
*/

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " -cu files" << endl;
		return 1;
	}
	
	string option = argv[1];
	for (int i = 2; i < argc; i++) {
		string nextFile = argv[i];
		if (option == "-c")
			Compressor::compress(nextFile);
		else if (option == "-u")
			Compressor::uncompress(nextFile);
		else {	
			cerr << "Invalid option provided" << endl;
			return 1;
		}
	}
	
	return 0;
}
