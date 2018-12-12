#include "Logic.hpp"

/*
The  function is  parsing all the info(aka the assembly that we got) from the file  
to  data sturctures(I use vector as for conains the vars).
input:  none
output: none
*/

void Logic::parseAssemblyInfo()
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
	cout << _path << "\nThe file name is: " << _path.filename()  << '\n';
}


/*
The function is getting all the arch into the map (include the object as value)
input:none
output: none
*/

void Logic::putArchOnMap()
{
	_archFound["x80008"] = std::make_unique<X8008Symbols>();
	_archFound["x8086"] = std::make_unique<X8086Symbols>();
	_archFound["x86"] = std::make_unique<X86Symbols>();
	_archFound["x64"] = std::make_unique<X64Symbols>();
}


/*
The function is setting  the assembly content from file into the vector 
input: none
output: none
*/


 void   Logic::setAssemblyFromFile(){ 
	ReadFile temp(_path);
	_assemblyFromFile = temp.read();
	if (isVectorIsEmpty()) {
		//TODO:: Throw exception of problematic file
	}
}


 /**
 c'tor of the class
 input: the assembly from file that was read - vector of strings
 output: new class
 **/

 Logic::Logic()
 {
	 try
	 {
		 checkForUserChoiceForLocalFile();
		 putArchOnMap();
		 setAssemblyFromFile();
		 setCurrentArch();
		 checkAndGetSymbols();

	 }
	 catch (ArchExecption & e) { cout << e.what() << '\n'; }
 }
 
 /*
 The function is a setter for a current arch.
 input:  none
 output: none
 */
 inline  void Logic::setCurrentArch() {
	 FindArchitcture findCurrentArch(_assemblyFromFile);
	 _currentArch = findCurrentArch.getFileArch();
 }
 

/*
The function is getting and setting the symbols(from the given arch).
input: none
output: none
*/

void Logic::checkAndGetSymbols()
{
	if (checkIfArchIsLegal())
	{
		//TODO: Get all the current symbols of the current arch
		auto& currentSymbols =  _archFound[_currentArch];
		//auto currentSymbols = std::make_unique<symbolArchClass>();
		//std::cout << currentSymbols << '\n';
		
	}
	else{throw ArchExecption(_currentArch);}
	
}