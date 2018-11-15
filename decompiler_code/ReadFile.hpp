#pragma once
#include <filesystem>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//TODO: Change the name
using namespace std::experimental::filesystem::v1;
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;

class ReadFile {
public:
	/*The function is the c'tor of the class
	 * Input: path 
	 * output: the new class.
	 */
	ReadFile(path path) :_path(path) {};
	
	/*
	* The function is the d'tor of the class
	*input: none
	* output: the defualt ruined class
	*/
	~ReadFile() = default;


	//The function is deleting 
	ReadFile(const ReadFile& cp) = delete;

	inline  path  getPath() { return _path; }
	
	vector<string> read();
private:
	path _path;
};