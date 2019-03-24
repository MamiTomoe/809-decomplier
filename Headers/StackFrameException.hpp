#pragma once

#include <iostream>
#include "Exception.hpp"

class StackFrameException : public Execption {
public:
	//The function is a c'tor of the class
	//@input: the exception
	//@output: The built class

	StackFrameException(std::string except) : Execption(except){}

	//The function is the d'tor of the class
	//@input: none
	//@output: The ruined class
	~StackFrameException() = default;

	//The function is a what  function (throws  an error when it has)
	//@input: none
	//@output: the except message - const char*

	
	virtual const char* what() const noexcept override { return _excMsg.c_str(); }
};