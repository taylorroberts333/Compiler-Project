//TAYLOR ROBERTS- only modified AST.cpp
#include "AST.h"
#include <iostream>
#include <string>
#include "Type.h"
#include "Scanner.h"
using namespace std;

ASTProgram::ASTProgram()
{

}

void ASTProgram::addFunction(ASTFunction* theFunction)
{
	functions.push_back(theFunction);
}

ASTFunction::ASTFunction(string namein, ASTTypeList* returnTypein)
{
	name = namein;
	returnTypes = returnTypein;
	params = NULL;
}

void ASTFunction::addParams(ASTParam* params)
{
	this->params = params;
}

void ASTFunction::setStatements(ASTStatements* statementsin)
{
	statements = statementsin;
}


ASTParam::ASTParam()
{

}
void ASTParam::addParam(string namein, string typein)
{
	varNames.push_back(namein);
	types.push_back(typein);
}


ASTStatements::ASTStatements()
{

}

void ASTStatements::addStatement(ASTNode* theNode)
{
	statements.push_back(theNode);
}

ASTDeclaration::ASTDeclaration(string typein, string namein, ASTNode * rightSidein)
{
	type = typein;
	name = namein;
	rightSide = rightSidein;
}

ASTFunctionCall::ASTFunctionCall(string namein, ASTArgs* theArgs, bool b)
{
	name = namein;
	args = theArgs;
	isStatement = b;
}

ASTArgs::ASTArgs()
{

}

void ASTArgs::addArg(ASTNode * theArg)
{
	args.push_back(theArg);
}

ASTTypeList::ASTTypeList()
{

}

void ASTTypeList::addArg(string theArg)
{
	args.push_back(theArg);
}


ASTBlock::ASTBlock(ASTStatements* stmts)
{
	statements = stmts;
}

ASTElement::ASTElement(string nameOrIDin)
{
	nameOrID = nameOrIDin;
}

ASTPow::ASTPow(vector<ASTNode *> nodes)
{
	children = nodes;
}

ASTFactor::ASTFactor(ASTNode* other)
{
	this->child = other;
}

ASTExpr::ASTExpr(vector<ASTNode *> operands , vector<string> operators)
{
	this->operands = operands;
	this->operators = operators;
}

ASTTerm::ASTTerm(vector<ASTNode*> operands, vector<string> operators)
{
	this->operands = operands;
	this->operators = operators;
}

ASTBooleanExprA::ASTBooleanExprA(vector<ASTNode*> operands, vector<string> operators)
{
	this->operands = operands;
	this->operators = operators;
}

ASTBooleanExprB::ASTBooleanExprB(vector<ASTNode*> operands, vector<string> operators)
{
	this->operands = operands;
	this->operators = operators;
}

ASTFor::ASTFor(ASTNode* dec, ASTNode* compare, ASTNode* inc, ASTNode* body, bool isblock)
{
	this->dec = dec;
	this->compare = compare;
	this->inc = inc;
	this->body = body;
	this->block = isblock;
}

ASTIf::ASTIf(ASTNode* compare, ASTNode* body, bool isblock)
{
	this->compare = compare;
	this->body = body;
	this->block = isblock;
}

ASTAssign::ASTAssign(ASTNode* other, string namein)
{
	child = other;
	name = namein;
}


ASTReturn::ASTReturn(vector<ASTNode*> operands)
{
	this->operands = operands;
}

ASTCallMultipleAssign::ASTCallMultipleAssign(vector<string> operands, ASTNode * call)
{
	this->vars = operands;
	this->functionCall = call;
}




void ASTProgram::print(int depth, int printspace)
{
	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]->print(0);
	}
}

void ASTFunction::print(int depth, int printspace)
{
	returnTypes->print(0);
	cout <<" "<< name << "(";
	if (params != NULL)
	{
		params->print(0);
	}
	cout << ")\n{\n";
	statements->print(1);
	cout << "}\n";
}

void ASTParam::print(int depth, int printspace)
{
	for (int i = 0; i < varNames.size(); i++)
	{
		cout << types[i] << " " << varNames[i];
		if (i != varNames.size() - 1)
		{
			cout << ", ";
		}
	}
}

void ASTStatements::print(int depth, int printspace)
{
	for (int i = 0; i < statements.size(); i++)
	{
		statements[i]->print(depth);
	}
}
void ASTDeclaration::print(int depth, int printspace)
{
	if (printspace == 1)
	{
		for (int i = 0; i < depth; i++)
		{
			cout << "    ";
		}
	}

	if (this->rightSide == NULL)
	{
		cout << type << " " << name << "; ";
		if (printspace == 1)
		{
			cout << "\n";
		}
	}
	else
	{
		cout << type << " " << name << " = ";
		rightSide->print(depth);
		cout << "; ";
		if (printspace == 1)
		{
			cout << "\n";
		}
	}

}

void ASTFunctionCall::print(int depth, int printspace)
{
	if (isStatement)
	{
		for (int i = 0; i < depth; i++)
		{
			cout << "    ";
		}
	}
	cout << name << "(";
	if (args != NULL)
	{
		args->print(depth);
	}
	cout << ")";
	if (isStatement)
	{
		cout << ";\n";
	}
}

void ASTArgs::print(int depth, int printspace)
{
	for (int i = 0; i < args.size(); i++)
	{
		args[i]->print(depth);
		if (i != args.size() - 1)
			cout << ", ";
	}
}

void ASTTypeList::print(int depth, int printspace)
{
	for (int i = 0; i < args.size(); i++)
	{
		cout << args[i];
		if (i != args.size() - 1)
			cout << ", ";
	}
}

void ASTBlock::print(int depth, int printspace)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}
	cout << "{\n";

	statements->print(depth + 1);

	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}
	cout << "}\n";
}

void ASTElement::print(int depth, int printspace)
{

	cout << nameOrID;
	
}

void ASTFactor::print(int depth, int printspace)
{
	cout << "(";
	child->print(depth);
	cout << ")";

}

void ASTPow::print(int depth, int printspace)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->print(depth);
		if (i != children.size() - 1)
		{
			cout << " pow ";
		}
	}
}

void ASTExpr::print(int depth, int printspace)
{
	for (int i = 0; i < operands.size(); i++)
	{
		operands[i]->print(depth);
		if (i != operands.size() - 1)
		{
			cout << " "<< operators[i]<<" ";
		}
	}
}

void ASTTerm::print(int depth, int printspace)
{
	for (int i = 0; i < operands.size(); i++)
	{
		operands[i]->print(depth);
		if (i != operands.size() - 1)
		{
			cout << " " << operators[i] << " ";
		}
	}
}

void ASTBooleanExprA::print(int depth, int printspace)
{
	for (int i = 0; i < operands.size(); i++)
	{
		operands[i]->print(depth);
		if (i != operands.size() - 1)
		{
			cout << " " << operators[i] << " ";
		}
	}
}

void ASTBooleanExprB::print(int depth, int printspace)
{
	for (int i = 0; i < operands.size(); i++)
	{
		operands[i]->print(depth);
		if (i != operands.size() - 1)
		{
			cout << " " << operators[i] << " ";
		}
	}
}

void ASTFor::print(int depth, int printspace)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}

	cout << "for (";
	dec->print(depth,false);
	compare->print(depth,false);
	cout << "; ";
	inc->print(depth,false);
	cout << ")\n";

	if (block)
	{
		body->print(depth);
	}
	else
	{
		body->print(depth+1);
	}
}

void ASTIf::print(int depth, int printspace)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}

	cout << "if (";
	compare->print(depth);
	cout << ")\n";

	if (block)
	{
		body->print(depth);
	}
	else
	{
		body->print(depth + 1);
	}
}

void ASTAssign::print(int depth, int printspace)
{
	if (printspace == 1)
	{
		for (int i = 0; i < depth; i++)
		{
			cout << "    ";
		}
	}
	cout << name<<" = ";
	child->print(depth);
	cout << ";";
	if (printspace == 1)
	{
		cout << "\n";
	}
}

void ASTReturn::print(int depth, int printspace)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}
	cout <<"return";
	for (int i = 0; i < operands.size(); i++)
	{
		cout << " ";
		operands[i]->print(depth);
		if (i != operands.size() - 1)
			cout << ",";
	}
	cout << ";\n";
}

void ASTCallMultipleAssign::print(int depth, int printspace)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "    ";
	}
	for (int i = 0; i < vars.size(); i++)
	{
		cout << ", ";
		cout << vars[i];
	}
	cout << " = ";
	functionCall->print(depth,0);
	cout << ";\n";
}

void typeError(int line, string code,string message, bool & hasError )
{
	cout <<code<<" on line : " << line<< "  "<<  message<<"\n";
	hasError = true;
}

int ASTNode::getLineNumber()
{
	return lineNumber;
}

ASTTypeList * ASTFunction::getTypeList()
{
	return returnTypes;
}

vector<string> ASTTypeList::getVector()
{
	return this->args;
}

string ASTFunction::getName()
{
	return name;
}

ASTParam* ASTFunction::getParam()
{
	return params;
}

vector<string> ASTParam::getVarNames()
{
	return varNames;
}

vector<string> ASTParam::getTypes()
{
	return types;
}

void ASTNode::setLineNumber(int l)
{
	this->lineNumber = l;
}

vector<ASTNode *> ASTStatements::getStatements()
{
	return statements;
}

vector<ASTNode *> ASTReturn::getTypes()
{
	return operands;
}

vector<ASTNode*> ASTArgs::getArgs()
{
	return this->args;
}

string ASTFunctionCall::getName()
{
	return name;
}

ASTArgs* ASTFunctionCall::getArgs()
{
	return args;
}

string ASTDeclaration::getType()
{
	return type;
}

Type ASTProgram::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	fmap = new FunctionReturnMap();


	vector<Type> timeParam;
	vector<Type> timeReturn;
	timeReturn.push_back(INT_T);

	(*fmap)["time"] = timeReturn;
	(*fmap)["time p"] = timeParam;

	vector<Type> setPixParam;
	vector<Type> setPixReturn;
	setPixParam.push_back(INT_T);
	setPixParam.push_back(INT_T);
	setPixParam.push_back(INT_T);

	(*fmap)["setPixel"] = setPixReturn;
	(*fmap)["setPixel p"] = setPixParam;

	vector<Type> getPixParam;
	vector<Type> getPixReturn;
	getPixParam.push_back(INT_T);
	getPixParam.push_back(INT_T);
	getPixReturn.push_back(INT_T);

	(*fmap)["getPixel"] = getPixReturn;
	(*fmap)["getPixel p"] = getPixParam;


	//save all the function names and their return types
	for (int i = 0; i < functions.size(); i++)
	{
		vector<Type> types;
		for (int j = 0; j < functions[i]->getTypeList()->getVector().size();j++)
		{
			if (functions[i]->getTypeList()->getVector()[j] == "int")
			{
				types.push_back(INT_T);
			}
			else if (functions[i]->getTypeList()->getVector()[j] == "bool")
			{
				types.push_back(BOOL_T);
			}
			else if (functions[i]->getTypeList()->getVector()[j] == "void")
			{
				//do nothing. void is signified by no types in the list.
			}
			else
			{
				typeError(functions[i]->getLineNumber(),"T1", "Invalid return type found on function: " + functions[i]->getTypeList()->getVector()[j], hadError);
			}
		}
		if (fmap->find(functions[i]->getName()) != fmap->end())
		{
			typeError(functions[i]->getLineNumber(), "T0", "function already defined: " + functions[i]->getName(), hadError);

		}
		else
		{
			(*fmap)[functions[i]->getName()] = types;
			
		}

		vector<Type> params;
		//have to verify the node exists, otherwise it crashes
		if (functions[i]->getParam() != 0)
		{
			for (int j = 0; j < functions[i]->getParam()->getTypes().size(); j++)
			{
				if (functions[i]->getParam()->getTypes()[j] == "int")
				{
					params.push_back(INT_T);
				}
				else if (functions[i]->getParam()->getTypes()[j] == "bool")
				{
					params.push_back(BOOL_T);
				}
				else
				{
					typeError(functions[i]->getLineNumber(), "T2", "Invalid param type found on function: " + functions[i]->getParam()->getTypes()[j], hadError);
				}
			}
		}

		//notice saving the params in the map with an invalid function name [i.e., with a space 'p' in it]
		(*fmap)[functions[i]->getName()+" p"] = params;
	}

	//call type check on all the functions. notice we saved the names / return types first
	for (int i = 0; i < functions.size(); i++)
	{
		//keep track of current function return types
		(*fmap)["current$"] = (*fmap)[functions[i]->getName()];
		functions[i]->typeCheck(map,fmap,hadError);
	}

	bool found = false;
	for (int i = 0; i < functions.size(); i++)
	{
		if (functions[i]->getName() == "entry")
		{
			found = true;
		}
	}
	if (!found)
	{
		typeError(getLineNumber(), "T3", "No entry function found", hadError);

	}

	return VOID_T;
}

Type ASTFunction::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	//new map so scoping in other functions doesn't conflict
	map = new TypeMap();

	if (params != 0)
	{
		for (int i = 0; i < params->getTypes().size(); i++)
		{
			(*map)[params->getVarNames()[i]] = params->getTypes()[i] == "int" ? INT_T : params->getTypes()[i] == "bool" ? BOOL_T : ERROR_T;
		}
	}

	statements->typeCheck(map, fmap, hadError);

	ASTNode* last = 0;
	if(statements->getStatements().size() > 0)
		last = statements->getStatements()[statements->getStatements().size()-1];

	ASTReturn* r = 0;
	if (dynamic_cast<ASTReturn*>(last) != nullptr)
	{
		r = (ASTReturn*)last;
	}

	return VOID_T;
}

Type ASTStatements::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < statements.size(); i++)
	{
		statements[i]->typeCheck(map,fmap,hadError);
	}
	return ERROR_T;
}

Type ASTDeclaration::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	if (map->find(name) != map->end())
	{
		typeError(getLineNumber(), "T4", "Variable: "+name+ " already defined", hadError);
	}
	else
	{
		if (type != "int" && type != "bool")
		{
			typeError(getLineNumber(), "T5", "Variable: " + name + " declared with illegal type: "+type, hadError);
		}
		else
		{
			if (type == "int")
			{
				(*map)[name] = INT_T;
			}
			else
			{
				(*map)[name] = BOOL_T;
			}
		}
	}

	if (rightSide != 0)
	{
		Type t = rightSide->typeCheck(map, fmap, hadError);
		if (t != (*map)[name])
		{
			typeError(getLineNumber(), "T17", "declaration right side's type does not match variable type", hadError);
		}
	}

	return VOID_T;
}

Type ASTIf::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	if(compare->typeCheck(map, fmap, hadError) != BOOL_T)
	{
		typeError(getLineNumber(), "T20", "Boolean not found on if guard", hadError);
	}

	TypeMap* oldMap = map;

	map = new TypeMap(); 

	map->insert(oldMap->begin(), oldMap->end()); 

	body->typeCheck(map,fmap,hadError);

	map = oldMap;

	return ERROR_T;
}

Type ASTFor::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	TypeMap* oldMap = map;

	map = new TypeMap(); 

	map->insert(oldMap->begin(), oldMap->end()); 

	dec->typeCheck(map,fmap,hadError);

	if(compare->typeCheck(map, fmap, hadError) != BOOL_T)
	{
		typeError(getLineNumber(), "T20", "Boolean not found on for guard", hadError);
	}

	inc->typeCheck(map,fmap,hadError);
	
	body->typeCheck(map,fmap,hadError);

	map = oldMap;

	return ERROR_T;
}

Type ASTAssign::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	Type t = child->typeCheck(map, fmap, hadError);

	if (map->find(name) == map->end()){
		typeError(getLineNumber(), "T19a", name + " must be declared before use ", hadError);
	}

	if (t != (*map)[name])
			{
				typeError(getLineNumber(), "T31", "left and right type assignments dont agree", hadError);
			}

	return ERROR_T;
}

Type ASTFunctionCall::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	string name = this->name;
	ASTNode* args = this->args;
	ASTArgs * realArgs = 0;
	if (args != 0)
	{
		realArgs = (ASTArgs *)args;
	}
	if ((*fmap).find(name+" p") == fmap->end())
	{
		typeError(getLineNumber(), "T18y", "Function does not exist", hadError);

	}
	else
	{
		vector<Type> ftypes = (*fmap)[name+" p"];
		vector<Type> argTypes;
		if (realArgs != 0)
		{
			for (int i = 0; i < realArgs->getArgs().size(); i++)
			{
				argTypes.push_back(realArgs->getArgs()[i]->typeCheck(map, fmap, hadError));
			}
		}

		if (argTypes.size() != ftypes.size())
		{
			typeError(getLineNumber(), "T18x", "Function call arguments length do not match what function wants", hadError);
		}
		else
		{
			for (int i = 0; i < argTypes.size(); i++)
			{
				if (argTypes[i] != ftypes[i])
				{
					typeError(getLineNumber(), "T18z", "Function call type arguments do not match", hadError);
					break;
				}
			}
		}
	}
	if ((*fmap).find(name + " p") == fmap->end())
		return ERROR_T;

	vector<Type> rtypes = (*fmap)[name];

	if (rtypes.size() > 1 && !isStatement)
	{
		typeError(getLineNumber(), "T18a", "single function call cannot return multiple arguments", hadError);
	}

	if ((*fmap)[name].size() == 0)
		return VOID_T;

	return (*fmap)[name][0];
}

Type ASTCallMultipleAssign::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	vector<Type> varTypes;

	for (int i = 0; i < vars.size(); i++)
	{
		Type t;

		if (map->find(vars[i]) != map->end())
		{
			t = (*map)[vars[i]];
		}
		else
		{
			typeError(getLineNumber(), "T19a", vars[i] + " must be declared before use ", hadError);
			t = ERROR_T;
		}
		varTypes.push_back(t);
	}

	string name = ((ASTFunctionCall *)(this->functionCall))->getName();
	ASTNode* args = ((ASTFunctionCall*)(this->functionCall))->getArgs();
	ASTArgs* realArgs = 0;
	if (args != 0)
	{
		realArgs = (ASTArgs*)args;
	}
	if ((*fmap).find(name + " p") == fmap->end())
	{
		typeError(getLineNumber(), "T19y", "Function does not exist", hadError);

	}
	else
	{
		vector<Type> ftypes = (*fmap)[name + " p"];
		vector<Type> argTypes;
		if (realArgs != 0)
		{
			for (int i = 0; i < realArgs->getArgs().size(); i++)
			{
				argTypes.push_back(realArgs->getArgs()[i]->typeCheck(map, fmap, hadError));
			}
		}

		//cout << argTypes.size() << " " << ftypes.size() << "\n";
		if (argTypes.size() != ftypes.size())
		{
			typeError(getLineNumber(), "T19x", "Function call arguments length do not match what function wants", hadError);
		}
		else
		{
			for (int i = 0; i < argTypes.size(); i++)
			{
				//cout << argTypes[i] << " " << ftypes[i] << "\n";
				if (argTypes[i] != ftypes[i])
				{
					typeError(getLineNumber(), "T19z", "Function call type arguments do not match", hadError);
					break;
				}
			}
		}
	}

	vector<Type> returnTypeList = (*fmap)[name];
	
	if (varTypes.size() != returnTypeList.size())
	{
		typeError(getLineNumber(), "T19x", "Function call arguments length do not match what function wants", hadError);
	}
	else
	{
		for (int i = 0; i < returnTypeList.size(); i++)
		{
			if (varTypes[i] != returnTypeList[i])
			{
				typeError(getLineNumber(), "T19z", "Function call type arguments do not match", hadError);
				break;
			}
		}
	}

	return ERROR_T;
}

Type ASTPow::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->typeCheck(map,fmap,hadError) != INT_T)
		{
			typeError(getLineNumber(), "T19", "POW require int", hadError);
		}
	}
	return INT_T; //has to be an int.
}

Type ASTExpr::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < operands.size(); i++)
	{
		if (operands[i]->typeCheck(map,fmap,hadError) != INT_T)
		{
			//has to be int to multiply or divide
			typeError(getLineNumber(), "T20", "* or / require int", hadError);
		}
	}
	return INT_T;
}

Type ASTTerm::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < operands.size(); i++)
	{
		if (operands[i]->typeCheck(map,fmap,hadError) != INT_T)
		{
			//has to be int to add or subtract
			typeError(getLineNumber(), "T21", "+ or - require int", hadError);
		}
	}
	return INT_T;
}

Type ASTFactor::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	Type t;
	
	t = child->typeCheck(map,fmap,hadError);

	return t;
}

bool isNumber(const string& str)
{
    for (int i = 0; i < str.length(); i++) {
        if (std::isdigit(str[i]) == 0) return false;
    }
    return true;
}

Type ASTElement::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	Type t;

	if(nameOrID == "true" || nameOrID == "false")
	{
		t = BOOL_T;
	}
	else if(isNumber(nameOrID))
	{
        t = INT_T;
	}
	else if(map->find(nameOrID) != map->end())
	{
		t = (*map)[nameOrID];
	}
	else
	{
		typeError(getLineNumber(), "T25", nameOrID + " must be a bool or an int", hadError);
		t = ERROR_T;
	}

	return t;
}

Type ASTBooleanExprA::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < operands.size(); i++)
	{
		if (operands[i]->typeCheck(map,fmap,hadError) != BOOL_T)
		{
			typeError(getLineNumber(), "T22", "AND/OR require bool", hadError);
		}
	}
	return BOOL_T;
}

Type ASTBooleanExprB::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	for (int i = 0; i < operands.size(); i++)
	{
		if(operators[i] == ">=" || operators[i] == ">"){
			if(operands[i]->typeCheck(map,fmap,hadError) != INT_T || operands[i+1]->typeCheck(map,fmap,hadError) != INT_T)
			{
				typeError(getLineNumber(), "T23", ">= or > require int", hadError);
			}
		}
		if (operators[i] == "=="){
      		if(operands[i]->typeCheck(map,fmap,hadError) != operands[i+1]->typeCheck(map,fmap,hadError))
			{
				typeError(getLineNumber(), "T24", "cannot compare an bool and int", hadError);
			}
   		}
	}
	return BOOL_T;
}

Type ASTBlock::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	TypeMap* oldMap = map;

	map = new TypeMap(); 

	map->insert(oldMap->begin(), oldMap->end()); 

	statements->typeCheck(map,fmap,hadError);

	map = oldMap;

	return ERROR_T;
}

//should be unneeded as return should only be the last statement. Checked in function
Type ASTReturn::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	ASTReturn * r = this;
	if (r != 0 && r->getTypes().size() > 0 && (*fmap)["current$"].size() == 0)
	{
		typeError(r->getLineNumber(), "T7", "return statement in function  has types whereas it does not return anything", hadError);
	}
	if (r != 0 && (*fmap)["current$"].size() != 0)
	{
		if ((*fmap)["current$"].size() != r->getTypes().size())
		{
			typeError(r->getLineNumber(), "T8", "return types and function types do not match in function", hadError);
		}
		else
		{
			for (int i = 0; i < r->getTypes().size(); i++)
			{
				//technically this may duplicate errors o well.
				if (r->getTypes()[i]->typeCheck(map, fmap, hadError) != (*fmap)["current$"][i])
				{
					typeError(r->getLineNumber(), "T9", "return types and function types do not match in function", hadError);
					break;
				}
			}
		}
	}
	return ERROR_T;
}

//should be unneeded based on how function and returns are implemented
Type ASTParam::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	cout << "Type check not implemented\n";
	return ERROR_T;
}
Type ASTTypeList::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	cout << "Type check not implemented\n";
	return ERROR_T;
}
Type ASTArgs::typeCheck(TypeMap* map, FunctionReturnMap* fmap, bool& hadError)
{
	cout << "ASTArgs Type check not implemented\n";
	return ERROR_T;
}