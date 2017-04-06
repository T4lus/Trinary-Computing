#include <tryte.h>

#include "parser.h"
#include "opcodes.h"
#include "utils.h"


Parser::Parser(std::string _inFile, std::string _outFile) {
	this->inFile = _inFile;
	this->outFile = _outFile;
}

int Parser::parse1() {
	this->nbError = 0;
	int lineNumber = 0;
	std::cout << "Starting parse 1 ..." << std::endl;

	std::string line;
	std::regex op_reg(OP_REGEX);
	std::smatch m;

	std::ifstream infile(this->inFile.c_str());
	while (std::getline(infile, line)) {
		lineNumber++;
		line = line.substr(0, line.find("#"));
		if (line == "")
			continue;
		line = reduce(line);

		if (regex_match(line, m, op_reg)) {
			std::vector<std::string> ops;
			ops.push_back(std::to_string(lineNumber));
		    for (int i = 1; i < m.size(); i++) {
		    	if (m[i] != "") {
		    		ops.push_back(m[i]);
		    	}
		    }
		    opMap.push_back(ops);
		}
	}

	for (auto op : opMap) {
		for (auto tab : op_tab) {
			if (!tab.opcode.compare(op[opMapCol::mnemonic])) {
				std::cout << op[opMapCol::mnemonic] << "\t : "; 
				std::vector<Tryte> opmem = tab.fct(op);

				for (auto mem : opmem) {
					std::cout << mem.str() << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	std::cout << "Parse 1 done, " << this->nbError << " error(s) detected" << std::endl;		
	if (this->nbError)
		return 1;
	return 0;
}

int Parser::parse2() {
	this->nbError = 0;
	std::cout << "Starting parse 2 ..." << std::endl;

	std::cout << "Parse 2 done, " << this->nbError << " error(s) detected" << std::endl;		
	if (this->nbError)
		return 1;
	return 0;
}

int Parser::compile() {

	return 0;
}

std::vector<args_type_t> Parser::GetArgType(std::vector<std::string> _args) {
	std::vector<args_type_t> args_type;

	for (auto arg : _args) {
		if (!arg.compare("A") || !arg.compare("B") || !arg.compare("C") || !arg.compare("D")) {
			args_type.push_back(T_REGISTER);
		}
		else if (!arg.compare(0, 1, "[") && !arg.compare(arg.size()-1, 1, "]") ) {
			if (!arg.compare("[A]") || !arg.compare("[B]") || !arg.compare("[C]") || !arg.compare("[D]"))
				args_type.push_back(T_REGISTER_ADDRESS);
			else
				args_type.push_back(T_ADDRESS);
		} 
		else if (isInteger(arg) || isHex(arg)) {
			args_type.push_back(T_CONSTANT);
		}
		else {
			args_type.push_back(T_ADDRESS);
		}
	}
	return args_type;
}

std::vector<Tryte> Parser::NOP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {-1};
	return memTab;
}
std::vector<Tryte> Parser::HLT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {0};
	return memTab;
}

/*
REG TO REG: 1,
ADDRESS TO REG: 2,
REGADDRESS TO REG: 3,

REG TO ADDRESS: 4,
REG TO REGADDRESS: 5,

NUMBER TO REG: 6,
NUMBER TO ADDRESS: 7,
NUMBER TO REGADDRESS: 8,
*/
std::vector<Tryte> Parser::MOV(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	int opValue = 1;

	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if ((args_type[0] == T_ADDRESS || args_type[0] == T_REGISTER_ADDRESS) && (args_type[1] == T_ADDRESS || args_type[1] == T_REGISTER_ADDRESS)) {
		throw -1;
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER) {
		memTab.push_back(opValue);
		memTab.push_back(register_tab[_opMap[2]]);
		memTab.push_back(register_tab[_opMap[3]]);
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_ADDRESS) {
		memTab.push_back(opValue + 1);
		memTab.push_back(register_tab[_opMap[2]]);
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER_ADDRESS) {
		memTab.push_back(opValue + 2);
		memTab.push_back(register_tab[_opMap[2]]);
	}
	if (args_type[0] == T_ADDRESS && args_type[1] == T_REGISTER) {
		memTab.push_back(opValue + 3);
	}
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_REGISTER) {
		memTab.push_back(opValue + 4);
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_CONSTANT) {
		memTab.push_back(opValue + 5);
		memTab.push_back(register_tab[_opMap[2]]);
	}
	if (args_type[0] == T_ADDRESS && args_type[1] == T_CONSTANT) {
		memTab.push_back(opValue + 6);
	}
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_CONSTANT) {
		memTab.push_back(opValue + 7);
	}

	return memTab;
}
std::vector<Tryte> Parser::DB(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	
	if (isInteger(_opMap[2])) {
		memTab.push_back(Tryte(stoi(_opMap[2])));
	} 
	else if (isHex(_opMap[2])) {
		memTab.push_back(Tryte( strtoul(_opMap[2].c_str(), NULL, 16) ));
	}
	else {
		_opMap[2] = _opMap[2].substr(1, _opMap[2].size() - 2);
		for (char& c : fromRaw(_opMap[2])) {
			memTab.push_back(Tryte((int)c));
		}
	}
	return memTab;
}

std::vector<Tryte> Parser::CMP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {20};

	return memTab;
}

std::vector<Tryte> Parser::JMP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {30};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Parser::JC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {31};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Parser::JNC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {32};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Parser::JZ(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {33};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Parser::JNZ(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {34};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}

std::vector<Tryte> Parser::PUSH(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {50};

	return memTab;
}
std::vector<Tryte> Parser::POP(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {54};

	return memTab;
}
std::vector<Tryte> Parser::CALL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {55};

	memTab.push_back("FFFFFFFFF");

	return memTab;
}
std::vector<Tryte> Parser::RET(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {57};

	return memTab;
}

std::vector<Tryte> Parser::INC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {60};

	return memTab;
}
std::vector<Tryte> Parser::DEC(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {65};

	return memTab;
}
std::vector<Tryte> Parser::ADD(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {70};

	return memTab;
}
std::vector<Tryte> Parser::SUB(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {75};

	return memTab;
}
std::vector<Tryte> Parser::MUL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {80};

	return memTab;
}
std::vector<Tryte> Parser::DIV(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {85};

	return memTab;
}

std::vector<Tryte> Parser::AND(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {90};

	return memTab;
}
std::vector<Tryte> Parser::OR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {95};

	return memTab;
}
std::vector<Tryte> Parser::XOR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {100};

	return memTab;
}

std::vector<Tryte> Parser::NOT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {105};

	return memTab;
}
std::vector<Tryte> Parser::NOTT(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {106};

	return memTab;
}
std::vector<Tryte> Parser::NOTF(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {107};

	return memTab;
}

std::vector<Tryte> Parser::SHL(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {110};

	return memTab;
}
std::vector<Tryte> Parser::SHR(std::vector<std::string> _opMap) {
	std::vector<Tryte> memTab;
	memTab = {115};

	return memTab;
}