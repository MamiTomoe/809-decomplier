#pragma once

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <range.hpp>
#include <array>

#include "StackFrameException.hpp"


#define PUSH_OPCODE "push"
#define CALL_OPCODE "call"
#define RETURN_OPCODE "ret"
#define MAKES_LOCAL_VARS_OPCODE "sub"
#define POINTER_THAT_THE_STACK_USE "bp"
#define STACK_POINTER_REGISTER "sp"
#define DEFUALT_TYPE "int"
#define OPCODE_THAT_DONT_APPEND_EQUAL "mov"
#define IN_STACK_VAR "-"
#define MAX_SIZE_FOR_INT_VAR 1
#define CMP_OPCODE "cmp"
#define INC_OPCODE "inc"
#define DEC_OPCODE "dec"
#define NOT_OPCODE "not"
#define ELSE_CONDITION "jmp"
#define MAX_SIZE 10
#define NOT_OPCODE "not"
#define PLUS_VAR_NUM 4
#define LOOP_INSTRCION "loop"
#define TYPE_INDEX 0

/*Explaine here for the index, it gets the args that needed (Varaditic macro(In our case the args of the map)) and an index. and start
from zero and goes up by the loop(we see in the macro for_indexed_m that there is a for and able to break. It will get the itertaor of the
map*/

#define for_indexed(...)  for_inedex_m(i, __VA_ARGS__)
#define for_indexed_m(m, ...)  for(bool _i_ = true, _break_ = false; _i_;) for(size_t m = 0; _i_; _i_ = false) for(__VA_ARGS__) if(_break_) break; else for(bool _j_ = true; _j_;) for(_break_ = true; _j_; _j_ = false) for(bool _k_ = true; _k_; m++, _k_ = false, _break_ = false)


typedef  std::pair<std::string, int> mapPair;
typedef std::pair<int, std::string>  parserPair;
typedef std::pair<int,std::pair<std::string, std::string>> pushAndPopAndCallParse;

enum opcodeVar {
	oneOpcodeVar  = 1,
	twoOpcodeVars
};

typedef std::pair<int, std::string> contentOfAssemblyFile;

struct varsVector {
	int _index;
	std::string _name;
	std::string _value;
	std::string _type;
};



enum jumpOpcode {
	basicJump,
	jumpEqual,
	jumpGreater,
	jumpBelow,
	jumpLess,
	jumpLessEqual,
	jumpGreaterEqual,
	jumpNotEqual,
	jumpAbove,
	jumpAboveEqual
};

class Translate {
public:

	Translate(std::vector<parserPair> stackAndHeapVars, std::vector<parserPair> functionsName,
		std::map<std::string, mapPair> foundSymbols, std::vector<parserPair> srcVars,
		std::vector<parserPair> dstVars,
		std::vector<parserPair> insturctions, std::vector<contentOfAssemblyFile> forFuckingTranslate,
		std::vector<parserPair> floatAndDoubleVars, std::map<std::string, std::string> types
		, std::vector<parserPair> oneOpcodeVars, std::string theARegister);

	~Translate() = default;


	Translate(const Translate&) = delete;



private:
	std::vector<parserPair> _functionsName;

	std::vector<parserPair> _stackAndHeapVars;


	std::vector<parserPair> _srcVars;

	std::vector<parserPair> _dstVars;

	std::map<std::string, mapPair> _foundSymbols;

	std::vector<parserPair> _insturctions;

	std::vector<std::string> _symbolsInsturctionsThatConatisTwoVars;

	std::vector<pushAndPopAndCallParse> _pushAndPopAndCallWithVars;

	std::vector<varsVector> _varsVector;//Special index, their  name, the value they contains.

	std::vector<parserPair> _stackFrame;//Special index +  the speical register (rbp)

	std::vector<contentOfAssemblyFile> _forFuckingTranslate;

	std::vector<parserPair> _floatAndDoubleVars;

	std::vector<parserPair> _oneOpcodeVars;

	//Taking the name of the function, the type of it and the num of vars
	std::map<std::string, std::pair<std::string, int>> _functionInformation;

	//TODO: If it works, delete the old one and stay with this (change the name of _function impormation)
	std::map<std::string, std::pair<std::string,std::vector<varsVector>>> _improvedFunctionInformation;

	std::map<std::string, std::string> _types;

	std::map<std::string, std::string> _functionVars;

	std::string _theARegister;

	void translateSymobls(); 


	void parsePushAndPopAndCallWithVars();

	int  parseTheNumOfVarsOfTheFunction(const int&);

	void translateFunction();

	void parseStackFrame();

	int findIndexOfTheCurrFunctionCall(const int&);

	std::vector<parserPair>::iterator findInVector(std::vector<parserPair>& givenVec, const parserPair& givenPair);

	void translateInsideOfFunction(const std::string&);
	
	void parseVaraibles();

	//The function is a getter of the translated opcode.
	inline std::string gettingTheTranslatedOpcode(const  std::string& opcodeToTranslate) const {
		return _foundSymbols.at(opcodeToTranslate).first;//The  found opcode from the map returned translation.
	}

	//The pusher to the  vars vector's only.
	//input: the speical index - int, the var's current num and name - string ,  and the value they contains - string
	//and type - std::string
	//output: none
	inline void pushToVarsVector(const int& speicalIndex,const std::string& theVarsName,const std::string& content,const std::string& type){ 
		_varsVector.push_back({ speicalIndex,theVarsName,content , type});
		//Emplament_back does not work it.
	}

	//The function is searching in varVectors for vars.
	//Input: the itertor of the search - parserPair
	//Output: the  found result.

	inline std::vector<varsVector>::iterator findInVarsVector(const parserPair& pp) 
	{
		auto findInVarVector(std::find_if(_varsVector.begin(), _varsVector.end(), [pp](const varsVector& vv)
		{ return vv._index == pp.first; }));
		
		return findInVarVector;
	}

	std::vector<varsVector> getFunctionsVars(const int&);


	//The function is translating all the dest and source part.
	//input: dst string, src string - parserPair and translation string. 
	//output:  none - for debug, it will changed to std::string
	 void translateDstAndSrcSymbols(const parserPair& dst, const parserPair& src, const std::string&  translation);

	 //The function  is checking if the var that  that we get is an acual  int var.
	 //input: var - const string
	 //output: is int var or not
	 inline bool  isIntVar(const std::string& var) const { return var.size() == MAX_SIZE_FOR_INT_VAR && isdigit(var[0]); }

	 std::string checkIfHasAlreadyType(const parserPair& pair);

	 void makeLocalVars(const int& numOfLocalVars , int& currNumOfVar);

	 void  translateCondition(const parserPair&  , const int&);

	 //The function is checking if it is part of stack frame
	 //@input: The instsurction - parserPair
	 //@output: True  or false

	 inline bool isPartOfStackFrame(const parserPair& p)  { return findInVector(_stackFrame, p) != _stackFrame.end();}
		
	 //The function is checking if it is part of stack and heap vars
	 //@input: The instsurction - parserPair
	 //@output: True  or false

	 inline bool isPartOfStackAndHeapVars(const parserPair& p) { return findInVector(_stackAndHeapVars, p) != _stackAndHeapVars.end(); }


	 void translateCurrentSymbol(const parserPair&);

	 //The function is checking if it is part of the symbol map or not
	//@input: The iterator -  const map's itertaor &
	 //@output: true or false

	 inline bool isOpcodeIsASymbol(const std::map<std::string, mapPair>::iterator& it) { return it != _foundSymbols.end(); }


	 //The function is checking if it has any source var 
	 //@input:  the current iterator - const  vector<parserPair>::iterator
	 //@output:  true or false

	// inline bool hasSoruceVar(const std::vector<parserPair>::iterator& it) { return it != _srcVars.end();}

	 //The function is checking if it has any dest var
	 //@input:  the current iterator - const  vector<parserPair>::iterator
	 //@output:  true or false

	 //inline bool hasDestVar()

	inline void translateDstAndSrcSymbols(const std::string& translation  , const parserPair&);

	inline void translateOneOpcodeSymbol(const std::string& translation, const parserPair&);

	void translateLabel(const parserPair&);
	
	int findLabelOrFunctionIndex(const std::string&);
	
	//The function is comparing if the the current label/function is the same given function/label
	//@input: the given function/label names  - const strings&
	//@output: is it equal or not - bool

	inline bool isEqual(const std::string& found, const std::string& given) { return found == given; }

	//The function is checking if it really a stack frame var or a function's var
	//@input: the opcode - const std::string& 
	//@Output: True or false - bool

	inline bool isFunctionVar(const std::string& opcode) {
		auto isFunctionVar(opcode.find(IN_STACK_VAR));
		return isFunctionVar != std::string::npos;
	}


	//Puting all the jump into one array of jumps.
	std::array<std::string, MAX_SIZE > _jumpArray;

	bool isItPartOfJumpArray(const std::string&);

	//The function is checking if it is a JMP opcode (for else)
	//@input: the name of the jump - const string&
	//@outpit: Is it or not - true or false

	inline bool  isJmpOpcode(const std::string& jumpOpcode) const { return _jumpArray[jumpOpcode::basicJump] == jumpOpcode; }

	void translateElse(const int&);

	void pushIntoTheJumpArray();

	//The function is checking if it is an instruction.
	inline bool isItInsturction(const  std::vector<parserPair>::iterator& it) { return it != _insturctions.end(); }

	void translateWhile( const  int& );

	void translateMain();

	void translateInisdeOfWhile(const int& , const std::string&);

	void setFunctionVars(const int&);

	//The function is checking if it part of function's var
	//@input: the result - auto
	//@output: is it or isn't -true or false.
	
	inline bool isPartOfFunctionVars(const std::map<std::string,std::string>::iterator& it) { return it != _functionVars.end(); }

	
	//std::vector<parserPair>::iterator findIfLoop(const parserPair&);

	//The function giving the result from the map type
	//@input:  the string - const std::string
	//@output:  the result - end or found

	inline std::map<std::string, std::string>::iterator typesMapResult(const std::string& givenString) {
		return _types.find(givenString.substr(TYPE_INDEX, givenString.find(' ')));
	}
};
