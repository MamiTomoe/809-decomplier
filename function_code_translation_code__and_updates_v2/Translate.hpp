#pragma once

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

#define X64_ARCH "X64"
#define x86_ARCH "X86"
#define X8086_ARCH "X8086"
#define X8008_ARCH "X8008"
#define PUSH_OPCODE "push"
#define CALL_OPCODE "call"
#define RETURN_OPCODE "ret"
#define MAKES_LOCAL_VARS_OPCODE "sub"
#define POINTER_THAT_THE_STACK_USE "bp"
#define STACK_POINTER_REGISTER "sp"
#define DEFUALT_TYPE "int"


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
		std::vector<parserPair> dstVars, std::string curArch,
		std::vector<parserPair> insturctions,std::vector<contentOfAssemblyFile> forFuckingTranslate);

	~Translate() = default;


	Translate(const Translate&) = delete;


private:
	//std::vector<std::string> _translatedSymbols;
	//std::vector<std::string> _oldInstructions;
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

	std::string _currArch;

	std::vector<contentOfAssemblyFile> _forFuckingTranslate;

	std::map<std::string, std::string> _stackFrameByArch;


	//Taking the name of the function, the type of it and the num of vars
	std::map<std::string, std::pair<std::string, int>> _functionInformation;

	//TODO: If it works, delete the old one and stay with this (change the name of _function impormation)
	std::map<std::string, std::pair<std::string,std::vector<varsVector>>> _improvedFunctionInformation;

	void translateSymobls();

	void getStackFrameByArch();

	void parsePushAndPopAndCallWithVars();

	std::string findStackFrame(const std::string&);

	//void parseOpcodeWithTranslate();

	//Finds if the vector contains the stack the stack frame.
	inline bool containsStackFrameForX64Bit() { return false; }

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
	inline void pushToVarsVector(const int& speicalIndex,const std::string& theVarsName,const std::string& content,const std::string& type)
	{ 
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

};

