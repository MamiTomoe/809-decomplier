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
	_symbols["mov"] = pairForSymbolMap("=", eightBitsOpcodesNumOfVars::movNumOfVars);
	//_symbols["MOV"] = "=";
	//_symbols["ADD"] = "+";
	_symbols["add"] = pairForSymbolMap("+", eightBitsOpcodesNumOfVars::addNumOfVars);
	_symbols["sub"] = pairForSymbolMap("-", eightBitsOpcodesNumOfVars::subNumOfVars);
	//_symbols["SUB"] = "-";
	_symbols["mul"] = pairForSymbolMap("*", eightBitsOpcodesNumOfVars::mulNumOfVars);
	//	_symbols["MUL"] = "*";
	_symbols["and"] = pairForSymbolMap("&", eightBitsOpcodesNumOfVars::andNumOfVars);
	//_symbols["AND"] = "&";
	_symbols["or"] = pairForSymbolMap( "|", eightBitsOpcodesNumOfVars::orNumOfVars);
	//_symbols["OR"] = "|";
	_symbols["xor"] = pairForSymbolMap("^", eightBitsOpcodesNumOfVars::xorNumOfVars);
	_symbols["not"] = pairForSymbolMap("!", eightBitsOpcodesNumOfVars::notNumOfVars);
	_symbols["shl"] = pairForSymbolMap("<<", eightBitsOpcodesNumOfVars::shlNumOfVars);
	_symbols["shr"] = pairForSymbolMap(">>", eightBitsOpcodesNumOfVars::shrNumOfVars);
	_symbols["cmp"] = pairForSymbolMap("if(", eightBitsOpcodesNumOfVars::cmpNumOfVars);
	_symbols["ja"] = pairForSymbolMap(">", eightBitsOpcodesNumOfVars::jaNumOfVars);
	_symbols["jna"] = pairForSymbolMap("<", eightBitsOpcodesNumOfVars::jnaNumOfVars);
	_symbols["je"] = pairForSymbolMap("==", eightBitsOpcodesNumOfVars::jeNumOfVars);
	_symbols["jne"] = pairForSymbolMap("!=", eightBitsOpcodesNumOfVars::jneNumOfVars);
	_symbols["div"] = pairForSymbolMap("/", eightBitsOpcodesNumOfVars::divNumOfVars);
	
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