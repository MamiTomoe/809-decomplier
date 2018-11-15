#include "FindArchitcture.hpp"

/*
The function is getting in all the architctures of assembly (x64,x86,x80886,x80008)
input: none
output: none
*/

void FindArchitcture::get_arictutre_for_map() 
{
	_architctures["r"] = "x64";
	_architctures["e"] = "x86";
	_architctures["x"] = "x8086";
	_architctures["l"] = "x8086";
	_architctures["h"] = "x8086";
	_architctures["A"] = "x80008";
	_architctures["B"] = "x80008";
	_architctures["C"] = "x80008";
	_architctures["D"] = "x80008";
}