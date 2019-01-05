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
	_symbols["idiv"] = std::pair<std::string,int>( "/", eightySixBitsOpcodesNumOfVars::idivNumOfVars);
	_symbols["imul"] = std::pair<std::string, int>("*", eightySixBitsOpcodesNumOfVars::imulNumOfVars);
	_symbols["loop"] = std::pair<std::string,int> ("while(", eightySixBitsOpcodesNumOfVars::loopNumOfVars);
	_symbols["neg"] =  std::pair<std::string,int>("-", eightySixBitsOpcodesNumOfVars::negNumOfVars);
	_symbols["dec"] = std::pair<std::string, int>("--", eightySixBitsOpcodesNumOfVars::decNumOfVars);
	_symbols["inc"] = std::pair<std::string,int>("++", eightySixBitsOpcodesNumOfVars::incNumOfVars);
}