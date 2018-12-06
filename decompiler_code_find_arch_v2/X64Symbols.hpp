#pragma once

#include "X86Symbols.hpp"

class X64Symbols : public X86Symbols {
public:
	
	X64Symbols();
	

	~X64Symbols();

	//The getter of the current symbols
	inline map<string, string> getCurrentSymbols() { return _symbols; }

private:
	map<string, string> _symbols;
	virtual  void getSymbols() override;

};