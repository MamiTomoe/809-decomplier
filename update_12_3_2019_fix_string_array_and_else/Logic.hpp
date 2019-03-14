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
#include "OpcodeNumOfVarsException.hpp"
#include "Translate.hpp"
#include "Types.hpp"


using std::cout;
using std::cin;
using boost::to_lower;
using std::endl;

namespace ba = boost::algorithm;
namespace fs = std::experimental::filesystem::v1;

typedef std::pair<int, std::string>  parserPair;


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
#define OPENING_STACK_FRAME "push"
#define END_OF_FUNCTION "ret"
#define FUNCTION_DECLARETION "proc"
#define IS_OPCODE_HAS_ONE_VAR 1
#define JMP_OPCODE "jmp"


enum   placeIndex {
	dstVarIndex = 1,
	srcVarIndex,
	functionOrStackVarsIndex = 1,
	twoPlaceLastIndex,
	defualtNextIndex = 1,
	oneVarOpcodePlace = 1
};

using pi = placeIndex;

typedef std::pair<int, std::string> contentOfAssemblyFile;

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
	inline std::vector<parserPair> getSourceVars() const { return _sourceVars; }

	//The getter of the insturctions
	inline std::vector<parserPair>  getInsturctions() const { return _insturctions; }

	//The getter of the dest vars
	inline std::vector<parserPair> getDestVars() const { return _destVars; }

	//The getter of the stack vars
	inline std::vector<parserPair> getStackAndHeapVars() const { return _stackAndHeapVars; }


	void getPathFromTheUser();

	 void  checkAndGetSymbols();

	 //The function is a getter of types
	 inline std::map<std::string, std::string> getTypes() const { return _types; }

private:
	std::vector<parserPair> _sourceVars;

	std::vector<parserPair> _insturctions;

	std::vector<parserPair> _destVars;

	std::vector<parserPair> _stackAndHeapVars;

	std::string _currentArch;//Get the current arch that was found.

	std::vector<std::string> _assemblyFromFile;

	std::vector<parserPair> _functionNames;

	std::vector<std::string> _symbolsInsturctionsThatConatisTwoVars;

	std::vector<contentOfAssemblyFile> _forFuckingTranslate;

	std::vector<parserPair> _floatAndDoubleVars;

	std::vector <parserPair> _oneOpcodeVars;

	std::map<std::string, std::pair<std::string, int>> _foundSymbols;

	std::map<std::string, std::string> _types;
	

	void parseAssemblyInfo();

	fs::path _path;

	std::string _theARegister;

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

	std::vector<std::string> translateTheCode();

	void getTypesFromTypesClass();
	

	//The function is pushing to the  the to the translate vector.
	//input: partFromTheFile and index - string and int
	//output: none

	inline void pushIntoTranslationVector(std::string& partFromTheFile, int& index) { 
		_forFuckingTranslate.emplace_back(index , partFromTheFile); 
	}


	/**
	The function is checking if the size of the vars from the symbols map is acually one varaible.
	input: var's num - int
	output: Is it equal to one - true or false (aka boolean).
	**/

	inline bool isItAOneVarOpcode(const int& opcodeNumOfVar) const { return IS_OPCODE_HAS_ONE_VAR == opcodeNumOfVar; }

	
};

	

