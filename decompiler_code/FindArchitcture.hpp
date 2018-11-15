#pragma once
#include <map>
#include <algorithm>
#include <string>

using std::map;
using std::string;

class FindArchitcture {

	FindArchitcture() { get_arictutre_for_map(); }

	~FindArchitcture() = default;
private:
	map<string, string> _architctures;
	void get_arictutre_for_map();
};