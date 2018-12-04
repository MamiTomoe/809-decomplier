#pragma once

#include "x8008Symbols.hpp"

class X8086Symbols : public X8008Symbols{
public:
	X8086Symbols();


	~X8086Symbols();

	//The getter of the current symbols
	inline map<string, string> getCurrentSymbols() { return _symbols; }

private:
	map<string, string> _symbols;
	virtual  void getSymbols() override;

};

