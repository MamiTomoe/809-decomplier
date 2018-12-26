#include "x8008Symbols.hpp"


/*
The c'tor of the class.
input:
output: the new class
*/
X8008Symbols::X8008Symbols()
{
	try 
	{

		getSymbols();
	}
	catch (OpcodeExecption& e) {
		//TODO: Move it into Logic after the and throw the exception in translate
		std::cout << e.what() << '\n';
	}
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

 
/*
The function is translate the symbol that was given from the current opcode given.
input: opcode - string
output: the symbol that was translated to - string
*/

std::string X8008Symbols::getSymbolFromSymbolsMap(std::string opcode)
{
	if (!isOpcodeLegal(opcode)) {
		throw OpcodeExecption("The opcode is not part from the current archictutre or isn't legal");
	}
	return _symbols[opcode];
}