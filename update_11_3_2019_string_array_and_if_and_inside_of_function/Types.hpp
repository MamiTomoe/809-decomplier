#pragma once

#include <map>
#include <ctype.h>
#include <string>


class Types
{
public:
	Types();
	~Types();

	//The function is the getter of the types

	inline std::map<std::string, std::string> getTypes() const { return _types; }

private:
	std::map<std::string, std::string> _types;

	void setTypesInMap();
};

