#pragma once

#include "X86Symbols.hpp"


enum sixtyFourBitsOpcodesNumOfVars
{

};

class X64Symbols : public X86Symbols {
public:
	
	X64Symbols();
	

	virtual ~X64Symbols() override {}

	//The getter of the current symbols
	inline std::map<std::string, std::pair<std::string,int>> getCurrentSymbols() { return _symbols; }

private:
	virtual  void getSymbols() override;

};