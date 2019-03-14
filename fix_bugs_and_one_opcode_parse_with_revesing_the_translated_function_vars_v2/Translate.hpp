#pragma once

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

#define PUSH_OPCODE "push"
#define CALL_OPCODE "call"
#define RETURN_OPCODE "ret"
#define MAKES_LOCAL_VARS_OPCODE "sub"
#define POINTER_THAT_THE_STACK_USE "bp"
#define STACK_POINTER_REGISTER "sp"
#define DEFUALT_TYPE "int"
#define OPCODE_THAT_DONT_APPEND_EQUAL "mov"
#define IN_STACK_VAR "-"
#define MAX_SIZE_FOR_INT_VAR 1

typedef  std::pair<std::string, int> mapPair;
typedef std::pair<int, std::string>  parserPair;
typedef std::pair<int,std::pair<std::string, std::string>> pushAndPopAndCallParse;



typedef std::pair<int, std::string> contentOfAssemblyFile;

struct varsVector {
	int _index;
	std::string _name;
	std::string _value;
	std::string _type;
};



class Translate {
public:

	Translate(std::vector<parserPair> stackAndHeapVars, std::vector<parserPair> functionsName,
		std::map<std::string, mapPair> foundSymbols, std::vector<parserPair> srcVars,
		std::vector<parserPair> dstVars,
		std::vector<parserPair> insturctions,std::vector<contentOfAssemblyFile> forFuckingTranslate,
		std::vector<parserPair> floatAndDoubleVars, std::map<std::string, std::string> types);

	~Translate() = default;


	Translate(const Translate&) = delete;


private:
	std::vector<parserPair> _functionsName;

	std::vector<parserPair> _stackAndHeapVars;

	std::vector<parserPair> _srcVars;

	std::vector<parserPair> _dstVars;

	std::map<std::string, mapPair> _foundSymbols;

	std::vector<parserPair> _insturctions;

	std::vector<std::string> _symbolsInsturctionsThatConatisTwoVars;

	std::vector<pushAndPopAndCallParse> _pushAndPopAndCallWithVars;

	std::vector<varsVector> _varsVector;//Special index, their  name, the value they contains.

	std::vector<parserPair> _stackFrame;//Special index +  the speical register (rbp)

	std::vector<contentOfAssemblyFile> _forFuckingTranslate;

	std::vector<parserPair> _floatAndDoubleVars;


	//Taking the name of the function, the type of it and the num of vars
	std::map<std::string, std::pair<std::string, int>> _functionInformation;

	//TODO: If it works, delete the old one and stay with this (change the name of _function impormation)
	std::map<std::string, std::pair<std::string,std::vector<varsVector>>> _improvedFunctionInformation;

	std::map<std::string, std::string> _types;

	void translateSymobls();


	void parsePushAndPopAndCallWithVars();

	int  parseTheNumOfVarsOfTheFunction(const int&);

	void translateFunction();

	void parseStackFrame();

	int findIndexOfTheCurrFunctionCall(const int&);

	std::vector<parserPair>::iterator findInVector(std::vector<parserPair>& givenVec, const parserPair& givenPair);

	void translateInsideOfFunction(const std::string&);
	
	void parseVaraibles();

	//The function is a getter of the translated opcode.
	inline std::string gettingTheTranslatedOpcode(const  std::string& opcodeToTranslate) const {
		return _foundSymbols.at(opcodeToTranslate).first;//The  found opcode from the map returned translation.
	}

	//The pusher to the  vars vector's only.
	//input: the speical index - int, the var's current num and name - string ,  and the value they contains - string
	//and type - std::string
	//output: none
	inline void pushToVarsVector(const int& speicalIndex,const std::string& theVarsName,const std::string& content,const std::string& type){ 
		_varsVector.push_back({ speicalIndex,theVarsName,content , type});
		//Emplament_back does not work it.
	}

	//The function is searching in varVectors for vars.
	//Input: the itertor of the search - parserPair
	//Output: the  found result.

	inline std::vector<varsVector>::iterator findInVarsVector(const parserPair& pp) 
	{
		auto findInVarVector(std::find_if(_varsVector.begin(), _varsVector.end(), [pp](const varsVector& vv)
		{ return vv._index == pp.first; }));
		
		return findInVarVector;
	}

	std::vector<varsVector> getFunctionsVars(const int&);


	//The function is translating all the dest and source part.
	//input: dst string, src string - parserPair and translation string. 
	//output:  none - for debug, it will changed to std::string
	 void translateDstAndSrcSymbols(const parserPair& dst, const parserPair& src, const std::string&  translation);

	 //The function  is checking if the var that  that we get is an acual  int var.
	 //input: var - const string
	 //output: is int var or not
	 inline bool  isIntVar(const std::string& var) const { return var.size() == MAX_SIZE_FOR_INT_VAR && isdigit(var[0]); }
};