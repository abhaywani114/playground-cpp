#include "Tokenizer.h"
using namespace std;

struct Symbol {
	char token;
	int theLine;
};

class Balance {
	private:
		Tokenizer tok;
		int error;
		void checkMatch(const Symbol & opSym, const Symbol & clSym);
	public:
		Balance (istream & input) : tok(input), error(0) {};
		int checkBalance();
};
void Balance::checkMatch(const Symbol & opSym, const Symbol & clSym) {
	//cout << "checkMatch(): " << opSym.token << " VS " << clSym.token << endl;
	if ((opSym.token == '(' && clSym.token != ')') ||
		(opSym.token == '{' && clSym.token != '}') ||
		(opSym.token == '[' && clSym.token != ']') ) {
		
		cout << "Found: " << opSym.token << " at line " << opSym.theLine 
			<< " doesn't match with closing " << clSym.token << " at line " << clSym.theLine << endl;
		error++;
	}
}

 
int Balance::checkBalance() {
	char ch;
	Symbol last_symbol, match;
	stack<Symbol, vector<Symbol> > pendingTokens;
	
	while( (ch = tok.getNextOpenClose()) != '\0' ) {
		last_symbol.token = ch;
		last_symbol.theLine = tok.getLineNumber();
		
		switch (ch) {
			case '(':
			case '[':
			case '{':
				pendingTokens.push(last_symbol);
				break;
			case ')':
			case  '}':
			case ']':
				if (pendingTokens.empty()) {
					 cout << "Extraneous " << ch << " at line " << tok.getLineNumber( ) << endl;
					 error++;
				} else {

					match = pendingTokens.top();
					pendingTokens.pop();
					checkMatch(match, last_symbol);
				}
			
				break;
		};
	}

	while ( !pendingTokens.empty()) {
		match = pendingTokens.top();
		pendingTokens.pop();
		cout << "Unmatched token: " << match.token << " at line " << match.theLine << endl;
		error++;
	}

	return error + tok.getErrorCount();
}

int main(int argc, char **argv) {
	if (argc == 1) {
		Balance p(cin);
		if (p.checkBalance() == 0)
			cout << "No error found" << endl;
	}	else {
		while( --argc ) {
			ifstream ifp(*++argv);
			if (!ifp) {
				cerr << "Cannot open " << *argv << endl;
				continue;
			}

			cout << *argv << " : " << endl;
			Balance p ( ifp ) ;
			if (p.checkBalance() == 0)
				cout << "No error found" << endl;
		}
	}

	return 0;
}
