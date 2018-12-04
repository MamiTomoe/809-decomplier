#include "Logic.hpp"

/*
The  function is  parsing all the info(aka the assembly that we got) from the file  
to  data sturctures(I use vector as for conains the vars).
input: vector of tje assembly that we got from the file.
output: none
*/

void Logic::parseAssemblyInfo(vector<string> assemblyFromFile)
{

}


/*
The funcion is setting the architcture  to the current architcture based of what the decompiler found.
input: none
output: none
*/

void Logic::setCurrentArchitcture()
{

}

/*
The function is getting the user choice  for a local file option
input:  none
output: none

*/

void Logic::checkForUserChoiceForLocalFile()
{
	char chosen;
	string fileName;
	cout << "Welcome to the Yuval's decompiler! would you like to decompile from a local file?(y/n) only\n";
	cin >> chosen;
	cout << "Enter the file's name\n";
	cin >> fileName;	
	chosen = std::tolower(chosen,std::locale());

	if (USER_WANT_LOCAL_FILE == chosen) {_path = fs::current_path().string() +  "/" + fileName;}
	else if (USER_DOESNT_WANT_LOCAL_FILE == chosen){_path  = fileName;}
	else{
		//TODO: execption here
	}
	cout << _path << "\nThe file name is:" << _path.filename()  << '\n';
}
