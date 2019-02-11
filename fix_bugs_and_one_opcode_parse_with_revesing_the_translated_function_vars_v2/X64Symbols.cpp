#include "X64Symbols.hpp"



/*
The c'tor of the class.
input:
output: the new class
*/

X64Symbols::X64Symbols() : X86Symbols()
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


void X64Symbols::getSymbols()
{
	_symbols["bswap"] = pairForSymbolMap(" (* << | 8)  | (* >> 8)", sixtyFourBitsOpcodesNumOfVars::bswapNumOfVars);
}