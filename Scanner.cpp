#include "Scanner.h"

#include <string>
using namespace std;

string Scanner::toString(TokenType t)
{
	if (t == NONE)
		return "NONE";
	if (t == PLUS)
		return "PLUS";
	if (t == MINUS)
		return "MINUS";
	if (t == EQL)
		return "EQL";
	if (t == LPAREN)
		return "LPAREN";
	if (t == RPAREN)
		return "RPAREN";
	if (t == LBRACE)
		return "LBRACE";
	if (t == RBRACE)
		return "RBRACE";
	if (t == CONSTANT)
		return "CONSTANT";
	if (t == EOL)
		return "EOL";
	if (t == EE)
		return "EE";
	if (t == GR)
		return "GR";
	if (t == GRE)
		return "GRE";
	if (t == MULTIPLY)
		return "MULTIPLY";
	if (t == DIVIDE)
		return "DIVIDE";
	if (t == MOD)
		return "MOD";
	if (t == COMMA)
		return "COMMA";
	if (t == DOT)
		return "DOT";
	if (t == AND)
		return "AND";
	if (t == OR)
		return "OR";
	if (t == POW)
		return "POW";
	if (t == IDEN)
		return "IDEN";
	if (t == ERROR)
		return "error: ";
	return "ERROR in tostring";
}

string Scanner::currentTokenString()
{
	return currents;
}

string Scanner::nextTokenString()
{
	return nexts;
}

TokenType Scanner::currentTokenType()
{
	return currenttt;
}

TokenType Scanner::nextTokenType()
{
	return nexttt;
}

Scanner::Scanner(string fname)
{
	filestream.open(fname);

	linenext = 1;

	

	if (!filestream.good())
	{
		cout << "Could not open file: "<< fname<<"\n";
		return;
	}

	
	advance(); //fill up first slot
	advance(); //fill up second slot

	/*while (currentTokenType() != NONE)
	{
		cout << toString(currentTokenType()) << " " << currentTokenString() << "\n";
		advance();
	}*/
}


void addToBuffer(string & buf, ifstream & stream)
{
	int next = stream.get();

	if (next == -1)
	{
		buf = buf + (char)0; //null signifies eof for today!
	}
	else
	{
		buf = buf + (char)next;
	}

}


void removeFromBuffer(string & buf, ifstream & stream)
{
	char last = buf.back();
	stream.putback(last);
	buf = buf.substr(0, buf.size() - 1);
	
}


bool isNum(char test)
{
	return (test == '0' || test == '1' || test == '2' || test == '3' || test == '4' || test == '5' || test == '6' || test == '7' || test == '8' || test == '9');
}

bool isLowerCharacter(char test)
{
	return (test == 'a' || test == 'b' || test == 'c' || test == 'd' ||
		test == 'e' || test == 'f' || test == 'g' || test == 'h' ||
		test == 'i' || test == 'j' || test == 'k' || test == 'l' ||
		test == 'm' || test == 'n' || test == 'o' || test == 'p' ||
		test == 'q' || test == 'r' || test == 's' || test == 't' ||
		test == 'u' || test == 'v' || test == 'w' || test == 'x' || test == 'y' || test == 'z' || test == '_');
}

bool isUpperCharacter(char test)
{
	return (test == 'A' || test == 'B' || test == 'C' || test == 'D' ||
		test == 'E' || test == 'F' || test == 'G' || test == 'H' ||
		test == 'I' || test == 'J' || test == 'K' || test == 'L' ||
		test == 'M' || test == 'N' || test == 'O' || test == 'P' ||
		test == 'Q' || test == 'R' || test == 'S' || test == 'T' ||
		test == 'U' || test == 'V' || test == 'W' || test == 'X' || test == 'Y' || test == 'Z');
}

bool isWhiteSpace(char test)
{
	return (test == ' ' || test == '\t' || test == '\n');
}




//advance places whatever is in the next variables into the current variables and finds what the next variables are supposed to be
void Scanner::advance()
{
	currents = nexts;
	currenttt = nexttt;
	linecurrent = linenext;

	string buffer;

	bool start = true;
	while (start)
	{
		start = false;

		buffer = "";

		addToBuffer(buffer, filestream);

		if (buffer[0] == '{')
		{
			nexttt = LBRACE;
			nexts = "{";
		}
		else if (buffer[0] == '}')
		{
			nexttt = RBRACE;
			nexts = "}";
		}
		else if (buffer[0] == '(')
		{
			nexttt = LPAREN;
			nexts = "(";
		}
		else if (buffer[0] == ')')
		{
			nexttt = RPAREN;
			nexts = ")";
		}
		else if (buffer[0] == '+')
		{
			nexttt = PLUS;
			nexts = "+";
		}
		else if (buffer[0] == '-')
		{
			addToBuffer(buffer, filestream);
			if (isNum(buffer[1]))
			{
				while (isNum(buffer[buffer.size() - 1]))
				{
					addToBuffer(buffer, filestream);
				}

				//remove last thing
				removeFromBuffer(buffer, filestream);
				nexttt = CONSTANT;
				nexts = buffer;
			}
			else
			{
				removeFromBuffer(buffer, filestream);
				nexttt = MINUS;
				nexts = "-";
			}
		}
		else if (buffer[0] == '/')
		{
			nexttt = DIVIDE;
			nexts = "/";
		}
		else if (buffer[0] == '*')
		{
			nexttt = MULTIPLY;
			nexts = "*";
		}
		else if (buffer[0] == '.')
		{
			nexttt = DOT;
			nexts = ".";
		}
		else if (buffer[0] == ',')
		{
			nexttt = COMMA;
			nexts = ",";
		}
		else if (buffer[0] == '=')
		{
			addToBuffer(buffer, filestream);
			if (buffer[1] == '=')
			{
				nexttt = EE;
				nexts = "==";
			}
			else
			{
				removeFromBuffer(buffer, filestream);
				nexttt = EQL;
				nexts = "=";
			}
		}
		else if (buffer[0] == ';')
		{
			nexttt = EOL;
			nexts = ";";
		}
		else if (buffer[0] == '>')
		{
			addToBuffer(buffer, filestream);
			if (buffer[1] == '=')
			{
				nexttt = GRE;
				nexts = ">=";
			}
			else
			{
				removeFromBuffer(buffer, filestream);
				nexttt = GR;
				nexts = ">";
			}
		}
		else if (buffer[0] == 0)
		{
			nexttt = NONE;
			nexts = "eof";
		}
		else if (isLowerCharacter(buffer[0]) || isUpperCharacter(buffer[0]))
		{
			addToBuffer(buffer, filestream);
			while (isLowerCharacter(buffer[buffer.size() - 1]) || isUpperCharacter(buffer[buffer.size() - 1]) || isNum(buffer[buffer.size() - 1]))
			{
				addToBuffer(buffer, filestream);
			}
			removeFromBuffer(buffer, filestream);

			if (buffer == "pow")
			{
				nexttt = POW;
				nexts = "pow";
			}
			else if (buffer == "orr")
			{
				nexttt = OR;
				nexts = "orr";
			}
			else if (buffer == "amp")
			{
				nexttt = AND;
				nexts = "amp";
			}
			else if (buffer == "mod")
			{
				nexttt = MOD;
				nexts = "mod";
			}
			else
			{
				nexttt = IDEN;
				nexts = buffer;
			}
		}
		else
		{
			if (isNum(buffer[0]))
			{
				while (isNum(buffer[buffer.size() - 1]))
				{
					addToBuffer(buffer, filestream);
				}

				//remove last thing
				removeFromBuffer(buffer, filestream);
				nexttt = CONSTANT;
				nexts = buffer;
			}
			else
			{
				//white space
				if (isWhiteSpace(buffer[0]))
				{
					while (isWhiteSpace(buffer[buffer.size() - 1]))
					{
						if (buffer[buffer.size() - 1] == '\n')
						{
							linenext++;
						}
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					start = true;
				}
				else
				{
					while (!isWhiteSpace(buffer[buffer.size() - 1]))
					{
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					nexttt = ERROR;
					nexts = "IT2: Invalid Token detected on line: " + to_string(linenext) + " [ " + buffer + " ]";
				}
			}
		}
	}
	/*cout << "***"<<endl;
	cout << linecurrent << " " << currentTokenString()<<endl;
	cout << linenext << " " << nextTokenString() << endl;
	cout << "***" << endl;*/
}



int Scanner::getLine()
{
	return linecurrent;
}