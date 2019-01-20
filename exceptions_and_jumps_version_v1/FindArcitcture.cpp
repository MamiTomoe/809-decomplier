#include "FindArchitcture.hpp"


/*
The function is getting in all the architctures of assembly (x64,x86,x80886,x80008)
input: none
output: none
*/

void FindArchitcture::getArictutreForMap() 
{
	_architctures['r'] = "x64";
	_architctures['e'] = "x86";
	_architctures['x'] = "x8086";
	_architctures['l'] = "x8086";
	_architctures['h'] = "x8086";
	_architctures['A'] = "x80008";
	_architctures['B'] = "x80008";
	_architctures['C'] = "x80008";
	_architctures['D'] = "x80008";
}


/*
The function is getting a string from the file (The register) 
and anaylise it so we can get the right letter for the right register
input: fullRegister - string
output: none
*/

void FindArchitcture::getRegFromString(const string& fullRegister)
{
	if (fullRegister.length())
	{
		if (X64_AND_X86_REGISTERS_LEGTH == fullRegister.length()) {
			_reg = fullRegister[X64_AND_X86_ARCH]; //Taking the first letter r or e
		}

		else if (X8086_REGISTERS_LEGTH == fullRegister.length()) {
			_reg = fullRegister[X8086_ARCH]; //Taking the last letter which it is x or l or h.
		}

		else {
			_reg = fullRegister[X8008_ARCH];//Taking the register itself becuase it is only A B C D 
		}
	}
	else {
		ArchExecption ae("The length of the register is not an accpetbale  size");
		throw ae;
	}
}

/*
The function is getting all the assembly content from the file and search only (for generic purpos)
input: The vector of assembly
output: none
*/

string FindArchitcture::findRegStringFromVector(const vector<string>& assemblyFromFile)
{
	string fullRegister("");
	for (const auto& line : assemblyFromFile){
		if (std::regex_match(line, std::regex("(r|e)([a-d]|[A-D])x"))) {
			//Find if there any r or e if not, it will find if the letter from a until d (little and big) and find if there is an x
			fullRegister = line;
			break;
		}

	}
	return fullRegister;
}

/*
The function is the c'tor of the class
input: the assembly vector
output: the new class
*/

FindArchitcture::FindArchitcture(const std::vector<std::string>&assemblyFromFile){
	getArictutreForMap();
	getRegFromString(findRegStringFromVector(assemblyFromFile));
}