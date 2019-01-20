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
The function will find  arch by getting  the letter from the given register\
input: register char
output: the given arch
*/

inline string FindArchitcture::getFileArch() { return _architctures.find(_reg) != _architctures.end() ? _architctures[_reg] : "Arch Execption";}

/*
The function is getting a string from the file (The register) 
and anaylise it so we can get the right letter for the right register
input: fullRegister - string
output: none
*/

void FindArchitcture::getRegFromString(string fullRegister)
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