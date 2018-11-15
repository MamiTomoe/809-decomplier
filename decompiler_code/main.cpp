#include "ReadFile.hpp"
#include <iostream>
using std::cout;

int main(void) 
{
	//For debug purpous only.
	ReadFile* r(new ReadFile("C:\\Users\\Mami\\source\\repos\\Decompiler\\Test_Text.txt"));
	vector<string> lines(r->read());
	for (const auto& line : lines) {
		cout << line.c_str() << '\n';
	}
	getchar();
	return 0;
}