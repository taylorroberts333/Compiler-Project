#include "Parser.h"

void Parser::printError(string code, string message, int line)
{
	cout << code << " on line : " << line << " " << message <<". Recieved " <<  scan->toString(scan->currentTokenType()) <<" \"" << scan->currentTokenString()<<"\"." << endl;
	errorDetected = true;
}

Parser::Parser(string fname)
{
	scan = new Scanner(fname);
	errorDetected = false;
	program = 0;
}

bool Parser::getErrorDetected()
{
	return errorDetected;
}

ASTProgram* Parser::parse()
{
	rdpProgram();
	return program;
}

void Parser::rdpProgram()
{
	program = new ASTProgram();
	program->setLineNumber(scan->getLine());

	if (scan->currentTokenType() == IDEN)
	{
		program->addFunction(rdpFunction());
	}
	else
	{
		printError("E1", "Expecting IDEN at program beginning", scan->getLine());
	}

	while (scan->currentTokenType() != NONE && !errorDetected)
	{
		program->addFunction(rdpFunction());
	}
}

ASTFunction* Parser::rdpFunction()
{
	ASTFunction* theFunc = NULL;
	ASTTypeList * rtype=0;
	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		rtype = rdpTypeList();
	
	}
	else if(!errorDetected)
	{
		printError("E2", "Expecting IDEN at beginning of funtion", scan->getLine());
	}

	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		theFunc = new ASTFunction(scan->currentTokenString(),rtype);
		theFunc->setLineNumber(scan->getLine());
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E2b", "Expecting IDEN after return type", scan->getLine());
	}

	if (scan->currentTokenType() == LPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E3", "Expecting ( after IDEN", scan->getLine());
	}

	//optional list
	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		theFunc->addParams(rdpParam());
	}


	if (scan->currentTokenType() == RPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E4", "Expecting ) to close parameters", scan->getLine());
	}

	if (scan->currentTokenType() == LBRACE && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E5", "Expecting { ", scan->getLine());
	}

	//statements goes here!
	if (!errorDetected)
	{
		theFunc->setStatements(rdpStatements());
	}

	if (scan->currentTokenType() == RBRACE && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E6", "Expecting } ", scan->getLine());
	}

	return theFunc;
}

ASTParam* Parser::rdpParam()
{
	ASTParam* param = new ASTParam();
	param->setLineNumber(scan->getLine());

	string type;
	string name;


	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		type = scan->currentTokenString();
		scan->advance();
	}
	else if(!errorDetected)
	{
		printError("E7", "Expecting IDEN for function parameter type ", scan->getLine());
	}

	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		name = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E8", "Expecting IDEN for function parameter name ", scan->getLine());
	}
	param->addParam(name, type);

	while (scan->currentTokenType() == COMMA && !errorDetected)
	{
		scan->advance();

		if (scan->currentTokenType() == IDEN && !errorDetected)
		{
			type = scan->currentTokenString();
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E7", "Expecting IDEN for function parameter type ", scan->getLine());
		}

		if (scan->currentTokenType() == IDEN && !errorDetected)
		{
			name = scan->currentTokenString();
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E8", "Expecting IDEN for function parameter name ", scan->getLine());
		}
		param->addParam(name, type);
	}
	



	return param;
}

ASTStatements* Parser::rdpStatements()
{
	ASTStatements* statements = new ASTStatements();
	statements->setLineNumber(scan->getLine());

	while (!errorDetected && scan->currentTokenType() != RBRACE)
	{
		statements->addStatement(rdpStatement());
	}

	return statements;
}

ASTNode* Parser::rdpStatement()
{
	if (scan->currentTokenString() == "for")
	{
		return (ASTNode*)rdpFor();
	}
	else if (scan->currentTokenString() == "if")
	{
		return (ASTNode*)rdpIf();
	}
	else if (scan->currentTokenString() == "return")
	{
		return (ASTNode*)rdpReturn();
	}
	else if (scan->currentTokenType() == COMMA)
	{
		return (ASTNode*)rdpCallMultipleAssign();
	}
	else if (scan->currentTokenType() == IDEN && scan->nextTokenType() == IDEN)
	{
		return (ASTNode*)rdpDeclaration();
	}
	else if (scan->currentTokenType() == IDEN && scan->nextTokenType() == LPAREN)
	{

		ASTNode* n = (ASTNode*)rdpFunctionCall(true);
		

		if (scan->currentTokenType() == EOL && !errorDetected)
		{
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E9b", "Expecting ; after functionCall statement", scan->getLine());
		}

		return n;
	}
	else if (scan->currentTokenType() == LBRACE)
	{
		return (ASTNode*)rdpBlock();
	}
	else
	{
		return (ASTNode*)rdpAssign();
	}


	return NULL;
}

ASTDeclaration* Parser::rdpDeclaration()
{
	string name;
	string type;
	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		type = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E9", "Expecting IDEN for variable type", scan->getLine());
	}

	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		name = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E10", "Expecting IDEN for variable name", scan->getLine());
	}

	ASTNode* n = NULL;
	if (scan->currentTokenType() == EQL && !errorDetected)
	{
		scan->advance();
		n = rdpBooleanExprA();
	}

	if (scan->currentTokenType() == EOL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E11", "Expecting ; after declaration", scan->getLine());
	}
	ASTDeclaration * dec = new ASTDeclaration(type, name, n);
	dec->setLineNumber(scan->getLine());
	return dec;
}

ASTFunctionCall* Parser::rdpFunctionCall(bool isStatement)
{
	string fname;
	ASTArgs* args=0;

	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		fname = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E12", "Expecting IDEN for function name", scan->getLine());
	}

	if (scan->currentTokenType() == LPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E12", "Expecting LPAREN after function name", scan->getLine());
	}

	if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
		args = rdpArgs();
	

	if (scan->currentTokenType() == RPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E13", "Expecting RPAREN after function arg list", scan->getLine());
	}
	ASTFunctionCall * func = new ASTFunctionCall(fname, args, isStatement);
	func->setLineNumber(scan->getLine());
	return func;
}

ASTArgs* Parser::rdpArgs()
{
	ASTArgs* param = new ASTArgs();
	param->setLineNumber(scan->getLine());
	ASTNode * name;

	name = rdpBooleanExprA();

	/*if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E14", "Expecting IDEN for function call argument type ", scan->getLine());
	}*/

	param->addArg(name);

	while (scan->currentTokenType() == COMMA && !errorDetected)
	{
		scan->advance();

		/*if (scan->currentTokenType() == IDEN && !errorDetected)
		{
			name = scan->currentTokenString();
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E15", "Expecting IDEN for function call argument type ", scan->getLine());
		}*/
		name = rdpBooleanExprA();

		param->addArg(name);
	}

	return param;
}

ASTTypeList* Parser::rdpTypeList()
{
	ASTTypeList* param = new ASTTypeList();
	param->setLineNumber(scan->getLine());

	string name;


	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		name = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E14b", "Expecting IDEN for function call argument type ", scan->getLine());
	}

	param->addArg(name);

	while (scan->currentTokenType() == COMMA && !errorDetected)
	{
		scan->advance();

		if (scan->currentTokenType() == IDEN && !errorDetected)
		{
			name = scan->currentTokenString();
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E15b", "Expecting IDEN for function call argument type ", scan->getLine());
		}

		param->addArg(name);
	}

	return param;
}

ASTBlock* Parser::rdpBlock()
{
	ASTBlock* block;
	if (scan->currentTokenType() == LBRACE && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E15", "Block expecting { ", scan->getLine());
	}

	block = new ASTBlock(rdpStatements());
	block->setLineNumber(scan->getLine());

	if (scan->currentTokenType() == RBRACE && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E16", "Block expecting } ", scan->getLine());
	}

	return block;
}

ASTNode* Parser::rdpElement()
{
	//functioncall
	if (scan->currentTokenType() == IDEN && scan->nextTokenType() == LPAREN && !errorDetected)
	{
		return rdpFunctionCall(false);
	}
	//constant
	else if (scan->currentTokenType() == CONSTANT && !errorDetected)
	{
		string s = scan->currentTokenString();
		scan->advance();
		ASTElement * el = new ASTElement(s);
		el->setLineNumber(scan->getLine());
		return el;
	}
	//var
	else if (scan->currentTokenType() == IDEN  && !errorDetected)
	{
		string s = scan->currentTokenString();
		scan->advance();
		ASTElement * el = new ASTElement(s);
		el->setLineNumber(scan->getLine());
		return el;
	}

	if(!errorDetected)
		printError("E17", "Expecting IDEN or Constant or Function Call ", scan->getLine());

	return 0;
}

ASTNode* Parser::rdpFactor()
{
	if (scan->currentTokenType() == LPAREN && !errorDetected)
	{
		scan->advance();

		ASTNode* n = (ASTNode *)rdpBooleanExprA();


		if (scan->currentTokenType() == RPAREN && !errorDetected)
		{
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E18", "expecting ) ", scan->getLine());
		}
		ASTFactor* f = new ASTFactor(n);
		f->setLineNumber(scan->getLine());
		return f;
	}
	else
	{
		return rdpElement();
	}
}

ASTNode* Parser::rdpPow()
{
	ASTNode* n = rdpFactor();

	vector<ASTNode*> pows;
	pows.push_back(n);

	while (scan->currentTokenType() == POW && !errorDetected)
	{
		scan->advance();
		pows.push_back(rdpFactor());
	}

	if (pows.size() > 1)
	{
		ASTPow * p = new ASTPow(pows);
		p->setLineNumber(scan->getLine());
		return p;
	}
	else
	{
		return n;
	}
}

ASTNode* Parser::rdpExpr()
{
	ASTNode* n = rdpPow();

	vector<ASTNode*> operands;
	vector<string> operators;

	operands.push_back(n);

	while ((scan->currentTokenType() == MULTIPLY || scan->currentTokenType() == DIVIDE) && !errorDetected)
	{
		operators.push_back(scan->currentTokenString());
		scan->advance();
		operands.push_back(rdpPow());
	}

	if (operands.size() > 1)
	{
		ASTExpr* epr = new ASTExpr(operands, operators);
		epr->setLineNumber(scan->getLine());
		return epr;
	}
	else
	{
		return n;
	}
}

ASTNode* Parser::rdpTerm()
{
	ASTNode* n = rdpExpr();

	vector<ASTNode*> operands;
	vector<string> operators;

	operands.push_back(n);

	while ((scan->currentTokenType() == PLUS || scan->currentTokenType() == MINUS) && !errorDetected)
	{
		operators.push_back(scan->currentTokenString());
		scan->advance();
		operands.push_back(rdpExpr());
	}

	if (operands.size() > 1)
	{
		ASTTerm * t = new ASTTerm(operands, operators);
		t->setLineNumber(scan->getLine());
		return t;
	}
	else
	{
		return n;
	}
}

ASTNode* Parser::rdpBooleanExprA()
{
	ASTNode* n = rdpBooleanExprB();

	vector<ASTNode*> operands;
	vector<string> operators;

	operands.push_back(n);

	while ((scan->currentTokenType() == AND || scan->currentTokenType() == OR) && !errorDetected)
	{
		operators.push_back(scan->currentTokenString());
		scan->advance();
		operands.push_back(rdpBooleanExprB());
	}

	if (operands.size() > 1)
	{
		ASTBooleanExprA * b = new ASTBooleanExprA(operands, operators);
		b->setLineNumber(scan->getLine());
		return b;
	}
	else
	{
		return n;
	}
}

ASTNode* Parser::rdpBooleanExprB()
{
	ASTNode* n = rdpTerm();

	vector<ASTNode*> operands;
	vector<string> operators;

	operands.push_back(n);

	while ((scan->currentTokenType() == EE || scan->currentTokenType() == GR || scan->currentTokenType() == GRE) && !errorDetected)
	{
		operators.push_back(scan->currentTokenString());
		scan->advance();
		operands.push_back(rdpTerm());
	}

	if (operands.size() > 1)
	{
		ASTBooleanExprB * b = new ASTBooleanExprB(operands, operators);
		b->setLineNumber(scan->getLine());
		return b;
	}
	else
	{
		return n;
	}
}

ASTNode* Parser::rdpAssign()
{
	string name;

	if (scan->currentTokenType() == IDEN && !errorDetected)
	{
		name = scan->currentTokenString();
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E19", " Assignment expecting IDEN ", scan->getLine());
	}

	if (scan->currentTokenType() == EQL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E20", " Assignment expecting = after IDEN ", scan->getLine());
	}

	ASTNode* rhs = rdpBooleanExprA();

	if (scan->currentTokenType() == EOL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E21", " expecting ;", scan->getLine());
	}

	ASTAssign * t = new ASTAssign(rhs, name);
	t->setLineNumber(scan->getLine());
	return t;
}

ASTNode* Parser::rdpReturn()
{
	vector<ASTNode*> params;

	if (scan->currentTokenString() == "return" && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E22", "  expecting return ", scan->getLine());
	}

	if (scan->currentTokenType() != EOL)
	{
		params.push_back(rdpBooleanExprA());
		while (scan->currentTokenType() == COMMA && !errorDetected)
		{
			scan->advance();

			params.push_back(rdpBooleanExprA());
		}
	}

	if (scan->currentTokenType() == EOL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E23", "  expecting ; ", scan->getLine());
	}

	ASTNode* tr = new ASTReturn(params);
	tr->setLineNumber(scan->getLine());
	return tr;
}

ASTNode* Parser::rdpFor()
{
	if (scan->currentTokenString() == "for" && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E24", "  expecting for ", scan->getLine());
	}

	if (scan->currentTokenType() == LPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E25", "  expecting ( ", scan->getLine());
	}

	ASTNode* dec = rdpDeclaration();

	ASTNode* compare = rdpBooleanExprA();

	if (scan->currentTokenType() == EOL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E26", "  expecting ; ", scan->getLine());
	}

	ASTNode* inc = rdpAssign();

	if (scan->currentTokenType() == RPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E27", "  expecting ) ", scan->getLine());
	}

	bool isBlock = scan->currentTokenType() == LBRACE;
	ASTNode* body = rdpStatement();
	ASTFor * f  = new ASTFor(dec, compare, inc, body, isBlock);
	f->setLineNumber(scan->getLine());
	return f;
}

ASTNode* Parser::rdpIf()
{
	if (scan->currentTokenString() == "if" && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E28", "  expecting if ", scan->getLine());
	}

	if (scan->currentTokenType() == LPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E29", "  expecting ( ", scan->getLine());
	}
	ASTNode* compare = rdpBooleanExprA();

	if (scan->currentTokenType() == RPAREN && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E29b", "  expecting ) ", scan->getLine());
	}

	bool isBlock = scan->currentTokenType() == LBRACE;
	ASTNode* body = rdpStatement();
	ASTIf * i = new ASTIf(compare, body, isBlock);
	i->setLineNumber(scan->getLine());
	return i;
}

ASTNode* Parser::rdpCallMultipleAssign()
{
	vector<string> names;

	do
	{
		if (scan->currentTokenType() == COMMA && !errorDetected)
		{
			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E40", "  expecting , ", scan->getLine());
		}

		if (scan->currentTokenType() == IDEN && !errorDetected)
		{
			names.push_back(scan->currentTokenString());

			scan->advance();
		}
		else if (!errorDetected)
		{
			printError("E41", "  expecting IDEN ", scan->getLine());
		}

	} while (scan->currentTokenType() == COMMA && !errorDetected);


	if (scan->currentTokenType() == EQL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E42", "  expecting = ", scan->getLine());
	}

	ASTNode* theNode = rdpFunctionCall(false);

	if (scan->currentTokenType() == EOL && !errorDetected)
	{
		scan->advance();
	}
	else if (!errorDetected)
	{
		printError("E43", "  expecting ; ", scan->getLine());
	}
	ASTCallMultipleAssign * cma = new ASTCallMultipleAssign(names, theNode);
	cma->setLineNumber(scan->getLine());
	return cma;
}