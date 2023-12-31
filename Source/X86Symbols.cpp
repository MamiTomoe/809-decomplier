#include "X86Symbols.hpp"


/*
The c'tor of the class.
input:
output: the new class
*/

X86Symbols::X86Symbols() : X8086Symbols()
{
}


/*
The d'tor of the class.
input:
output: the ruined class
*/




/*
The function is putting all of the assembly that we start as symbols.
input: none.
output: none
*/

void X86Symbols::getSymbols() 
{
	_symbols["test"] = pairForSymbolMap("&", thiryTwoBitsOpcodesNumOfVars::testNumOfVars);
}