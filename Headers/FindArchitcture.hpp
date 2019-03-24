#pragma once
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include "ArchExecption.hpp"

#define X64_AND_X86_REGISTERS_LEGTH 3
#define X8086_REGISTERS_LEGTH 2
#define X64_AND_X86_ARCH 0 
#define X8086_ARCH 1
#define X8008_ARCH 0
#define UPPER_DEFUALT_A_REGISTER "A"
#define LOWER_DEFUALT_A_REGISTER "a"
#define AX_REGISTER  "ax"

using std::map;
using std::string;
using std::vector;


enum   archForTheAregister : char {
	x8008Arch = 'A',
	X8086LowArch = 'l',
	X8086HighArch = 'h',
	X8086Arch = 'x',
	x86Arch = 'e',
	X64Arch = 'r'

};

using  findAregister =  archForTheAregister;

class FindArchitcture {
public:
	FindArchitcture(const vector<string>& assemblyFromFile);



	/*
	The function will find  arch by getting  the letter from the given register\
	input: register char
	output: the given arch
	*/

	inline string getFileArch() { return _architctures.find(_reg) != _architctures.end() ? _architctures[_reg] : "Arch Execption"; }

	~FindArchitcture() = default;

	FindArchitcture(const FindArchitcture& other) = delete;//So we won't use a copy c'tor

	//The function is a getter for arch's map.
	//@input: none
	//@output: The architcture's map - map<char ,string> const

	inline std::map<char, std::string> getArchMap() const { return  _architctures; }


	std::string getTheARegister();

private:
	map<char, string> _architctures;
	void getArictutreForMap();
	void getRegFromString(const string& fullRegister);
	string findRegStringFromVector(const vector<string>& assemblyFromFile);
	char _reg;


};