#pragma once
#pragma warning(disable:4996)
#include <map>
#include <algorithm>
#include <string>



#define X64_AND_X86_REGISTERS_LEGTH 3
#define X8086_REGISTERS_LEGTH 2
#define X64_AND_X86_ARCH 0 
#define X8086_ARCH 1
#define X8008_ARCH 0

using std::map;
using std::string;
//using split;


class FindArchitcture {
public:
	FindArchitcture(string fullRegister) { getArictutreForMap(); }

	inline string getFileArch();

	~FindArchitcture() = default;

	FindArchitcture(const FindArchitcture& other) = delete;//So we won't use a copy c'tor
private:
	map<char, string> _architctures;
	void getArictutreForMap();
	void getRegFromString(string fullRegister);
	char _reg;
};