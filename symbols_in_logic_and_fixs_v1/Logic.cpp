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
The function is getting the wanted path from the user
input:  none
output: none

*/

void Logic::getPathFromTheUser()
{
	string fileName;
	cout << "Welcome to the Yuval's decompiler! Please enter the file's name: ";
	cin >> fileName;	
	if (fileName.empty()) { FileExecption("There is no file name and path!"); }
	else { _path = fileName; }
}


/*
The function is getting all the arch into the map (include the object as value)
input:none
output: none
*/

void Logic::putArchOnMap()
{
	//First making the rest of the uniq ptrs(withouth the X8008Symbols)
	std::unique_ptr<X8086Symbols> X8086 = std::make_unique<X8086Symbols>();
	std::unique_ptr<X86Symbols> X86 = std::make_unique<X86Symbols>();
	std::unique_ptr<X64Symbols> X64 = std::make_unique<X64Symbols>();

	_archFound["x80008"] = std::make_unique<X8008Symbols>( );

	//Reset is replacing the old unique pointer to a new one
	//static cast otherwise it won't work and uniq ptr
	_archFound["x8086"] = std::unique_ptr<X8008Symbols>{ static_cast<X8008Symbols*>(X8086.release()) };
	
	_archFound["x86"] = std::unique_ptr<X8008Symbols>{static_cast<X8008Symbols*>(X86.release())};
	_archFound["x64"] = std::unique_ptr<X8008Symbols>{static_cast<X8008Symbols*>(X64.release())};
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
		 getPathFromTheUser();
		 putArchOnMap();
		 setAssemblyFromFile();
		 setCurrentArch();
		 checkAndGetSymbols();

	 }
	 catch (ArchExecption & ae) { cout << ae.what() << '\n'; }
	 catch (FileExecption & fe) { cout << fe.what() << '\n'; }
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
	
		auto&& tempMap = _archFound[_currentArch].get()->getCurrentSymbols();

		for (auto& symbol : tempMap)
		{
			std::cout << "In assembly: " << symbol.first<< " In pesudo C: " << symbol.second << '\n';
		}
		
		//std::cout << currentSymbols << '\n';
		
	}
	else{throw ArchExecption(_currentArch);}
	
}