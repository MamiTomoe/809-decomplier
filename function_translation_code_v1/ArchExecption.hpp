#pragma once

#include <string>
#include <exception>
#include "Exception.hpp"


class ArchExecption : public Execption {
public:
	//C'tor of the class
	ArchExecption(std::string excMsg) noexcept : Execption{ excMsg } { }

	//D'tor of the class
	~ArchExecption() noexcept = default;

	//The override of the what execption
	virtual const char* what() const noexcept override { return  _excMsg.c_str(); }

	
	

};