#include "X8086Symbols.hpp"

/*
The c'tor of the class.
input:
output: the new class
*/

X8086Symbols::X8086Symbols() : X8008Symbols()
{
}



/*
The d'tor of the class.
input:
output: the ruined class
*/

X8086Symbols::~X8086Symbols()
{
}

/*
The function is putting all of the assembly that we start as symbols.
input: none.
output: none
*/

void X8086Symbols::getSymbols()
{
	_symbols["idiv"] = "/";
	_symbols["imul"] = "*";
	_symbols["loop"] = "while(";
	_symbols["neg"] = "-";

}