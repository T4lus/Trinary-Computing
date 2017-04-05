
#include "opcodes.h"

// {MNEMONIC, ARGS NUMBER, MODES, TRYTE VALUE, PARSE FUNCTION}
std::vector<op_t> op_tab = {
	{"NOP", 0, {}, -1, &Opcodes::NOP},
	{"HLT", 0, {}, 0, &Opcodes::HLT},
	{"MOV", 2, {T_REGISTER | T_ADDRESS, T_REGISTER | T_ADDRESS | T_CONSTANT}, 1, &Opcodes::MOV},
	{"DB", 1, {T_CONSTANT}, 5, &Opcodes::DB},

	{"CMP", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 20, &Opcodes::CMP},
	
	{"JMP", 1, {T_ADDRESS}, 30, &Opcodes::JMP},
	{"JC", 1, {T_ADDRESS}, 31, &Opcodes::JC},
	{"JNC", 1, {T_ADDRESS}, 32, &Opcodes::JNC},
	{"JZ", 1, {T_ADDRESS}, 33, &Opcodes::JZ},
	{"JNZ", 1, {T_ADDRESS}, 34, &Opcodes::JNZ},

	{"PUSH", 1, {T_REGISTER | T_ADDRESS | T_CONSTANT}, 50, &Opcodes::PUSH},
	{"POP", 1, {T_REGISTER}, 54, &Opcodes::POP},
	{"CALL", 1, {T_ADDRESS}, 55, &Opcodes::CALL},
	{"RET", 0, {}, 57, &Opcodes::RET},
	
	{"INC", 1, {T_REGISTER}, 60, &Opcodes::INC},
	{"DEC", 1, {T_REGISTER}, 65, &Opcodes::DEC},
	{"ADD", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 70, &Opcodes::ADD},
	{"SUB", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 75, &Opcodes::SUB},
	{"MUL", 1, {T_REGISTER | T_ADDRESS | T_CONSTANT}, 80, &Opcodes::MUL},
	{"DIV", 1, {T_REGISTER | T_ADDRESS | T_CONSTANT}, 85, &Opcodes::DIV},

	{"AND", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 90, &Opcodes::AND},
	{"OR", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 95, &Opcodes::OR},
	{"XOR", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 100, &Opcodes::XOR},

	{"NOT", 1, {T_REGISTER}, 105, &Opcodes::NOT},													//STI (U -> U)
	{"NOTT", 1, {T_REGISTER}, 106, &Opcodes::NOTT},													//PTI (U -> T)
	{"NOTF", 1, {T_REGISTER}, 107, &Opcodes::NOTF},													//NTI (U -> F)

	{"SHL", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 110, &Opcodes::SHL},
	{"SHR", 2, {T_REGISTER, T_REGISTER | T_ADDRESS | T_CONSTANT}, 115, &Opcodes::SHR}
};

std::vector<args_type_t> GetArgType(std::vector<std::string> _args) {
	std::vector<args_type_t> args_type;

	for (auto arg : _args) {
		if (!arg.compare('A') || !arg.compare('B') || !arg.compare('C') || !arg.compare('D'))
			args_type.push_back(T_REGISTER);
		if (!arg.compare(0, 1, '[') && !arg.compare(arg.size()-1, 1, ']')) {
			args_type.push_back(T_ADDRESS);
		}
	}

	return args_type;
}

std::vector<Tryte> Opcodes::NOP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {-1};

	return memTab;
}
std::vector<Tryte> Opcodes::HLT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {0};

	return memTab;
}

std::vector<Tryte> Opcodes::MOV(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	int opValue = 1;



	memTab.push_back(opValue);

	return memTab;
}
std::vector<Tryte> Opcodes::DB(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {5};

	return memTab;
}

std::vector<Tryte> Opcodes::CMP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {20};

	return memTab;
}

std::vector<Tryte> Opcodes::JMP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {30};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Opcodes::JC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {31};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Opcodes::JNC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {32};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Opcodes::JZ(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {33};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Opcodes::JNZ(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {34};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}

std::vector<Tryte> Opcodes::PUSH(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {50};

	return memTab;
}
std::vector<Tryte> Opcodes::POP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {54};

	return memTab;
}
std::vector<Tryte> Opcodes::CALL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {55};

	memTab.push_back("FFFFFFFFF");
	memTab.push_back("FFFFFFFFF");
	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Opcodes::RET(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {57};

	return memTab;
}

std::vector<Tryte> Opcodes::INC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {60};

	return memTab;
}
std::vector<Tryte> Opcodes::DEC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {65};

	return memTab;
}
std::vector<Tryte> Opcodes::ADD(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {70};

	return memTab;
}
std::vector<Tryte> Opcodes::SUB(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {75};

	return memTab;
}
std::vector<Tryte> Opcodes::MUL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {80};

	return memTab;
}
std::vector<Tryte> Opcodes::DIV(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {85};

	return memTab;
}

std::vector<Tryte> Opcodes::AND(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {90};

	return memTab;
}
std::vector<Tryte> Opcodes::OR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {95};

	return memTab;
}
std::vector<Tryte> Opcodes::XOR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {100};

	return memTab;
}

std::vector<Tryte> Opcodes::NOT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {105};

	return memTab;
}
std::vector<Tryte> Opcodes::NOTT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {106};

	return memTab;
}
std::vector<Tryte> Opcodes::NOTF(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {107};

	return memTab;
}

std::vector<Tryte> Opcodes::SHL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {110};

	return memTab;
}
std::vector<Tryte> Opcodes::SHR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {115};

	return memTab;
}