#pragma once

#include <map>
#include <vector>
#include <string>


class Translate {
public:
	Translate(std::vector<std::string> currentSymbols) {}
private:
	std::vector<std::string> _translatedSymbols;
	std::vector<std::string> _oldInstructions;
	std::vector<std::string> _functionsName;
	std::vector<std::string> _stackAndHeapVars;
	std::map<std::string, std::pair<std::string, int>> _foundSymbols;

	
	void translateSymobls();


};