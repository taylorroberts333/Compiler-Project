#ifndef SCANNER

#define SCANNER



#include <iostream>
#include <fstream>
using namespace std;

enum TokenType{ERROR, LBRACE, RBRACE, EOL, IDEN, CONSTANT, PLUS, MINUS, EQL, EE, LPAREN, RPAREN, GR,GRE,MULTIPLY,DIVIDE,MOD, COMMA,DOT,AND,OR, POW ,NONE /*this is for if the file is empty*/};

class Scanner
{
public:
	Scanner(string filename);

	TokenType currentTokenType();
	TokenType nextTokenType();
	string currentTokenString();
	string nextTokenString();

	void advance();

	string toString(TokenType t);

	int getLine();
private:
	ifstream filestream;
	string currents;
	string nexts;
	TokenType currenttt;
	TokenType nexttt;

	int linenext;
	int linecurrent;
};

#endif // !