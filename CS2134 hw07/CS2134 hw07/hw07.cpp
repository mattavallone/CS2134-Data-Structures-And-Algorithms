//Mathew Avallone
//hw07

#include <string>
#include <fstream>
#include <iostream>
#include "Tokenizer.cpp"
#include <stack>
using namespace std;

struct Symbol
{
	char token;
	int  theLine;
	Symbol() {}
	Symbol(char tok, int line) : token(tok), theLine(line) {}
};

class Balance
{
public:
	Balance(istream & is) :tok(is), errors(0) {}

	int checkBalance() {
		int errorCount = 0;
		stack<char> bal;
		char ch = tok.getNextOpenClose();
		while (ch != '\0') {
				if (ch == '(' || ch == '[' || ch == '{') {
					bal.push(ch);
				}
				else if (ch == ')' || ch == ']' || ch == '}') {
					Symbol oParen(bal.top(), tok.getLineNumber());
					Symbol cParen(ch, tok.getLineNumber());

					if (bal.empty()) {//if a close parenthese has no open parentheses on the stack
						++errorCount;
						cerr << "No matching open parenthese at line " << tok.getLineNumber() << endl;
					}
					else if (!checkMatch(oParen, cParen)) {
						++errorCount;
					}
					else 
						bal.pop();
				}
			ch = tok.getNextOpenClose();
		}

		if (!bal.empty()) { //if endOfFile is reached but the stack is not empty
			++errorCount;
			cerr << "End of File reached but open parenthese not matched with closed" << endl;
		}
		return errorCount;
	}// returns the number of mismatched parenthesis
private:
	Tokenizer tok;
	int errors;
	bool checkMatch(const Symbol& oParen, const Symbol& cParen) {
		if ((int)oParen.token + 1 != (int)cParen.token && (int)oParen.token + 2 != (int)cParen.token) { //checks ANSCII values for parentheses (they're adjacent values or off by 2 values on ANSCII table)
			cerr << "Error at line " << cParen.theLine << endl;
			return false;
		}
		return true;
	}
	
};

int main() {
	ifstream someCode("code.txt");
	Balance checkSomeCode(someCode);
	cout << "checkBalance() " << checkSomeCode.checkBalance() << endl;
}