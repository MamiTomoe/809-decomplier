#pragma once
#include "Exception.hpp"

class OpcodeNumOfVarsException : public Execption {
public:

	/*
	The function is the c'tor of the class
	input: exception message - string
	output: the builden class
	*/
	OpcodeNumOfVarsException(std::string excMsg) : Execption(excMsg){}


	/*
	The function is the d'tor of the class
	input: The exception message
	output: the ruined class
	*/
	~OpcodeNumOfVarsException() = default;


	/*
	The function is the function that conatine the exception message
	(It is the function that I used to override and get to the outside
	classes the content of the exception message)
	Input: none
	Output: The exception message.

	*/

	virtual const char* what() const  noexcept override { return _excMsg.c_str(); }
};