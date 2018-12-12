#pragma once
#include <filesystem>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

//TODO: Change the name
namespace  fs =  std::experimental::filesystem::v1;
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using boost::find;
using boost::is_any_of;
using std::endl;

 


class ReadFile {
public:
	/**The function is the c'tor of the class
	 * Input: path
	 * output: the new class.
	 */
	ReadFile(fs::path path) :_path{path} {};
	
	/*
	* The function is the d'tor of the class
	*input: none
	* output: the defualt ruined class
	*/
	~ReadFile() = default;


	//The function is deleting 
	ReadFile(const ReadFile& cp) = delete;

	inline  fs::path  getPath() { return _path; }
	
	inline void setPath(fs::path  _path) { this->_path = _path; }

	vector<string> read();


private:
	fs::path _path;
};