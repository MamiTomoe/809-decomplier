#pragma once
#include <map>
#include <algorithm>
#include <string>

#define X64_AND_X86_REGISTERS_LEGTH 3
#define X8086_REGISTERS_LEGTH 2
#define X64_AND_X86_ARCH 0 
#define X8086_ARCH 1
#define X8008_ARCH 0

using std::map;
using std::string;
//using split;


class FindArchitcture {
public:
	FindArchitcture(string fullRegister) { 
		getArictutreForMap(); 
		getRegFromString(fullRegister);
	}

	/*
	The function will find  arch by getting  the letter from the given register\
	input: register char
	output: the given arch
	*/

	inline string getFileArch() { return _architctures.find(_reg) != _architctures.end() ? _architctures[_reg] : "Arch Execption"; }

	~FindArchitcture() = default;

	FindArchitcture(const FindArchitcture& other) = delete;//So we won't use a copy c'tor
private:
	map<char, string> _architctures;
	void getArictutreForMap();
	void getRegFromString(string fullRegister);
	char _reg;
};