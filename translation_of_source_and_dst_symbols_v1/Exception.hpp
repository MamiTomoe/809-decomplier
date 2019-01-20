#pragma once

#include <string>
#include <exception>

class Execption  :  public std::exception {
public:
	//The c'tor of the class
	Execption(std::string excMsg) noexcept: _excMsg{"The error message is: " +excMsg}{ }
	
	//The d'tor of the class
	~Execption() noexcept = default;
	
	virtual const char* what() const noexcept override { return  _excMsg.c_str() ; }

	//The getter of the exception message
	inline std::string getExceptionMessage() { return _excMsg; }

protected:
	std::string _excMsg;
};