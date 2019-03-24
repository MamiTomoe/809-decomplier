#pragma once

#include <map>
#include <ctype.h>
#include <string>


class Types
{
public:
	Types();

	/*
	The function is the d'tor of the class
	@input: none
	@output: the ruined class.
	*/
	~Types() = default;

	//The function is the getter of the types

	inline std::map<std::string, std::string> getTypes() const { return _types; }

private:
	std::map<std::string, std::string> _types;

	void setTypesInMap();
};

