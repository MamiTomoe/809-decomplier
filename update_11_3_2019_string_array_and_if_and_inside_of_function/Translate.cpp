#include "Translate.hpp"

/*
The function is  the c'tor of the class.
input: function name, stack and heap vars - vector of strings.
	   foundSymbols - map of opcode, its translate and num of vars
output: the build class
*/

Translate::Translate(std::vector<parserPair> stackAndHeapVars, std::vector<parserPair> functionsName,
	std::map<std::string, mapPair> foundSymbols, std::vector<parserPair> srcVars,
	std::vector<parserPair> dstVars,
	std::vector<parserPair> insturctions, std::vector<contentOfAssemblyFile> forFuckingTranslate,
	std::vector<parserPair> floatAndDoubleVars,std::map<std::string,std::string> types, std::vector<parserPair> oneOpcodeVars
 , std::string theARegister) :
	_foundSymbols{foundSymbols}, _functionsName{functionsName},_stackAndHeapVars{stackAndHeapVars}, 
	_srcVars{srcVars},_dstVars{dstVars}, _insturctions{insturctions},
	_forFuckingTranslate{ forFuckingTranslate}, _floatAndDoubleVars{floatAndDoubleVars} , _types{types},
	_oneOpcodeVars{oneOpcodeVars}, _theARegister{ theARegister}

{
	parseStackFrame();
	if (_stackFrame.empty()){
		//TODO: throw exception
	}
	parseVaraibles();
	
	translateFunction(); 
	translateSymobls();
}


/*
The function is translating all of the symbols.
input: none
output: none
*/



void Translate::translateSymobls() 
{
	size_t i = 0;
	

	for_indexed_m(i,const auto& insturction : _insturctions)
	{
		if (auto find = _foundSymbols.find(insturction.second); find != _foundSymbols.end()) {


			
			auto findInSrcVar(findInVector(_srcVars, insturction));

			auto findInDstVar(findInVector(_dstVars, insturction));

			//If it's part of the src vars and dst vars and not part of the stack frame
			if (!isPartOfStackFrame(insturction))
			{
				 if (CMP_OPCODE == insturction.second)
				 {
					translateCondition(insturction , i);
				 }
				else if (findInSrcVar != _srcVars.end() && findInDstVar != _dstVars.end())
				{
						translateDstAndSrcSymbols(*findInDstVar, *findInSrcVar, insturction.second);
				}
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

	
	for(auto&&  function : _improvedFunctionInformation)
	{
		if (!function.second.second.empty())
		{
			std::string varsName;

			//From the last var  to the first
			for (int i = (int)function.second.second.size() - 1; i >=  0 ; --i) {
				if (!i)//The last var that it prints (aka the first var in the vector)
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
			if (auto find(findInStackAndHeapVars->second.find(POINTER_THAT_THE_STACK_USE)); find != std::string::npos) {

					_stackFrame.push_back(std::make_pair(instruction.first, instruction.second));
			}
			
		}
		else {


			if (auto findInSrcVars = findInVector(_srcVars, instruction); findInSrcVars != _srcVars.end()) {
				auto findIfThisIsNotAVar(findInSrcVars->second.find(IN_STACK_VAR));

				if (auto find = findInSrcVars->second.find(POINTER_THAT_THE_STACK_USE); find != std::string::npos && findIfThisIsNotAVar == std::string::npos) 
				{
					_stackFrame.push_back(std::make_pair(instruction.first, instruction.second));
				}

				if (auto find = findInSrcVars->second.find(STACK_POINTER_REGISTER); find != std::string::npos) {
					_stackFrame.emplace_back(instruction.first, instruction.second);
				}

				else {
					auto findInDstVars(findInVector(_dstVars, instruction));

					if (auto find = findInDstVars->second.find(POINTER_THAT_THE_STACK_USE); find != std::string::npos && !isFunctionVar(findInDstVars->second)) {
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
	for (int i = 0; i < _forFuckingTranslate.size(); ++i)
	{
		if (auto find = _forFuckingTranslate[i].second.find(functionName + ":"); find != std::string::npos) 
		{
			std::cout << "\n{\n";
			while (RETURN_OPCODE != _forFuckingTranslate[i].second) 
			{
				
				
				if (!isPartOfStackFrame(std::make_pair(_forFuckingTranslate[i].first, _forFuckingTranslate[i].second))) 
				{
					if (auto isSymbol(_foundSymbols.find(_forFuckingTranslate[i].second)); isOpcodeIsASymbol(isSymbol))
					{
						auto currInstruction(findInVector(_insturctions, _forFuckingTranslate[i]));//Already know from parsing
						translateCurrentSymbol(*currInstruction);
					}
				}
				++i;
			}
			std::cout << "\treturn " << _theARegister << ";\n}\n";
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


			if (auto findSpecificNum(findInVector(_stackAndHeapVars, insturction)); findSpecificNum != _stackAndHeapVars.end())
			{
				if (isIntVar(findSpecificNum->second)){
					//TODO: until the types class to find the right type it is an defualt type.
					pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second, DEFUALT_TYPE);
					
				}

				else {
					pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second, DEFUALT_TYPE);
				}

				numOfVar++;//Next the num of vars.
			}
		}
		
		else if (MAKES_LOCAL_VARS_OPCODE == insturction.second) {
			

			if (isPartOfStackFrame(insturction)) {
				
				if (auto findTheNumOfTheLocalVars(findInVector(_dstVars, insturction));  findTheNumOfTheLocalVars != _dstVars.end()) {

					makeLocalVars(findTheNumOfTheLocalVars->first, numOfVar);
				}
			}

			if (auto isFloatOrDoubleVar(findInVector(_floatAndDoubleVars, insturction)); isFloatOrDoubleVar != _floatAndDoubleVars.end()) {
				pushToVarsVector(isFloatOrDoubleVar->first, "a" + std::to_string(numOfVar), isFloatOrDoubleVar->second, "float");
			}
		}
		//TODO: parse pointer vars.

		std::string gotType = checkIfHasAlreadyType(insturction);
		if (!gotType.empty()) {
			pushToVarsVector(insturction.first, "a" + std::to_string(numOfVar), "0" ,gotType);//The null byte for all the type + gotten type
		}

		
		//else if(auto isGotTypeAlready(_types.f))
	}

	parsePushAndPopAndCallWithVars();
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

		//If this is part of stack frame  or call  (of other function) break from the function.
		if (isPartOfStackFrame(currInsturction) || CALL_OPCODE == _insturctions[i].second || RETURN_OPCODE == _insturctions[i].second) 
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
The function is translating the the opcode into (the dest and source symbols) into c type like
@input: dest , source and opcode - const parserPair& const parserPair&  const string&
@ouput: none
*/

void Translate::translateDstAndSrcSymbols(const parserPair& dst, const parserPair& src, const std::string& opcode) {
	std::string translated;
	if (OPCODE_THAT_DONT_APPEND_EQUAL != opcode) {
		translated = '\t'+ dst.second  + gettingTheTranslatedOpcode(opcode) + "=" + src.second;
		std::cout << translated << ";\n";
	}
	else
	{
		translated = '\t' + dst.second +  gettingTheTranslatedOpcode(opcode) + src.second;
		std::cout << translated << ";\n";
	}
}

/*
The function is  checking if the type is from existing type.
input: The speific pair - parse pair
output: if it has a type or  hasn't type (from the map of types) - true or false
*/

std::string Translate::checkIfHasAlreadyType(const parserPair& pair)
{
	std::string gottenType = "";
	for (const auto& type : _types)
	{
		if (auto isTypeAnnouced(pair.second.find(type.first)); isTypeAnnouced != std::string::npos){

			gottenType = type.second;
			break;
		}
	}

	return gottenType;
}

/*
The function is making the locals vars of function
@input: the num of locals var and currNumOfVar - int
@output: none
*/

void Translate::makeLocalVars(const int& numOfLocalsVars , int& currNumOfVar)
{
	for (int i = 0; i < numOfLocalsVars; ++i){
		pushToVarsVector(numOfLocalsVars, "b" + std::to_string(currNumOfVar),"0", DEFUALT_TYPE);
		currNumOfVar++;
	}
}

/*
The function is translation  a  given condition from assembly to pusedo c
input: oarserPair and currIndex - const parserPair  and const int&
output: none
*/

void  Translate::translateCondition(const parserPair& p , const int& index)
{
	auto srcVar(findInVector(_srcVars,p)) , destVar(findInVector(_dstVars, p));

	auto whichCondition(_foundSymbols.find(_insturctions[index + 1].second));

	if (auto theCondition(_foundSymbols.find(_insturctions[index].second)); theCondition != _foundSymbols.end() && whichCondition != _foundSymbols.end()) 
	{
		
		std::cout << theCondition->second.first  << srcVar->second << " " << whichCondition->second.first << "  " << destVar->second << ")";
	
		if (auto  getLabel(findInVector(_oneOpcodeVars, _insturctions[index + 1])); getLabel != _oneOpcodeVars.end()) {
			
			std::cout << "\n{\n";
			translateLabel(*getLabel);
			std::cout << "}\n";
		}
	}


}

/*
The function is translating the current  symbol
@input: the instsruction - const parserPair&
@output: none
*/

void Translate::translateCurrentSymbol(const parserPair& currInstrctuion)
{

		if (CMP_OPCODE == currInstrctuion.second) {//If the currInstrction is a  conditon

			//Finding the index of the curr instrction
			auto index = std::distance(_insturctions.begin(), findInVector(_insturctions, currInstrctuion)); 

			translateCondition(currInstrctuion, index);
		}
	
		else
		{
			auto symbol(_foundSymbols.find(currInstrctuion.second));

			switch (symbol->second.second)
			{
			case opcodeVar::oneOpcodeVar:
				translateOneOpcodeSymbol(symbol->second.first, currInstrctuion);
				break;
			case opcodeVar::twoOpcodeVars:
				translateDstAndSrcSymbols(symbol->first, currInstrctuion);
				break;
			default:
				break;
			}
		}
}

/*
The function is  a function that get the translation and find the src and dest vars and translate it.
@input: the opcode and the current instrcution - const string &  , const parserPair&
@output: none
*/

 void Translate::translateDstAndSrcSymbols(const std::string& opcode , const parserPair& instruction)
{
	auto src(findInVector(_srcVars, instruction)), dst(findInVector(_dstVars, instruction));
	translateDstAndSrcSymbols(*dst, *src, opcode);
}

 /*
 The function is translating  one opocde var.
 input: translation and the one opcode var - const  string& , const parserPair& 
 output: none
 */

 void Translate::translateOneOpcodeSymbol(const std::string& translation , const parserPair& instrction)
 {
	 auto theVar(findInVector(_oneOpcodeVars, instrction));

	 if (DEC_OPCODE != instrction.second && INC_OPCODE != instrction.second) {
		 std::cout << '\t' << _theARegister << " " << translation << "= " << theVar->second << ";\n";
	 }

	 else {
		 std::cout << '\t' << theVar->second << translation << ";\n";
	 }
	 
 }

 /*
 The function is translating the labels (for cmp)
 @input:
 @output: 
 */

 void Translate::translateLabel(const parserPair& currInsturction)
 {
	 int i = findLabelOrFunctionIndex(currInsturction.second);

	 for (i += 1; i < _forFuckingTranslate.size(); ++i)//The after the label
	 {
		 if (auto isLabel = _forFuckingTranslate[i].second.find(":");  isLabel != std::string::npos) { break; }


		 else if(auto isSymbol(_foundSymbols.find(_forFuckingTranslate[i].second)); isOpcodeIsASymbol(isSymbol)){
			 translateCurrentSymbol(_forFuckingTranslate[i]);
		 }
		 
	 }
 }

 /*
 The function is searching for label or function's index
 @input: the  name of the function/label - const string&
 @output: the index - int
 */

int Translate::findLabelOrFunctionIndex(const std::string& functionOrLabel)
{
	 int i = 0 , j = 0; 
	 for_indexed_m(i, auto translate : _forFuckingTranslate)
	 {
		 if (std::string isLabelOrFunction = functionOrLabel + ":";  isLabelOrFunction == translate.second) {
			 j = i;
			 break; 
		 }

	 }
	 
	 return j;
}