#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

class X8008Symbols {
public:
	X8008Symbols();

	~X8008Symbols() = default;
	
	//The getter of the current symbols
	inline map<string, string> getCurrentSymbols() { return _symbols; }

protected:

	map<string, string> _symbols;
	virtual  void getSymbols();
};