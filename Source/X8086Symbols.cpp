#include "X8086Symbols.hpp"

/*
The c'tor of the class.
input:
output: the new class
*/

X8086Symbols::X8086Symbols() : X8008Symbols()
{
	getSymbols();
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

void X8086Symbols::getSymbols()
{
	_symbols["idiv"] = pairForSymbolMap( "/", eightySixBitsOpcodesNumOfVars::idivNumOfVars);
	_symbols["imul"] = pairForSymbolMap("*", eightySixBitsOpcodesNumOfVars::imulNumOfVars);
	_symbols["loop"] = pairForSymbolMap("while(ecx > 0)", eightySixBitsOpcodesNumOfVars::loopNumOfVars);
	_symbols["neg"] = pairForSymbolMap("-", eightySixBitsOpcodesNumOfVars::negNumOfVars);
	_symbols["dec"] = pairForSymbolMap("--", eightySixBitsOpcodesNumOfVars::decNumOfVars);
	_symbols["inc"] = pairForSymbolMap("++", eightySixBitsOpcodesNumOfVars::incNumOfVars);
	_symbols["loope"] = pairForSymbolMap("while(ecx > 0 && ZF)", eightySixBitsOpcodesNumOfVars::loopeNumOfVars);
	_symbols["loopne"] = pairForSymbolMap("while(ecx > 0 && !ZF)", eightySixBitsOpcodesNumOfVars::loopneNumOfVars);
}