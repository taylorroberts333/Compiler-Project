#pragma once

#include <vector>
#include <string>
#include "Type.h"
using namespace std;

class ASTFunction;
class ASTNode;
class ASTProgram;
class ASTParam;
class ASTStatements;
class ASTIf;
class ASTFor;
class ASTDeclaration;
class ASTAssign;
class ASTFunctionCall;
class ASTArgs;
class ASTPow;
class ASTExpr;
class ASTTerm;
class ASTFactor;
class ASTElement;
class ASTBooleanExprA;
class ASTBooleanExprB;
class ASTTypeList;
class ASTCallMultipleAssign;


class ASTNode
{
public:
	virtual void print(int depth, int printspace=true) = 0;
	virtual Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)=0;
	void setLineNumber(int l);
	int getLineNumber();
protected:
	int lineNumber;

};

class ASTProgram : public ASTNode
{
public:
	ASTProgram();
	void addFunction(ASTFunction* theFunction);

	void print(int depth, int printspace = true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);

private:
	vector<ASTFunction*> functions;
};

class ASTFunction : public ASTNode
{
public:
	ASTFunction(string namein, ASTTypeList* returnTypein);
	void addParams(ASTParam* theParams);
	void setStatements(ASTStatements* statementsin);
	void print(int depth, int printspace = true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	ASTTypeList * getTypeList();
	ASTParam* getParam();
	string getName();
private:
	string name;
	ASTTypeList* returnTypes;
	ASTParam* params;
	ASTStatements* statements;
};

class ASTParam : public ASTNode
{
public:
	ASTParam();
	void addParam(string name, string type);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	vector<string> getVarNames();
	vector<string> getTypes();

private:
	vector<string> varNames; 
	vector<string> types;
};

class ASTStatements : public ASTNode
{
public:
	ASTStatements();
	void addStatement(ASTNode *);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	vector<ASTNode*> getStatements();
private:
	vector<ASTNode*> statements;
};

class ASTDeclaration : public ASTNode
{
public:
	ASTDeclaration(string typein, string namein, ASTNode* rightSidein);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	string getType();
private:
	string type, name;
	ASTNode* rightSide;
};

class ASTFunctionCall : public ASTNode
{
public:
	ASTFunctionCall(string namein, ASTArgs* theArgs, bool isStatementin);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	string getName();
	ASTArgs* getArgs();
private:
	string name;
	ASTArgs* args;
	bool isStatement;
};

class ASTArgs : public ASTNode
{
public:
	ASTArgs();
	void addArg(ASTNode * theArd);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	vector<ASTNode*> getArgs();
private:
	vector<ASTNode *> args;
};

class ASTTypeList : public ASTNode
{
public:
	ASTTypeList();
	void addArg(string theName);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	vector<string> getVector();
private:
	vector<string> args;
};

class ASTBlock : public ASTNode
{
public:
	ASTBlock(ASTStatements * stmts);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	ASTStatements* statements;
};


class ASTElement : public ASTNode
{
public:
	ASTElement(string nameOrIDin);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	string nameOrID;
};

class ASTFactor : public ASTNode
{
public:
	ASTFactor(ASTNode * other);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	ASTNode* child;
};

class ASTPow : public ASTNode
{
public:
	ASTPow(vector<ASTNode *> nodes);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<ASTNode*> children;
};

class ASTExpr : public ASTNode
{
public:
	ASTExpr(vector<ASTNode*> operands,vector<string> operators);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<ASTNode*> operands;
	vector<string> operators;
};

class ASTTerm : public ASTNode
{
public:
	ASTTerm(vector<ASTNode*> operands, vector<string> operators);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<ASTNode*> operands;
	vector<string> operators;
};

class ASTBooleanExprB : public ASTNode
{
public:
	ASTBooleanExprB(vector<ASTNode*> operands, vector<string> operators);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<ASTNode*> operands;
	vector<string> operators;
};

class ASTBooleanExprA : public ASTNode
{
public:
	ASTBooleanExprA(vector<ASTNode*> operands, vector<string> operators);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<ASTNode*> operands;
	vector<string> operators;
};

class ASTFor : public ASTNode
{
public:
	ASTFor(ASTNode* dec, ASTNode*compare, ASTNode*inc, ASTNode*body, bool block);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	ASTNode* dec, *compare, *inc, *body;
	bool block;
};

class ASTIf : public ASTNode
{
public:
	ASTIf(ASTNode* compare, ASTNode* body, bool block);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	ASTNode * compare, * body;
	bool block;
};

class ASTAssign : public ASTNode
{
public:
	ASTAssign(ASTNode* other, string name);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	ASTNode* child;
	string name;
};

class ASTReturn : public ASTNode
{
public:
	ASTReturn(vector<ASTNode*> operands);
	void print(int depth, int printspace=true);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
	vector<ASTNode*> getTypes();
private:
	vector<ASTNode*> operands;
};

class ASTCallMultipleAssign : public ASTNode
{
public:
	ASTCallMultipleAssign(vector<string> operands, ASTNode* functionCall);
	void print(int depth, int printspace);
	Type typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError);
private:
	vector<string> vars;
	ASTNode* functionCall;
};

