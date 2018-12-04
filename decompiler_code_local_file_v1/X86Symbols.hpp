#pragma once

#include "X8086Symbols.hpp"

class X86Symbols : public X8086Symbols  {
public:
	X86Symbols();

	~X86Symbols();

	//The getter of the current symbols
	inline map<string, string> getCurrentSymbols() { return _symbols; }

private:
	map<string, string> _symbols;
	virtual  void getSymbols() override;

};

