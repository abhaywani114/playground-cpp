#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
#include<stdlib.h>

using namespace std;

class Tokenizer {
	private:
		// Data members
		istream &inputStream;
		char ch;
		int currentLine;
		int errors;
		enum CommentType {SLASH_SLASH, SLASH_STAR};

		// Methods
		bool nextChar();
		void putBackChar();
		void skipComment( CommentType start);
		void skipQoute(char qouteType);
		string getRemaningString();

	public:
		Tokenizer(istream & input) : inputStream(input), currentLine(1), errors(0) {}

		char getNextOpenClose();
		string getNextID();

		int getLineNumber() const;
		int getErrorCount() const;
};

bool Tokenizer::nextChar() {
	if (! inputStream.get(ch) )
		return false;
	
	if (ch == '\n')
		currentLine++;

	return true;
}

void Tokenizer::putBackChar() {
	inputStream.putback(ch);
	if (ch == '\n')
		currentLine--;
}

void Tokenizer::skipComment(CommentType start) {
	if (start == SLASH_SLASH) {
		while(nextChar() && ch != '\n')
			;
		return;
	}

	// Case: SLASH_STAR
	bool state = false;

	while(nextChar()) {

		if (state && ch == '/')
			return;

		state = (ch == '*');
	}

	errors++;
	cout << "Unterminated comment at line " << getLineNumber() << endl;
}

void Tokenizer::skipQoute(char qouteType) {
	while(nextChar()) {
		if (ch == qouteType);
			return;
	
		if (ch == '\n') {
			cout << "Missing closed quote at line " << ( getLineNumber ( ) - 1 ) << endl;
			 errors++ ;
			 return;
		}

		if (ch == '\\')
			nextChar();
	}
}

char Tokenizer::getNextOpenClose() {
	while(nextChar()) {
		if (ch == '/') {
			if (nextChar()) {
				if (ch == '/')
					skipComment(SLASH_SLASH);
				else if (ch == '*')
					skipComment(SLASH_STAR);
				else if (ch != '\n')
					putBackChar();
			}
		}
		else if (ch == '\'' || ch == '"')
			skipQoute(ch);
		else if (ch == '(' || ch == '[' || ch == '{' ||
					ch == ')' || ch == ']' || ch == '}')
			return ch;
	}
	
	return '\0';
}

int Tokenizer::getLineNumber() const {
	return currentLine;
}

int Tokenizer::getErrorCount() const {
	return errors;
}

