#pragma once

#include <map>
#include <string>
#include <iostream>
#include "OpcodeExecption.hpp"

enum eightBitsOpcodesNumOfVars {
	movNumOfVars = 2,
	addNumOfVars = 2,
	subNumOfVars = 2,
	mulNumOfVars = 1,
	andNumOfVars = 2,
	orNumOfVars = 2,
	xorNumOfVars = 2,
	notNumOfVars = 1,
	shlNumOfVars = 2,
	shrNumOfVars = 2,
	cmpNumOfVars = 2,
	jaNumOfVars = 1,
	jeNumOfVars = 1,
	jnaNumOfVars = 1,
	jneNumOfVars = 1,
	divNumOfVars = 1

};

typedef std::pair<std::string, int>   pairForSymbolMap;

class X8008Symbols {
public:
	X8008Symbols();

	X8008Symbols(const X8008Symbols&  other) { _symbols = other._symbols; }

	virtual ~X8008Symbols() {}
	
	//The getter of the current symbols
	inline std::map<std::string, std::pair<std::string,int>> getCurrentSymbols() { return _symbols; }

	//retuning string because we want to keep the old insturction and not change it althoght we have a new instructuion
	std::string getSymbolFromSymbolsMap(std::string opcode);


protected:

	//First , the opcode , second is the translate the thrid is the number of vars that the opcode contains 

	std::map<std::string, std::pair<std::string,int>> _symbols;

	virtual  void getSymbols();



	//Find if the opcode is legal 
	inline  bool isOpcodeLegal(std::string opcode) { return _symbols.find(opcode) != _symbols.end(); }
	
};