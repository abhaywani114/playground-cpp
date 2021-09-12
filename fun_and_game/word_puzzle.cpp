#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
//#include "matrix.h"

using namespace std;

class Puzzle {
	public:
		Puzzle();
		int solvePuzzle() const;

		//for testing
		~Puzzle() {
		}

	private:
		vector<vector<char> > theBoard;
		vector<string> theWords;
		ifstream puzzleStream;
		ifstream wordStream;

		void openFile(const string & message, ifstream & inFile);
		void readPuzzle();
		void readWords();

		int solveDirection( int baseRow, int baseCol,
						int rowDelta, int colDelta) const;
};

// define constructor
Puzzle::Puzzle() { //: theBoard(0,0) {
	openFile( "Enter puzzle file", puzzleStream);
	openFile( "Enter dictionary name", wordStream);

	readWords();
	readPuzzle();
}

// openFile routine
void Puzzle::openFile(const string & message, ifstream & inFile) {
	string name;
	do {
		inFile.clear();
		cout << message << ": ";
		cin >> name;
		inFile.open(name.c_str());
	} while (!inFile);
}

// read words
void Puzzle::readWords() {

	string thisWord;
	int numEntries = 0;
	for(; wordStream >> thisWord; numEntries++) {
		theWords.push_back( thisWord);
		if (numEntries != 0 && theWords[numEntries] < theWords[numEntries-1]) {
			cerr << "Dictonary is not sorted... skipping" << endl;
			continue;
		}
	}
}

// return vector<char> from a string of chars
vector<char> toVec(const string & str) {
	vector<char> v(str.length());
	for (int i = 0; i < str.length(); i++)
		v[i] = str[i];
	return v;
}

void Puzzle::readPuzzle() {
	string oneLine;
	// if file is empty
	if (getline(puzzleStream, oneLine).eof())
		return;

	int columns  = oneLine.length();
	theBoard.push_back( toVec(oneLine));

	while ( ! (getline(puzzleStream, oneLine).eof() )) {
			if ( oneLine.length() != columns)
				cerr << "Puzzle is not rectangular" << endl;
			else
				theBoard.push_back( toVec(oneLine) );
	}
}

int Puzzle::solvePuzzle() const {
	int match = 0;
	for (int r = 0; r < theBoard.size(); r++)
		for(int c = 0; c < theBoard[r].size(); c++)
			for (int rd = -1; rd <= 1; rd++)
				for (int cd = -1; cd <= 1; cd++) 
					if (rd != 0 || cd != 0)
						match += solveDirection(r, c, rd, cd);
	return match;
}

// return true if prefix is a prefix of a word
bool isPrefix( const string & prefix, const string & word) { 
	if (word.length() < prefix.length())
		return false;
	
	for (int i = 0; i < prefix.length(); i++)
		if (prefix[i] != word[i])
			return false;
	
	return true;
}

// Search the grid from a string point and direction
int Puzzle::solveDirection(int baseRow, int baseCol,
		int rowDelta, int colDeta) const {
	string word;
	int numMatches = 0;
	
	word = theBoard[baseRow][baseCol];

	for (int i = baseRow + rowDelta, j = baseCol + colDeta;
			i >= 0 && j >= 0 && i < theBoard.size() &&
							j < theBoard[i].size();
			i += rowDelta, j += colDeta) {

		word += theBoard[i][j];

		vector<string>::const_iterator itr;
		itr = lower_bound( theWords.begin(), theWords.end(), word);

		if (itr == theWords.end() || !isPrefix(word, *itr))
			break;

		if (*itr == word) {
			numMatches ++;
			cout << "Found " << word << " at (" << baseRow << "," << baseCol << ") to (" <<
				i  << "," << j  << ")" << endl;
		}

	}

	return numMatches;
}

int main() {
	Puzzle p1;
	cout << "Solve puzzle: " << endl; 
	p1.solvePuzzle();

	return 0;
}
