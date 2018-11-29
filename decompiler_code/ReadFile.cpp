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
	vector<string> tempForSplit;
	fileToRead.open(_path);
	if (!fileToRead.is_open())
	{
		//TODO: Execption here
	}
	while (fileToRead >> line) { 
		if (auto found = line.find(","); found != string::npos) { 
			split(tempForSplit, line, is_any_of(",")); 
			for ( auto lineSplitted : tempForSplit) { lines.push_back(lineSplitted); }
		}
		else { lines.push_back(line); }
		 
	}
	return lines;
}

/*

*/