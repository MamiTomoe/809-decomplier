#pragma once

#include "x8008Symbols.hpp"

typedef std::pair<std::string, int>   pairForSymbolMap;

enum eightySixBitsOpcodesNumOfVars
{
	idivNumOfVars = 1,
	imulNumOfVars = 1,
	loopNumOfVars = 1,
	loopeNumOfVars = 1,
	loopneNumOfVars = 1,
	negNumOfVars = 1,
	decNumOfVars = 1,
	incNumOfVars = 1
};

class X8086Symbols : public X8008Symbols{
public:
	X8086Symbols();


	virtual ~X8086Symbols() override { }

	//The getter of the current symbols
	inline std::map<std::string, std::pair<std::string,int>> getCurrentSymbols() { return _symbols; }

	//Find if the opcode is legal 

private:
	virtual  void getSymbols() override;

};

