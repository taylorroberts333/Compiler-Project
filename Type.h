#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

enum Type {NULL_T=0,ERROR_T,INT_T, BOOL_T, VOID_T,EXISTS_T, MULTIPLE_RETURN_T}; //if the thing does not exist in the map, it will return a 0

typedef std::unordered_map<string, Type> TypeMap;
typedef std::unordered_map<string, vector<Type> > FunctionReturnMap;
