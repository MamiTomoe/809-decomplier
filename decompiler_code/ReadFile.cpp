#include "ReadFile.hpp"

/*
The function is reading from the  spefieic file(given path)
input: none
output: none
*/

vector<string> ReadFile::read()
{
	ifstream fileToRead;
	string line;
	vector<string> lines;
	fileToRead.open(_path);
	if (!fileToRead.is_open())
	{
		//TODO: Execption here
	}
	while (fileToRead >> line) { lines.push_back(line); }
	return lines;
}

/*

*/