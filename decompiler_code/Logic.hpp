#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using std::vector;
using std::string;
using boost::split;


class Logic {
public:

	/**
	c'tor of the class 
	input: the assembly from file that was read - vector of strings
	output: new class
	**/


	Logic(vector<string> assemblyFromFile);

	
	/*
	The d'tor of class 
	input: none
	output: the ruined  object
	*/

	~Logic() = default;

	//The getter of the source vars
	inline vector<string> getSourceVars() { return _sourceVars; }

	//The getter of the insturctions
	inline vector<string> getInsturctions() { return _insturctions; }

	//The getter of the dest vars
	inline vector<string> getDestVars() { return _destVars; }

	//The getter of the stack vars
	inline vector<string> getStackVars() { return _stackVars; }


	void setCurrentArchitcture();


private:
	vector<string> _sourceVars;
	
	vector<string> _insturctions;
	
	vector<string> _destVars;

	vector<string> _stackVars;

	string _currentArch;//Get the current arch that was found.

	void parseAssemblyInfo(vector<string> assemblyFromFile);

};