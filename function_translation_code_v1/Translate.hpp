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
#define POINTER_THAT_THE_STACK_USE "bp"

typedef  std::pair<std::string, int> mapPair;
typedef std::pair<int, std::string>  parserPair;
typedef std::pair<int,std::pair<std::string, std::string>> pushAndPopAndCallParse;


struct varsVactor {
	int index;
	std::string name;
	std::string value;
};


typedef std::pair<int, std::string> contentOfAssemblyFile;


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

	std::vector<varsVactor> _varsVector;//Special index, their  name, the value they contains.

	std::vector<parserPair> _stackFrame;//Special index +  the speical register (rbp)

	std::string _currArch;

	std::vector<contentOfAssemblyFile> _forFuckingTranslate;

	std::map<std::string, std::string> _stackFrameByArch;


	//Taking the name of the function, the type of it and the num of vars
	std::map<std::string, std::pair<std::string, int>> _functionInformation;

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
};

