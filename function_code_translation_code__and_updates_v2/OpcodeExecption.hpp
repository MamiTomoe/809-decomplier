#pragma once
#include "Exception.hpp"

class OpcodeExecption : public Execption {
public:
	OpcodeExecption(std::string excMsg) noexcept: Execption{excMsg} {}

	~OpcodeExecption()  noexcept = default;

	virtual const char* what() const noexcept override { return _excMsg.c_str(); }
};