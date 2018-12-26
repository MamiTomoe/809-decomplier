#pragma once

#include "X86Symbols.hpp"

class X64Symbols : public X86Symbols {
public:
	
	X64Symbols();
	

	virtual ~X64Symbols() override {}

	//The getter of the current symbols
	inline std::map<std::string, std::string> getCurrentSymbols() { return _symbols; }

private:
	virtual  void getSymbols() override;

};