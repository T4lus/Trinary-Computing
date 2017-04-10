
#include "opcodes.h"
#include "parser.h"


std::map<std::string, int> register_tab = {
	{"A", 1},
	{"B", 2},
	{"C", 3},
	{"D", 4}
};

// {MNEMONIC, ARGS NUMBER, MODES, TRYTE VALUE, PARSE FUNCTION}
std::map<std::string, op_t> op_tab = {
	{"NOP", {"NOP", 0, {}, -1, &Parser::NOP}},
	{"HLT", {"HLT", 0, {}, 0, &Parser::HLT}},
	{"MOV", {"MOV", 2, {}, 1, &Parser::MOV}},
	{"DB",  {"DB",  1, {}, 10, &Parser::DB}},

	{"CMP", {"CMP", 2, {}, 20, &Parser::CMP}},
	
	{"JMP", {"JMP", 1, {}, 30, &Parser::JMP}},
	{"JC",  {"JC",  1, {}, 32, &Parser::JC}},
	{"JNC", {"JNC", 1, {}, 34, &Parser::JNC}},
	{"JUC", {"JUC", 1, {}, 36, &Parser::JUC}},
	{"JZ",  {"JZ",  1, {}, 38, &Parser::JZ}},
	{"JNZ", {"JNZ", 1, {}, 40, &Parser::JNZ}},
	{"JUZ", {"JUZ", 1, {}, 42, &Parser::JUZ}},

	{"PUSH", {"PUSH", 1, {}, 50, &Parser::PUSH}},
	{"POP",  {"POP",  1, {}, 54, &Parser::POP}},
	{"CALL", {"CALL", 1, {}, 55, &Parser::CALL}},
	{"RET",  {"RET",  0, {}, 57, &Parser::RET}},
	
	{"INC", {"INC", 1, {}, 60, &Parser::INC}},
	{"DEC", {"DEC", 1, {}, 61, &Parser::DEC}},
	{"ADD", {"ADD", 2, {}, 70, &Parser::ADD}},
	{"SUB", {"SUB", 2, {}, 75, &Parser::SUB}},
	{"MUL", {"MUL", 1, {}, 80, &Parser::MUL}},
	{"DIV", {"DIV", 1, {}, 85, &Parser::DIV}},

	{"AND", {"AND", 2, {}, 90, &Parser::AND}},
	{"OR",  {"OR",  2, {}, 95, &Parser::OR}},
	{"XOR", {"XOR", 2, {}, 100, &Parser::XOR}},

	{"NOT",  {"NOT",  1, {}, 105, &Parser::NOT}},													//STI (U -> U)
	{"NOTT", {"NOTT", 1, {}, 106, &Parser::NOTT}},													//PTI (U -> T)
	{"NOTF", {"NOTF", 1, {}, 107, &Parser::NOTF}},													//NTI (U -> F)

	{"SHL", {"SHL", 2, {}, 110, &Parser::SHL}},
	{"SHR", {"SHR", 2, {}, 115, &Parser::SHR}}
};

/*
NONE: 0,
MOV REG TO REG: 1,
MOV ADDRESS TO REG: 2,
MOV REGADDRESS TO REG: 3,
MOV REG TO ADDRESS: 4,
MOV REG TO REGADDRESS: 5,
MOV NUMBER TO_REG: 6,
MOV NUMBER TO_ADDRESS: 7,
MOV NUMBER TO_REGADDRESS: 8,

ADD_REG_TO_REG: 10,
ADD_REGADDRESS_TO_REG: 11,
ADD_ADDRESS_TO_REG: 12,
ADD_NUMBER_TO_REG: 13,

SUB_REG_FROM_REG: 14,
SUB_REGADDRESS_FROM_REG: 15,
SUB_ADDRESS_FROM_REG: 16,
SUB_NUMBER_FROM_REG: 17,

INC REG: 18,
DEC REG: 19,

CMP_REG_WITH_REG: 20,
CMP_REGADDRESS_WITH_REG: 21,
CMP_ADDRESS_WITH_REG: 22,
CMP_NUMBER_WITH_REG: 23,

JMP_REGADDRESS: 30,
JMP_ADDRESS: 31,

JC_REGADDRESS: 32,
JC_ADDRESS: 33,

JNC_REGADDRESS: 34,
JNC_ADDRESS: 35,

JZ_REGADDRESS: 36,
JZ_ADDRESS: 37,

JNZ_REGADDRESS: 38,
JNZ_ADDRESS: 39,


PUSH_REG: 50,
PUSH_REGADDRESS: 51,
PUSH_ADDRESS: 52,
PUSH_NUMBER: 53,

POP_REG: 54,

CALL_REGADDRESS: 55,
CALL_ADDRESS: 56,

RET: 57,

MUL_REG: 60,
MUL_REGADDRESS: 61,
MUL_ADDRESS: 62,
MUL_NUMBER: 63,

DIV_REG: 64,
DIV_REGADDRESS: 65,
DIV_ADDRESS: 66,
DIV_NUMBER: 67,

AND_REG_WITH_REG: 70,
AND_REGADDRESS_WITH_REG: 71,
AND_ADDRESS_WITH_REG: 72,
AND_NUMBER_WITH_REG: 73,

OR_REG_WITH_REG: 74,
OR_REGADDRESS_WITH_REG: 75,
OR_ADDRESS_WITH_REG: 76,
OR_NUMBER_WITH_REG: 77,

XOR_REG_WITH_REG: 78,
XOR_REGADDRESS_WITH_REG: 79,
XOR_ADDRESS_WITH_REG: 80,
XOR_NUMBER_WITH_REG: 81,

NOT_REG: 82,

SHL_REG_WITH_REG: 90,
SHL_REGADDRESS_WITH_REG: 91,
SHL_ADDRESS_WITH_REG: 92,
SHL_NUMBER_WITH_REG: 93,

SHR_REG_WITH_REG: 94,
SHR_REGADDRESS_WITH_REG: 95,
SHR_ADDRESS_WITH_REG: 96,
SHR_NUMBER_WITH_REG: 97
*/
