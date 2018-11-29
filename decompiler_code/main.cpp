#include "ReadFile.hpp"
#include "FindArchitcture.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main(void) 
{
	//For debug purpous only.
	ReadFile* r(new ReadFile("C:\\Users\\Mami\\source\\repos\\Decompiler\\Test_Text.txt"));
	
	vector<string> lines(r->read());
	
	for (const auto& line : lines) {cout << line.c_str() << '\n';}
	
	
	FindArchitcture* fa( new FindArchitcture(lines[2]));
	string arch = fa->getFileArch();
	cout << arch << endl;
	

	getchar();
	return 0;
}