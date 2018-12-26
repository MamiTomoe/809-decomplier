#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <variant>
#include "ReadFile.hpp"
#include "FindArchitcture.hpp"
#include "x64Symbols.hpp"
#include "ArchExecption.hpp"
#include "FileExecption.h"



using std::cout;
using std::cin;
using boost::to_lower;
using std::endl;
namespace ba = boost::algorithm;
namespace fs = std::experimental::filesystem::v1;


#define USER_WANT_LOCAL_FILE 'y'
#define USER_DOESNT_WANT_LOCAL_FILE 'n'
#define ILEGAL_ARCH "Arch Execption"


class Logic {
public:

	Logic();

	/*
	The d'tor of class
	input: none
	output: the ruined  object
	*/

	~Logic() = default;


	//Delete a copy c'tor for logic (shallow copy).
	Logic(Logic&) = delete;

	//Delete a copy c'tor for Logic(deep copy).
	//Logic(const Logic&) = delete;

	//The getter of the source vars
	inline vector<string> getSourceVars() { return _sourceVars; }

	//The getter of the insturctions
	inline vector<string> getInsturctions() { return _insturctions; }

	//The getter of the dest vars
	inline vector<string> getDestVars() { return _destVars; }

	//The getter of the stack vars
	inline vector<string> getStackAndHeapVars() { return _stackAndHeapVars; }

	void getPathFromTheUser();

	void checkAndGetSymbols();


private:
	std::vector<std::string> _sourceVars;

	std::vector<std::string> _insturctions;

	std::vector<std::string> _destVars;

	std::vector<std::string> _stackAndHeapVars;

	std::string _currentArch;//Get the current arch that was found.

	std::vector<std::string> _assemblyFromFile;

	

	void parseAssemblyInfo();

	fs::path _path;

	//The function is a setter for the current arch
	inline  void setCurrentArch();

	//Uniq ptr because I don't "share" the ownership ( a smart pointer that know hot to manage itself)
	std::map<string, std::unique_ptr<X8008Symbols>> _archFound;

	//The function is setting all the assembly content from the file
	void  setAssemblyFromFile();
	void putArchOnMap();

	//check if the arch that we have gotten is legal or not
	inline bool checkIfArchIsLegal() { return _currentArch != ILEGAL_ARCH; }

	inline bool isVectorIsEmpty() { return _assemblyFromFile.empty(); }

};