#include "Types.hpp"



/*
The function is the c'tor of the class.
@input: none
@output: The built class
*/
Types::Types()
{
	setTypesInMap();
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