#include "Logic.hpp"

/*
The  function is  parsing all the info(aka the assembly that we got) from the file  
to  data sturctures(I use vector as for conains the vars).
input:  none
output: none
*/

void Logic::parseAssemblyInfo()
{
	//bool stop = false;
	for (int   i = 0; i < _assemblyFromFile.size(); ++i)
	{
		//Finding the function that we are working with
		
		if (auto found = _assemblyFromFile[i].find(":"); found != std::string::npos) {
	
			pushIntoTranslationVector(_assemblyFromFile[i], i);

			_functionNames.push_back(parserPair(i,_assemblyFromFile[i]));
		}

		else if (START_FORM_FILE == _assemblyFromFile[i] || END_FROM_FILE == _assemblyFromFile[i]){
			//Not from stack frame from the compiler explorer
		}

		else if (auto found = _foundSymbols.find(_assemblyFromFile[i]); found != _foundSymbols.end())
		{
		
		
			if (isOpcodeVarsFromTheFileAreLegal(found->second.second + i))
			{
				pushIntoTranslationVector(_assemblyFromFile[i], i);
				_insturctions.push_back(parserPair(i, _assemblyFromFile[i]));

				if (isItAOneVarOpcode(found->second.second))
				{
					_oneOpcodeVars.emplace_back(i, _assemblyFromFile[i + pi::oneVarOpcodePlace]);
				}

				else 
				{
				//	_forFuckingTranslate.emplace_back(i, _assemblyFromFile[i]);


					_destVars.push_back(parserPair(i, _assemblyFromFile[i + pi::dstVarIndex]));
					pushIntoTranslationVector(_assemblyFromFile[i + pi::dstVarIndex] , i);

					_sourceVars.push_back(parserPair(i, _assemblyFromFile[i + pi::srcVarIndex]));
					pushIntoTranslationVector(_assemblyFromFile[i +  pi::dstVarIndex] , i);
				}
				i += found->second.second;//Getting to the next things in the file and not the vars of the opcode


			}

				else {
					//stop = true;
					throw OpcodeNumOfVarsException("The num of the opcode is illegal");
				}
		}

		//If it is a "Push" or "call" instrtuion  and it is not the end
		//It is not suppost to be the end  of the vector 
		//but it is a way to check if there is a problem in instrction
		
		//It copies the function's content  here insteand of calling it

		else if (isInstructuionNotLast(i))
		{
			if (auto found = _foundSymbols.find(_assemblyFromFile[i + 1]); found == _foundSymbols.end()) {

				pushIntoTranslationVector(_assemblyFromFile[i], i);
				_insturctions.push_back(parserPair(i,_assemblyFromFile[i]));
				if (PUT_STACK_VARS_IN_ASSEMBLY == _assemblyFromFile[i])
				{
					_stackAndHeapVars.push_back(parserPair(i,_assemblyFromFile[i + pi::functionOrStackVarsIndex]));

					pushIntoTranslationVector(_assemblyFromFile[i + pi::functionOrStackVarsIndex], i);
				}
				else if (FUNCTION_INSTRCATION == _assemblyFromFile[i]) {
					_stackAndHeapVars.push_back(parserPair(i,FUNCTION_INSTRCATION));//To know where the num of the function stops
				
					_functionNames.push_back(parserPair(i,_assemblyFromFile[i + pi::functionOrStackVarsIndex]));
					
					pushIntoTranslationVector(_assemblyFromFile[i + pi::functionOrStackVarsIndex],i);
				}
				else if (REMOVE_STACK_VARS_IN_ASSEMBLY == _assemblyFromFile[i]) {
					_stackAndHeapVars.push_back(parserPair(i,_assemblyFromFile[i + pi::functionOrStackVarsIndex]));

					pushIntoTranslationVector(_assemblyFromFile[i + pi::functionOrStackVarsIndex] , i);
				}
				i += pi::defualtNextIndex;
			}
			else{
				//TODO: exception of  wrong opcode's parameter;
			}
			
		}
		else if (END_FROM_FILE == _assemblyFromFile[i]) { 
			pushIntoTranslationVector(_assemblyFromFile[i], i);

			_insturctions.push_back(parserPair(i,_assemblyFromFile[i])); 
		}
		
		else{
			//stop = true;
			throw OpcodeNumOfVarsException("The number of vars is illegal for the special opcodes");
		}
	}
	
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
	if (isVectorOfAssemblyIsEmpty()) {
		throw FileExecption("There is not any code in assembly to work with!");
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
		 parseAssemblyInfo();
		 translateTheCode();
		

		 for (const auto& i : _stackAndHeapVars) { std::cout << i.first << " and:" << i.second << '\n'; }
		 for (const auto& i : _functionNames) { std::cout << i.first << " and:" << i.second << '\n';}
	 }
	 catch (ArchExecption & ae) { cout << ae.what() << '\n'; }
	 catch (FileExecption & fe) { cout << fe.what() << '\n'; }
	 catch (OpcodeNumOfVarsException& nove) { cout << nove.what() << '\n'; }
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
output: the map that has the translate of the opcode and the number of nums that the opcode conatins
*/
 
void  Logic::checkAndGetSymbols()
{
	if (checkIfArchIsLegal()){
		_foundSymbols = _archFound[_currentArch].get()->getCurrentSymbols();
	}
	else{throw ArchExecption(_currentArch);}
	
}

/*
The function is checking if  the num of vars  of the opcode is legal 
with  the current size of the vector (checks if there is any missing  num of vars
in the vector size).
input: the last index of the opcode's num of vars - int.
output:  If there is missing or not - boolean
*/

bool Logic::isOpcodeVarsFromTheFileAreLegal(const int& lastIndexOfOpcodeNumOfVars)  const{
	return lastIndexOfOpcodeNumOfVars < _assemblyFromFile.size() || lastIndexOfOpcodeNumOfVars != _assemblyFromFile.size();
}

/*
The function is passing a call for the translation class
(with all the information thats it needed) and returens  it's translation
Input: none
Output: The traslated code - vector of strings
*/

std::vector<std::string> Logic::translateTheCode() {
	Translate t(_stackAndHeapVars, _functionNames, _foundSymbols,_sourceVars,_destVars,
		_insturctions,_forFuckingTranslate,_floatAndDoubleVars,_types);
	std::vector<std::string> translatedCode;
	return translatedCode;
}


/*
The function is getting the types from the types class.
input:none
output: none
*/

inline void Logic::getTypesFromTypesClass(){
	Types t;
	_types = t.getTypes();
}
