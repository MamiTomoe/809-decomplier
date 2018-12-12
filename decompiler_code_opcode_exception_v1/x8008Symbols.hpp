#pragma once

#include <map>
#include <string>
#include <iostream>
#include "OpcodeExecption.hpp"


class X8008Symbols {
public:
	X8008Symbols();

	~X8008Symbols() = default;
	
	//The getter of the current symbols
	inline std::map<std::string, std::string> getCurrentSymbols() { return _symbols; }

	//retuning string because we want to keep the old insturction and not change it althoght we have a new instructuion
	std::string getSymbolFromSymbolsMap(std::string opcode);


protected:

	std::map<std::string, std::string> _symbols;

	virtual  void getSymbols();



	//Find if the opcode is legal 
	inline  bool isOpcodeLegal(std::string opcode) { return _symbols.find(opcode) != _symbols.end(); }
	
};