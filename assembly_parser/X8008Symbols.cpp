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
	_symbols["mov"] = std::pair<std::string,int>("=", eightBitsOpcodesNumOfVars::movNumOfVars);
	//_symbols["MOV"] = "=";
	//_symbols["ADD"] = "+";
	_symbols["add"] = std::pair<std::string, int>("+", eightBitsOpcodesNumOfVars::addNumOfVars);
	_symbols["sub"] = std::pair<std::string, int>("-", eightBitsOpcodesNumOfVars::subNumOfVars);
	//_symbols["SUB"] = "-";
	_symbols["mul"] = std::pair<std::string, int>("*", eightBitsOpcodesNumOfVars::mulNumOfVars);
	//	_symbols["MUL"] = "*";
	_symbols["and"] = std::pair<std::string, int>("&", eightBitsOpcodesNumOfVars::andNumOfVars);
	//_symbols["AND"] = "&";
	_symbols["or"] = std::pair<std::string, int>( "|", eightBitsOpcodesNumOfVars::orNumOfVars);
	//_symbols["OR"] = "|";
	_symbols["xor"] = std::pair<std::string, int>("^", eightBitsOpcodesNumOfVars::xorNumOfVars);
	_symbols["not"] = std::pair<std::string, int>("!", eightBitsOpcodesNumOfVars::notNumOfVars);
	_symbols["shl"] = std::pair<std::string, int>("<<", eightBitsOpcodesNumOfVars::shlNumOfVars);
	_symbols["shr"] = std::pair<std::string, int>(">>", eightBitsOpcodesNumOfVars::shrNumOfVars);
	_symbols["cmp"] = std::pair<std::string, int>("==", eightBitsOpcodesNumOfVars::cmpNumOfVars);

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
	return _symbols[opcode].first;
}