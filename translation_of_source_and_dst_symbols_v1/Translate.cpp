#include "Translate.hpp"

/*
The function is  the c'tor of the class.
input: function name, stack and heap vars - vector of strings.
	   foundSymbols - map of opcode, its translate and num of vars
output: the build class
*/

Translate::Translate(std::vector<parserPair> stackAndHeapVars, std::vector<parserPair> functionsName,
	std::map<std::string, mapPair> foundSymbols, std::vector<parserPair> srcVars,
	std::vector<parserPair> dstVars, std::string curArch,
	std::vector<parserPair> insturctions, std::vector<contentOfAssemblyFile> forFuckingTranslate) :
	_foundSymbols{foundSymbols}, _functionsName{functionsName},_stackAndHeapVars{stackAndHeapVars}, 
	_srcVars{srcVars},_dstVars{dstVars}, _currArch{curArch}, _insturctions{insturctions},
	_forFuckingTranslate{ forFuckingTranslate}

{
	parseStackFrame();
	if (_stackFrame.empty()){
		//TODO: throw exception
	}
	parseVaraibles();
	parsePushAndPopAndCallWithVars();
	translateFunction(); 
	translateSymobls();
}

/*

*/

std::string Translate::findStackFrame(const std::string& givenStackPointer)
{
	/**
	if (X64_ARCH == _currArch) {
		if()
	}
	*/
	return "";
}

/*
The function is getting the stack farme by the found arch
input:  none
output: none
*/

void Translate::getStackFrameByArch()
{
	//if()
}

/*
The function is translating all of the symbols.
input: none
output: none
*/

void Translate::translateSymobls() 
{
	for (auto& insturction : _insturctions) 
	{
		if (auto find = _foundSymbols.find(insturction.second); find != _foundSymbols.end()) {
			
			auto findInSrcVar(findInVector(_srcVars, insturction));

			auto findInDstVar(findInVector(_dstVars, insturction));

			//If it's part of the src vars and dst vars and not part of the stack frame
			if(findInSrcVar != _srcVars.end()  && findInDstVar != _dstVars.end() && findInVector(_stackFrame, insturction) == _stackFrame.end())
			{
				translateDstAndSrcSymbols(*findInDstVar, *findInSrcVar, insturction.second);
			}
		}
	}
}

/*
The function is translating the function from assembly to pusedo c
input:none
output: none.
*/

void Translate::translateFunction()
{
	int functionNumOfVars = 0;

	for (auto&& functionName : _functionsName) {

			 auto foundFunction(findInVector(_insturctions,functionName));

			 if (foundFunction != _insturctions.end()) {
				 functionNumOfVars = parseTheNumOfVarsOfTheFunction(foundFunction->first); 
				 _functionInformation[functionName.second] = std::make_pair("int", functionNumOfVars);
				 //Giving the defualt return, (int)

				 _improvedFunctionInformation[functionName.second] = std::make_pair("int", getFunctionsVars(foundFunction->first));
			 }
			
	}


	std::cout << "The old way:\n  (Test)";

	for (auto& function : _functionInformation) {
		if (functionNumOfVars)
		{
			std::string varsName;
			for (int i = 0; i < function.second.second; ++i) {
				std::string varNum = std::to_string((i + 1));
				if (i != function.second.second - 1) {//If it is not the last var of the function 
					varsName += "int a" + varNum + ',';
				}
				else {
					varsName += "int a" + varNum;
				}
			}
			std::cout << function.second.first << " " << function.first << '(' + varsName + ')';
		}
		else { std::cout << function.second.first << " " << function.first << '()'; }

		translateInsideOfFunction(function.first);
	}
	
	std::cout << "The new way:`\n";

	for(auto&&  function : _improvedFunctionInformation)
	{
		if (!function.second.second.empty())
		{
			std::string varsName;

			for (int i = 0; i < function.second.second.size(); ++i) {
				if (i == function.second.second.size() - 1)//The last var
				{
					varsName +=  function.second.second[i]._type + " " + function.second.second[i]._name;
				}
				else {
					varsName += function.second.second[i]._type + " " + function.second.second[i]._name + ',';
				}
			}
			
			std::cout << function.second.first << " " << function.first << "(" << varsName << ")";
		}
		else { std::cout << function.second.first << " " << function.first << "()"; }

		translateInsideOfFunction(function.first);
	}

}

/*
The function is parsing the opcode from the old insturction to it's translate in the translation vector
input: none
output: none

void Translate::parseOpcodeWithTranslate()
{
	for (auto opcodeAndTranslation : _foundSymbols) {
		_oldInstructions.push_back(opcodeAndTranslation.first);//The opcode itself (In assembly launage)
		_translatedSymbols.push_back(opcodeAndTranslation.second.first);//It's translation of the certin opcode.
	}
}
*/

/*
The function is pasrsing the num of the vars in the function (that the function contains)
input: the speical index of the  current function name - const int &
output: The num of vars - int
*/

int  Translate::parseTheNumOfVarsOfTheFunction(const int& currFunctionNameSpeicalIndex)
{
	int count = 0;
	
	
	for (int i = findIndexOfTheCurrFunctionCall(currFunctionNameSpeicalIndex) - 1; i >= 0; --i) {//Starting from the last push 
		if ( CALL_OPCODE == _insturctions[i].second) { break; }

		
		if (PUSH_OPCODE == _insturctions[i].second) {

			auto pushInsturction = _insturctions[i];

			auto  find(std::find_if(_pushAndPopAndCallWithVars.begin(),_pushAndPopAndCallWithVars.end(),
				[&pushInsturction](const pushAndPopAndCallParse& pushPair) {return  pushPair.first == pushInsturction.first; }));
			
			
			if (find != _pushAndPopAndCallWithVars.end()) {//Finding the push instcruction  is acuaclly exist (For debugging and problem case)

				//Finding if  it is not the the pointer that the stack uses. ("rbp") , Leave the for
				if (auto found = find->second.second.find(POINTER_THAT_THE_STACK_USE); found != std::string::npos) { break; }

				else { count++; }
			}

			/*
			auto findInStacsVars(findInVarsVector(pushInsturction));
			if (findInStacsVars != _varsVector.end()) {

			}
			*/

		}
	
	}
	

	return count;
}

/*
The function is finding the index of the current function from the vector (insturction)
input: the speical index of the  current function name - const int &
output: The index in the vector itself
*/

int Translate::findIndexOfTheCurrFunctionCall(const int& currFunctionNameSpeicalIndex) 
{
	int index = 0;
	for (int i = 0; i < _insturctions.size(); ++i) {
		if (_insturctions[i].first == currFunctionNameSpeicalIndex) {//The found index of the function index in the vector of insutrctions.
			index = i;
			break;
		}
	}
	return index;
}

/*
The function is parsing the push and pop to be in vector with vars (all vector)
input: none
output: none
*/

void Translate::parsePushAndPopAndCallWithVars()
{
	for (auto&& instruction : _insturctions) {

		auto  findInsturction(findInVector(_stackAndHeapVars, instruction));

		if (findInsturction != _stackAndHeapVars.end()) {
			//TODO: a typedef to the pair of strings
			_pushAndPopAndCallWithVars.push_back(pushAndPopAndCallParse(instruction.first,std::make_pair(instruction.second, findInsturction->second)));
		}
	}
}

/*
The function is parsing the stack frame in the vector (insturction)
input: none
output: none
*/

void Translate::parseStackFrame()
{
	for (auto& instruction  : _insturctions) {


		if (auto  findInStackAndHeapVars = findInVector(_stackAndHeapVars,instruction); findInStackAndHeapVars != _stackAndHeapVars.end())
		{
			if (auto find = findInStackAndHeapVars->second.find(POINTER_THAT_THE_STACK_USE); find != std::string::npos) {

					_stackFrame.push_back(std::make_pair(instruction.first, instruction.second));
			}
			
		}
		else {


			if (auto findInSrcVars = findInVector(_srcVars, instruction); findInSrcVars != _srcVars.end()) {
				if (auto find = findInSrcVars->second.find(POINTER_THAT_THE_STACK_USE); find != std::string::npos) {
					_stackFrame.push_back(std::make_pair(instruction.first, instruction.second));
				}

				if (auto find = findInSrcVars->second.find(STACK_POINTER_REGISTER); find != std::string::npos) {
					_stackFrame.emplace_back(instruction.first, instruction.second);
				}

				else {
					auto findInDstVars(findInVector(_dstVars, instruction));

					if (auto find = findInDstVars->second.find(POINTER_THAT_THE_STACK_USE); find != std::string::npos) {
						_stackFrame.push_back(std::make_pair(instruction.first, instruction.second));
					}

	
				}
			}
		}
		
	}

}

/*
The function is finding the wanted vars (from the vector)
input:  the given vector and the given pair.
output: the found pair.
*/


std::vector<parserPair>::iterator Translate::findInVector(std::vector<parserPair>& givenVector, const parserPair& givenPair)
{
	auto findInVector(std::find_if(givenVector.begin(), givenVector.end(), [givenPair](const parserPair& foundPair)
	{return givenPair.first == foundPair.first; }));
	
	if (findInVector != givenVector.end()) {return findInVector;}
	return givenVector.end();
}

/*
The function is translating the inside of the translated function.
input: function's name - const std::string
output: none
*/

void Translate::translateInsideOfFunction(const std::string& functionName)
{

	//	findIndexOfTheCurrFunctionCall()
	for (int i = 0; i < _forFuckingTranslate.size(); ++i) {
		if (auto find = _forFuckingTranslate[i].second.find(functionName + ":"); find != std::string::npos) {
			std::cout << "{\n";
			while (RETURN_OPCODE != _forFuckingTranslate[i].second) {
				auto find = findInVector(_stackFrame, std::make_pair(_forFuckingTranslate[i].first, _forFuckingTranslate[i].second));
				if (find != _stackFrame.end()) {
					//TODO: translation
				}
				++i;
			}
			std::cout << "}\n";
			break;
		}

		
	}
}

/*
The function is parsing the varibles from the vector.(That got from the heap and stack vars
input: none
output: none
*/

void Translate::parseVaraibles() {
	
	int numOfVar = 0;

	for (auto& insturction : _insturctions) 
	{
		if (PUSH_OPCODE == insturction.second) {

			auto findSpecificNum(findInVector(_stackAndHeapVars, insturction));

			if (findSpecificNum != _stackAndHeapVars.end()) 
			{
				//TODO: until the types class to find the right type it is an defualt type.
				pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second,DEFUALT_TYPE);
				numOfVar++;//Next the num of vars.
			}
		}
		
		else if (MAKES_LOCAL_VARS_OPCODE == insturction.second) {
			
			auto findIfItPartOfTheStackFarme(findInVector(_stackFrame, insturction));

			if (findIfItPartOfTheStackFarme != _stackFrame.end()) {
				
				auto findTheNumOfTheLocalVars(findInVector(_dstVars, insturction));
				if (findTheNumOfTheLocalVars != _dstVars.end()) {

					for (int i = 0; i < std::stoi(findTheNumOfTheLocalVars->second); ++i) 
					{
					
						pushToVarsVector(findTheNumOfTheLocalVars->first, "a" + std::to_string(numOfVar), 
							findTheNumOfTheLocalVars->second,DEFUALT_TYPE);
						numOfVar++;
					}
				}
			}
		}
		//TODO: parse pointer vars.
	}
}

/*
The function is finding  the vars of the speific function.
input: the function's speical index - const int&s
output:  the function's var - vector of vars 
*/

std::vector<varsVector> Translate::getFunctionsVars(const int& functionSpeicalIndex)
{
	std::vector<varsVector> functionsVar; 

	for (int i = findIndexOfTheCurrFunctionCall(functionSpeicalIndex) - 1; i > 0; --i) //Starting after the function's call
	{

		auto currInsturction(_insturctions[i]);
		auto findInStackFrame(findInVector(_stackFrame, currInsturction));

		//If this is part of stack frame  or call  (of other function) break from the function.
		if (findInStackFrame != _stackFrame.end() || CALL_OPCODE == _insturctions[i].second || RETURN_OPCODE == _insturctions[i].second) 
		{ break; }

		else if (PUSH_OPCODE == _insturctions[i].second) {
			auto currInsturction(_insturctions[i]);
			auto findIfThoseAreFunctionsVars(findInVarsVector(currInsturction));

			if (findIfThoseAreFunctionsVars != _varsVector.end()) {
				functionsVar.push_back(*findIfThoseAreFunctionsVars);
			}
		}
	}

	return functionsVar;
}

/*

*/

void Translate::translateDstAndSrcSymbols(const parserPair& dst, const parserPair& src, const std::string&  translation) {
	std::string translated;
	if (OPCODE_THAT_DONT_APPEND_EQUAL != translation) {
		translated = dst.second  + gettingTheTranslatedOpcode(translation) + "=" + src.second;
		std::cout << translated << '\n';
	}
	else
	{
		translated = dst.second +  gettingTheTranslatedOpcode(translation) + src.second;
		std::cout << translated << '\n';
	}
}