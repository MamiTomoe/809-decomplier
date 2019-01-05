#pragma once

#include "X8086Symbols.hpp"

class X86Symbols : public X8086Symbols  {
public:
	X86Symbols();

	virtual ~X86Symbols() override {}

	//The getter of the current symbols
	inline std::map<std::string, std::pair<std::string,int>> getCurrentSymbols() { return _symbols; }

private:
	virtual  void getSymbols() override;

};

