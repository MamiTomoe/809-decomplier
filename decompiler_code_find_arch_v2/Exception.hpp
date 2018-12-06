#pragma once

#include <string>
#include <exception>

class Execption  : std::exception {
public:
	//The c'tor of the class
	Execption(std::string excMsg) noexcept: _excMsg{"The error message is: " +excMsg}{ }
	
	//The d'tor of the class
	~Execption() noexcept = default;
	
	virtual const char* what() const noexcept override { return  _excMsg.c_str() ; }

private:
	std::string _excMsg;
};