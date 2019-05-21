
#include "opcodes.h"
#include "parser.h"


// {MNEMONIC, ARGS NUMBER, MODES, TRYTE VALUE, PARSE FUNCTION}
std::map<std::string, op_t> op_tab = {
	{"HLT", {"HTL", 0, {}, 9126, &Parser::HLT}},
	
	{"NOP", {"NOP", 0, {}, 0, &Parser::NOP}},

	{"MOV", {"MOV", 2, {}, 1, &Parser::MOV}},
	
	{"DT", {"DT",  1, {}, 10, &Parser::DT}},
	{"DW", {"DW",  1, {}, 11, &Parser::DW}},
	{"DTW", {"DTW",  1, {}, 12, &Parser::DTW}},

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
