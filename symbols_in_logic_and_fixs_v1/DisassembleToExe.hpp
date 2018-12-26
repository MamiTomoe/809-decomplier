#pragma once

#include <Windows.h> 
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class DisassembleToExe {
public:
	DisassembleToExe(fs::path p);
	~DisassembleToExe() = default;
private: 
	fs::path _path;
	
};