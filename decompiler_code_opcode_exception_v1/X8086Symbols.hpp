#pragma once

#include "x8008Symbols.hpp"

class X8086Symbols : public X8008Symbols{
public:
	X8086Symbols();


	~X8086Symbols();

	//The getter of the current symbols
	inline std::map<std::string, std::string> getCurrentSymbols() { return _symbols; }

	//Find if the opcode is legal 

private:
	virtual  void getSymbols() override;

};

