#pragma once

#include <iostream>
#include <string>
#include "Scanner.h"
#include "AST.h"
using namespace std;



class Parser
{
public:
	Parser(string fname);
	ASTProgram * parse();

	void printError(string code, string message, int line);

	void rdpProgram();
	ASTFunction* rdpFunction();
	ASTParam* rdpParam();
	ASTStatements* rdpStatements();
	ASTNode* rdpStatement();
	ASTBlock* rdpBlock();
	ASTDeclaration* rdpDeclaration();
	ASTFunctionCall* rdpFunctionCall(bool isStatement);
	ASTNode* rdpElement();
	ASTNode* rdpIf();
	ASTNode* rdpFor();
	ASTNode* rdpAssign();
	ASTNode* rdpReturn();
	ASTArgs* rdpArgs();
	ASTTypeList* rdpTypeList();
	ASTNode* rdpPow();
	ASTNode* rdpExpr();
	ASTNode* rdpTerm();
	ASTNode* rdpFactor();
	ASTNode* rdpBooleanExprA();
	ASTNode* rdpBooleanExprB();

	ASTNode* rdpCallMultipleAssign();

	bool getErrorDetected();
private:
	bool errorDetected;
	Scanner* scan;
	ASTProgram * program;
};