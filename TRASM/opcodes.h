/*
**
** Made by T4lus
** Trinary ASM OPCODE
** 
*/

#ifndef OPCODES_H
#define OPCODES_H

#include <functional>

#include "trinary.h"
#include "trit.h"
#include "tryte.h"
#include "tword.h"

#define OP_REGEX			"^[\\t ]*(?:([.A-Za-z0-9_]+[:]))?(?:[\\t ]*([A-Za-z]{2,4})(?:[\\t ]+(\\[[A-Za-z0-9_]+((\\+|-)[0-9]+)?\\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+)(?:[\\t ]*[,][\\t ]*(\\[[A-Za-z0-9_]+((\\+|-)[0-9]+)?\\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?)?)?"

#define TOKEN_COMMENT		'#'
#define TOKEN_LABEL 		':'
#define TOKEN_SEPARATOR 	','
#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

#define T_REGISTER				1
#define T_ADDRESS       		2
#define T_REGISTER_ADDRESS     	4
#define T_CONSTANT      		8

typedef char    args_type_t;

//register list
//{"A", 0},
//{"B", 1},
//{"C", 2},
//{"D", 3}

class Opcodes
{
public:

	static std::vector<args_type_t> GetArgType(std::vector<std::string>);

	static std::vector<Tryte> NOP(std::vector<std::string>);	
	static std::vector<Tryte> HLT(std::vector<std::string>);
	static std::vector<Tryte> MOV(std::vector<std::string>);
	static std::vector<Tryte> DB(std::vector<std::string>);
	
	static std::vector<Tryte> CMP(std::vector<std::string>);
	
	static std::vector<Tryte> JMP(std::vector<std::string>);
	static std::vector<Tryte> JC(std::vector<std::string>);
	static std::vector<Tryte> JNC(std::vector<std::string>);
	static std::vector<Tryte> JZ(std::vector<std::string>);
	static std::vector<Tryte> JNZ(std::vector<std::string>);
	
	static std::vector<Tryte> PUSH(std::vector<std::string>);
	static std::vector<Tryte> POP(std::vector<std::string>);
	static std::vector<Tryte> CALL(std::vector<std::string>);
	static std::vector<Tryte> RET(std::vector<std::string>);

	static std::vector<Tryte> INC(std::vector<std::string>);
	static std::vector<Tryte> DEC(std::vector<std::string>);
	static std::vector<Tryte> ADD(std::vector<std::string>);
	static std::vector<Tryte> SUB(std::vector<std::string>);
	static std::vector<Tryte> MUL(std::vector<std::string>);
	static std::vector<Tryte> DIV(std::vector<std::string>);

	static std::vector<Tryte> AND(std::vector<std::string>);
	static std::vector<Tryte> OR(std::vector<std::string>);
	static std::vector<Tryte> XOR(std::vector<std::string>);

	static std::vector<Tryte> NOT(std::vector<std::string>);
	static std::vector<Tryte> NOTT(std::vector<std::string>);
	static std::vector<Tryte> NOTF(std::vector<std::string>);

	static std::vector<Tryte> SHL(std::vector<std::string>);
	static std::vector<Tryte> SHR(std::vector<std::string>);

};



typedef struct  op_s {
	std::string		opcode;
	char 			nbr_args;
	args_type_t	 	type[4];
	int 			code;
	std::function<std::vector<Tryte>(std::vector<std::string>)>  fct;
} op_t;

extern  std::vector<op_t> op_tab;


#endif