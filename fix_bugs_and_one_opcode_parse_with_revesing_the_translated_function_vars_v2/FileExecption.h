#pragma once
#include "Exception.hpp"

class FileExecption : public Execption  
{
public:
	FileExecption(std::string excMsg) : Execption{ excMsg } {}
	~FileExecption() = default;


	virtual const char* what() const noexcept override { return  _excMsg.c_str(); }
};

