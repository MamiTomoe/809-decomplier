#pragma once

//#include <map>
#include <vector>
#include <string>

class Translate {
public:
	Translate(std::vector<std::string> currentSymbols) {}
private:
	std::vector<std::string> _translatedSymbols;
	//std::map<std::string,std::string> 
	std::vector<std::string> _oldInstructions;
	void translateSymobls();


};