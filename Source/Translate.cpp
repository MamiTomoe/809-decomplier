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
	pushIntoTheJumpArray();
	parseStackFrame();
	if (_stackFrame.empty()){
		std::string exc = "There is no stack frame found";
		throw StackFrameException(exc);
	}
	parseVaraibles();
	
	translateFunction(); 
	translateSymobls();
	translateMain();
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
		if(isJmpOpcode(insturction.second))
		{
			translateElse(i);
		}

		else if (auto isLoop(insturction.second.find(LOOP_INSTRCION)); isLoop != std::string::npos)//Find if contains the loop (while) instrcution
		{
			translateWhile(i);
		}
		
		else if (auto find = _foundSymbols.find(insturction.second); isOpcodeIsASymbol(find)) {


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

		auto foundFunction(findInVector(_insturctions, functionName));

		if (isItInsturction(foundFunction) && !isItPartOfJumpArray(foundFunction->second))//In the future When it can search for a stack frame , It will support jmp 
		{
				 functionNumOfVars = parseTheNumOfVarsOfTheFunction(foundFunction->first); 
				// _functionInformation[functionName.second] = std::make_pair("int", functionNumOfVars);
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
			setFunctionVars(function.second.second.size() );//The functtions num of vars
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
				if (isPartOfStackFrame(std::make_pair(find->first,find->second.second))) { break; }

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

		if (auto  findInsturction(findInVector(_stackAndHeapVars, instruction)); findInsturction != _stackAndHeapVars.end()) {
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

					_stackFrame.emplace_back(instruction.first, instruction.second);
			}
			
		}
		else {


			if (auto findInSrcVars = findInVector(_srcVars, instruction),  findInDstVars(findInVector(_dstVars, instruction)); findInSrcVars != _srcVars.end())
			{
				
				if (!isFunctionVar(findInDstVars->second) && !isFunctionVar(findInSrcVars->second))
				{

					if (auto e = std::regex("(r|e)(sp|bp)"); std::regex_match(findInSrcVars->second, e)  || std::regex_match(findInDstVars->second , e) && isConnectedToOpcodeVars(instruction.second)) {
						_stackFrame.emplace_back(instruction.first, instruction.second);
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
	
	return findInVector !=  givenVector.end() ?  findInVector : givenVector.end();
}

/*
The function is translating the inside of the translated function.
input: function's name - const std::string
output: none
*/

void Translate::translateInsideOfFunction(const std::string& functionName)
{

	//	findIndexOfTheCurrFunctionCall()
	//	auto indexOfFunction = std::distance(_forFuckingTranslate.begin() , findInVector(_forFuckingTranslate, ))
	
	for (int i = 0; i < _forFuckingTranslate.size(); ++i)
	{
		if (auto find = _forFuckingTranslate[i].second.find(functionName + ":"); find != std::string::npos) 
		{
			std::cout << "\n{\n";
			while (i < _forFuckingTranslate.size() && RETURN_OPCODE != _forFuckingTranslate[i].second) //If it is a ret or if the size
				//is smaller
			{
				
				
				if (!isPartOfStackFrame(std::make_pair(_forFuckingTranslate[i].first, _forFuckingTranslate[i].second))) 
				{
					if (auto isSymbol(_foundSymbols.find(_forFuckingTranslate[i].second)); isOpcodeIsASymbol(isSymbol))
					{
						auto currInstruction(findInVector(_insturctions, _forFuckingTranslate[i]));//Already know from parsing
						translateCurrentSymbol(*currInstruction);
					}
					else if(isJmpOpcode(_forFuckingTranslate[i].second)) 
					{//Try this
						auto index = std::distance(_insturctions.begin(), findInVector(_insturctions, _forFuckingTranslate[i]));
							translateElse(index);
					}
				}
				else if (MAKES_LOCAL_VARS_OPCODE == _forFuckingTranslate[i].second)
				{
					//auto indexOfLocalVars(findInVector(_))
				}
				++i;
			}
			std::cout << "\treturn " << _theARegister << ";\n}\n";
			break;
		}

		
	}
}

/*
The function is parsing the varibles from the vector.(That got from the heap and stack vars)
input: none
output: none
*/

void Translate::parseVaraibles() {
	
	int numOfVar = 1;//Starting from first var

	for (auto& insturction : _insturctions)
	{
		if (!isPartOfStackFrame(insturction))
		{
			if (PUSH_OPCODE == insturction.second) {


				if (auto findSpecificNum(findInVector(_stackAndHeapVars, insturction)); findSpecificNum != _stackAndHeapVars.end())
				{
					if (isIntVar(findSpecificNum->second)) {
						//TODO: until the types class to find the right type it is an defualt type.
						pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second, DEFUALT_TYPE);

					}

					else if (auto typeResult(typesMapResult(insturction.second)); typeResult != _types.end()) {
						pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second, typeResult->second);
					}

					else {
						pushToVarsVector(findSpecificNum->first, "a" + std::to_string(numOfVar), findSpecificNum->second, DEFUALT_TYPE);
					}

					numOfVar++;//Next the num of vars.
				}
			}

			
			}
		else if (MAKES_LOCAL_VARS_OPCODE == insturction.second) {


			if (isPartOfStackFrame(insturction)) {

				if (auto findTheNumOfTheLocalVars(findInVector(_dstVars, insturction));  findTheNumOfTheLocalVars != _dstVars.end()) {
					auto numOfLocals(findInVector(_srcVars, insturction));
					int num = std::stoi(numOfLocals->second);//Not recommend , THis is exploited way, the better way in boost
					makeLocalVars(findTheNumOfTheLocalVars->first,  num);
				}
			}

			if (auto isFloatOrDoubleVar(findInVector(_floatAndDoubleVars, insturction)); isFloatOrDoubleVar != _floatAndDoubleVars.end()) {
				pushToVarsVector(isFloatOrDoubleVar->first, "a" + std::to_string(numOfVar), isFloatOrDoubleVar->second, "float");
			}
			//TODO: parse pointer vars.

			std::string gotType = checkIfHasAlreadyType(insturction);
			if (!gotType.empty()) {
				pushToVarsVector(insturction.first, "a" + std::to_string(numOfVar), "0", gotType);//The null byte for all the type + gotten type
			}


			//else if(auto isGotTypeAlready(_types.f))
		}

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
input: parserPair and currIndex - const parserPair  and const int&
output: none
*/

void  Translate::translateCondition(const parserPair& p , const int& index)
{
	auto srcVar(findInVector(_srcVars,p)) , destVar(findInVector(_dstVars, p));

	auto whichCondition(_foundSymbols.find(_insturctions[index + 1].second));

	if (auto theCondition(_foundSymbols.find(_insturctions[index].second)); theCondition != _foundSymbols.end() && whichCondition != _foundSymbols.end()) 
	{
		
		std::cout <<"\t" << theCondition->second.first  << srcVar->second << " " << whichCondition->second.first << "  " << destVar->second << ")";
	
		if (auto  getLabel(findInVector(_oneOpcodeVars, _insturctions[index + 1])); getLabel != _oneOpcodeVars.end()) {
			
			std::cout << "\n\t{\n";
			translateLabel(*getLabel);
			std::cout << "\n\t}\n";
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

		else if (isItPartOfJumpArray(currInstrctuion.second)) //If it is part of jump (importat to skip) or else 
		{
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
	 parserPair source, dest;
	auto src(findInVector(_srcVars, instruction)), dst(findInVector(_dstVars, instruction));//Finding first the src and dst

	//Using this , so it only change the source of parserPair and not the instrction itself so does the dest
	source = *src;
	dest = *dst;

	if (auto isFunctionVar(_functionVars.find(src->second)); isPartOfFunctionVars(isFunctionVar)) { source.second = isFunctionVar->second; }

	else if(auto isFunctionVar(_functionVars.find(dst->second)); isPartOfFunctionVars(isFunctionVar)) { dest.second = isFunctionVar->second; }

	translateDstAndSrcSymbols(dest, source, opcode);
}

 /*
 The function is translating  one opocde var.
 input: translation and the one opcode var - const  string& , const parserPair& 
 output: none
 */

 void Translate::translateOneOpcodeSymbol(const std::string& translation , const parserPair& instrction)
 {
	 parserPair opcode;
	 auto theVar(findInVector(_oneOpcodeVars, instrction));

	 opcode = *theVar;

	 if (auto isFunctionVar(_functionVars.find(theVar->second)); isPartOfFunctionVars(isFunctionVar)) { opcode.second = isFunctionVar->second; }

	 if (DEC_OPCODE != instrction.second && INC_OPCODE != instrction.second && NOT_OPCODE != instrction.second) {
		 std::cout << '\t' << _theARegister << " " << translation << "= " << opcode.second << ";\n";
	 }

	 else {
		 std::cout << '\t' << opcode.second << translation << ";\n";
	 }
	 
 }

 /*
 The function is translating the labels (for cmp)
 @input: currInsturction - const parserPair&
 @output: none
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

/*
The function is  finding if it one of the jump opcodes
@input: the opcode - const string&
@output: Is it or is not - true or false.
*/

bool Translate::isItPartOfJumpArray(const std::string& opcode)
{
	bool stop = false;
	for (int i = 0; i < MAX_SIZE && !stop; i++)
	{
		if (opcode == _jumpArray[i]) {
			stop = true;
			break;
		}
	}
	return stop == true;
}

/*
The function is  translating else.
@input:  parserPair and currIndex - const parserPair  and const int&
@output: none
*/

void Translate::translateElse( const int& currIndex) 
{
	std::cout << "\telse\n\t{\n";

	if (auto  getLabel(findInVector(_oneOpcodeVars, _insturctions[currIndex])); getLabel != _oneOpcodeVars.end()){
		
		translateLabel(*getLabel);
		std::cout << "\n\t}\n";
	}

}

/*
The function is pushing jumps string into the jump array.
@input: none
@output: none
*/

void Translate::pushIntoTheJumpArray()
{
		_jumpArray[jumpOpcode::basicJump] = "jmp";
		_jumpArray[jumpOpcode::jumpEqual] = "je";
		_jumpArray[jumpOpcode::jumpGreater] = "jg";
		_jumpArray[jumpOpcode::jumpBelow] = "jb";
		_jumpArray[jumpOpcode::jumpLess] = "jl";
		_jumpArray[jumpOpcode::jumpLessEqual] = "jle";
		_jumpArray[jumpOpcode::jumpGreaterEqual] = "jge";
		_jumpArray[jumpOpcode::jumpNotEqual] = "jne";
		_jumpArray[jumpOpcode::jumpAbove] = "ja";
		_jumpArray[jumpOpcode::jumpAboveEqual] = "jae";
}

/*
The function is translting the while loop
@input: currInstruction,  currIndex - const parserPair& and const int&
@output: none
*/

void Translate::translateWhile(const  int& currIndex)
{
	auto getLoop(_foundSymbols.find(_insturctions[currIndex].second));
	std::cout << "\t"<<  getLoop->second.first << "\n\t{\n";
	
	if (auto getLabel(findInVector(_oneOpcodeVars, _insturctions[currIndex])); getLabel != _oneOpcodeVars.end()){
		auto index = std::distance(_forFuckingTranslate.begin(), findInVector(_forFuckingTranslate, _insturctions[currIndex]));//Find the real index of the while in the transaltion vector.
		translateInisdeOfWhile(index - 1, getLabel->second + ":");//For not starting from loop and adding the : for the label itself
		std::cout << "\n\t}\n";
	}
	
}


/*
The function is translating main.
@input: none
@output: none
*/

void Translate::translateMain()
{
	std::cout << "int main(void)";
	translateInsideOfFunction("main");
}

/*
The function is translating inside of a while
@input:  currIndex and label name - const int& , const std::String&
@output: none
*/

void Translate::translateInisdeOfWhile(const int& currIndex , const std::string& labelName)
{
	int  vecIndex = currIndex; 

	while (_forFuckingTranslate[vecIndex].second !=  labelName)
	{
		if (auto isSymbol(_foundSymbols.find(_forFuckingTranslate[vecIndex].second)); isOpcodeIsASymbol(isSymbol))
		{
			auto currInstruction(findInVector(_insturctions, _forFuckingTranslate[vecIndex]));//Already know from parsing
			translateCurrentSymbol(*currInstruction);
		}
		vecIndex--;
	}
}

/*
The function is setting the function vars (to make them more beautufl.
@input the num of the functions var - const int.
@output: none
*/

void Translate::setFunctionVars(const int& numOfFunctionVars)
{
	for (int i = numOfFunctionVars, j = PLUS_VAR_NUM; i > 0; i--, j += PLUS_VAR_NUM)
	{
		_functionVars["[rbp-" + std::to_string(j) + "]"] = "a" + std::to_string(i);//To make the it into the function var
	}
}

/*
The function  is  searching  for a loop for debug  purpous.
@input:  
@output:


std::vector<parserPair>::iterator Translate::findIfLoop(const parserPair& currentInstrctuion)
{
	auto isLoop(std::find_if())

	return 
}
*/

/*
The function is  translating call.
@input: the current index
@output: none
*/

void Translate::translateCall(const int& index)
{

}