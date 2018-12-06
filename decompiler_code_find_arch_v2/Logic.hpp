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


using std::vector;
using std::string;
using boost::split;
using std::cout;
using std::cin;
using boost::to_lower;
using std::endl;
namespace ba = boost::algorithm;
namespace fs = std::experimental::filesystem::v1;


#define USER_WANT_LOCAL_FILE 'y'
#define USER_DOESNT_WANT_LOCAL_FILE 'n'


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
	inline vector<string> getStackVars() { return _stackVars; }



	void setCurrentArchitcture();

	 void checkForUserChoiceForLocalFile();




private:
	vector<string> _sourceVars;
	
	vector<string> _insturctions;
	
	vector<string> _destVars;

	vector<string> _stackVars;

	string _currentArch;//Get the current arch that was found.

	vector<string> _assemblyFromFile;

	void parseAssemblyInfo();
	
	fs::path _path;

	//The function is a setter for the current arch
	inline  void setCurrentArch();
	
	//Uniq ptr because I don't "share" the ownership ( a smart pointer that know hot to manage itself)
	map<string,std::variant<std::unique_ptr<X8008Symbols>, std::unique_ptr<X8086Symbols>, std::unique_ptr<X86Symbols>, std::unique_ptr<X64Symbols>>> _archFound;

	//The function is setting all the assembly content from the file
	void  setAssemblyFromFile();
	void putArchOnMap();





};