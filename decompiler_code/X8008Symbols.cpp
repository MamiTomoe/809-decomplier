#include "x8008Symbols.hpp"

X8008Symbols::X8008Symbols()
{

}


/*
The function is putting all of the assembly that we start as symbols.
input: none.
output: none
*/

void X8008Symbols::getSymbols()
{
	_symbols["mov"] = "=";
	//_symbols["MOV"] = "=";
	//_symbols["ADD"] = "+";
	_symbols["add"] = "+";
	_symbols["sub"] = "-";
	//_symbols["SUB"] = "-";
	_symbols["mul"] = "*";
	//	_symbols["MUL"] = "*";
	_symbols["and"] = "&";
	//_symbols["AND"] = "&";
	_symbols["or"] = "|";
	//_symbols["OR"] = "|";
	_symbols["xor"] = "^";
	_symbols["not"] = "!";
	_symbols["shl"] = "<<";
	_symbols["shr"] = ">>";
	_symbols["cmp"] = "==";


}