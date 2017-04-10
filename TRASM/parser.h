/*
**
** Made by T4lus
** Trinary ASM OPCODE
** 
*/

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

#include <tryte.h>

#include "opcodes.h"
#include "types.h"


class Parser {
private:
	std::string 				inFile;
	std::string 				outFile;

	int							nbError = 0;
	std::vector<std::string> 	errors;
	
	maps_t						maps;

public:
	Parser(std::string _inFile, std::string _outFile);
	
	int parse();

	void buildSizeMap();
	void buildLabelMap();

	static std::vector<args_type_t> GetArgType(std::vector<std::string>);
	static Tryte GetRegisterAddress(std::string);

	static std::vector<Tryte> NOP(std::vector<std::string>, maps_t);	
	static std::vector<Tryte> HLT(std::vector<std::string>, maps_t);
	static std::vector<Tryte> MOV(std::vector<std::string>, maps_t);
	static std::vector<Tryte> DB(std::vector<std::string>, maps_t);
	
	static std::vector<Tryte> CMP(std::vector<std::string>, maps_t);
	
	static std::vector<Tryte> JMP(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JC(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JNC(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JUC(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JZ(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JNZ(std::vector<std::string>, maps_t);
	static std::vector<Tryte> JUZ(std::vector<std::string>, maps_t);

	static std::vector<Tryte> PUSH(std::vector<std::string>, maps_t);
	static std::vector<Tryte> POP(std::vector<std::string>, maps_t);
	static std::vector<Tryte> CALL(std::vector<std::string>, maps_t);
	static std::vector<Tryte> RET(std::vector<std::string>, maps_t);

	static std::vector<Tryte> INC(std::vector<std::string>, maps_t);
	static std::vector<Tryte> DEC(std::vector<std::string>, maps_t);
	static std::vector<Tryte> ADD(std::vector<std::string>, maps_t);
	static std::vector<Tryte> SUB(std::vector<std::string>, maps_t);
	static std::vector<Tryte> MUL(std::vector<std::string>, maps_t);
	static std::vector<Tryte> DIV(std::vector<std::string>, maps_t);

	static std::vector<Tryte> AND(std::vector<std::string>, maps_t);
	static std::vector<Tryte> OR(std::vector<std::string>, maps_t);
	static std::vector<Tryte> XOR(std::vector<std::string>, maps_t);

	static std::vector<Tryte> NOT(std::vector<std::string>, maps_t);
	static std::vector<Tryte> NOTT(std::vector<std::string>, maps_t);
	static std::vector<Tryte> NOTF(std::vector<std::string>, maps_t);

	static std::vector<Tryte> SHL(std::vector<std::string>, maps_t);
	static std::vector<Tryte> SHR(std::vector<std::string>, maps_t);
	
};


#endif