#include "Types.hpp"



Types::Types()
{
}


Types::~Types()
{
}


/*
The function is getting the types into the map.
input: none
output: none
*/

void Types::setTypesInMap()
{
	_types["byte"] = "char";
	_types["dword"] = "unsigned long";
	_types["word"] = "unsigned short";
}