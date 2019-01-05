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



#define ILEGAL_ARCH "Arch Execption"
#define PUT_STACK_VARS_IN_ASSEMBLY "push"
#define REMOVE_STACK_VARS_IN_ASSEMBLY "pop"
#define START_FORM_FILE "start"
#define END_FROM_FILE "end"
#define DEST_VASR_INDEX 1
#define SRC_VARS_INDEX 2
#define NEXT_INDEX_REGULAR 1
#define FUNCTION_OR_STACK_VARS_INDEX 1
#define FUNCTION_INSTRCATION "call" 
#define TWO_PALCE_LAST 2


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


	//The getter of the source vars
	inline std::vector<std::string> getSourceVars() const { return _sourceVars; }

	//The getter of the insturctions
	inline std::vector<std::string>  getInsturctions() const { return _insturctions; }

	//The getter of the dest vars
	inline std::vector<std::string> getDestVars() const { return _destVars; }

	//The getter of the stack vars
	inline std::vector<std::string> getStackAndHeapVars() const { return _stackAndHeapVars; }

	void getPathFromTheUser();

	 void  checkAndGetSymbols();



private:
	std::vector<std::string> _sourceVars;

	std::vector<std::string> _insturctions;

	std::vector<std::string> _destVars;

	std::vector<std::string> _stackAndHeapVars;

	std::string _currentArch;//Get the current arch that was found.

	std::vector<std::string> _assemblyFromFile;

	std::vector<std::string> _functionNames;

	std::map<std::string, std::pair<std::string, int>> _foundSymbols;


	void parseAssemblyInfo();

	fs::path _path;


	//The function is a setter for the current arch
	inline  void setCurrentArch();

	//Uniq ptr because I don't "share" the ownership ( a smart pointer that know hot to manage itself)
	std::map<string, std::unique_ptr<X8008Symbols>> _archFound;

	//The function is setting all the assembly content from the file
	void  setAssemblyFromFile();

	void putArchOnMap();

	//checks if the arch that we have gotten is legal or not
	inline bool checkIfArchIsLegal() const { return _currentArch != ILEGAL_ARCH; }

	//checks if the vector of assembly is empty.
	inline bool isVectorOfAssemblyIsEmpty() const { return _assemblyFromFile.empty(); }

	//checks if  the given index is not the last of
	// vector vars for some variables (For some insturctions is important that it won't be last)
	inline bool isInstructuionNotLast(const int& index) const { return index != _assemblyFromFile.size() - 1; }

	//checks if  the given index is not the last of the given vector vars 
	//and not two places last for the  given vector.
	inline bool isInstructuionNotTheTwoLastAndNotLast(const int& index) const { return isInstructuionNotLast(index) && index != _assemblyFromFile.size() - TWO_PALCE_LAST; }

	//The checker of the num of vars  of the opcode with the  current size of  the assembly  file
	//In case there is more vars than the opcode's num of vars than it will be considered as a single case
	inline bool isOpcodeVarsFromTheFileAreLegal(const int& lastIndexOfOpcodeNumOfVars)  const;
};

	

