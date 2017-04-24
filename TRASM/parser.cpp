#include <functional>

#include <tryte.h>

#include "parser.h"
#include "utils.h"


Parser::Parser(std::string _inFile, std::string _outFile) {
	this->inFile = _inFile;
	this->outFile = _outFile;
}

int Parser::parse() {
	this->nbError = 0;
	int lineNumber = 0;
	std::cout << "Starting parse 1 ..." << std::endl;

	std::string line;
	std::regex op_reg(OP_REGEX);
	std::smatch m;

	//load File
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
		    this->maps.opMap.push_back(ops);
		}
	}

	//create size map
	this->buildSizeMap();
	//create size map
	this->buildLabelMap();

	//debug
	std::cout << " === DEBUG === " << std::endl;
	std::cout << " -- label -- " << std::endl;
	for (auto& item : this->maps.labelMap) {
		std::cout << item.first << "\t : " << Tryte(item.second).str() << std::endl;
	}
	std::cout << std::endl;
	std::cout << " -- memory -- " << std::endl;
	for (auto op : this->maps.opMap) {
		if (op_tab.find(op[opMapCol::mnemonic]) != op_tab.end()) {
			std::cout << op_tab[op[opMapCol::mnemonic]].opcode << "\t : ";
			std::vector<Tryte> opmem = op_tab[op[opMapCol::mnemonic]].fct(op, this->maps);
			for (auto mem : opmem) {
				std::cout << mem.str() << " ";
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Parse 1 done, " << this->nbError << " error(s) detected" << std::endl;		
	if (this->nbError)
		return 1;
	return 0;
}

void Parser::buildSizeMap() {
	std::cout << "Building size map" << std::endl;
	for (auto op : this->maps.opMap) {
		int currentSize = 1;
		
		if (op_tab.find(op[opMapCol::mnemonic]) != op_tab.end()) {
			if (op_tab[op[opMapCol::mnemonic]].nb_args < 1) {
				currentSize = 1;
			}else if (op_tab[op[opMapCol::mnemonic]].nb_args < 2) {
				if ( !op_tab[op[opMapCol::mnemonic]].opcode.compare("DB") ) {
					currentSize = this->DB(op, this->maps).size();
				} else {
					std::vector<args_type_t> argType = GetArgType({op[2]});
					switch (argType[0]) {
						case T_REGISTER : 
						case T_REGISTER_ADDRESS : 
						case T_ADDRESS : 
						case T_CONSTANT : currentSize += 1; break;
					}
				}
			}
			else {
				std::vector<args_type_t> argType = GetArgType({op[2], op[3]});
				
				switch (argType[0]) {
					case T_REGISTER : 
					case T_REGISTER_ADDRESS : 
					case T_ADDRESS : 
					case T_CONSTANT : currentSize += 1; break;
				}
				switch (argType[1]) {
					case T_REGISTER : 
					case T_REGISTER_ADDRESS : 
					case T_ADDRESS : 
					case T_CONSTANT : currentSize += 1; break;
				}
			}
		}
		else {
			currentSize = 0;
		} 
		this->maps.sizeMap.push_back({op[opMapCol::mnemonic], currentSize});
	}
}

void Parser::buildLabelMap() {
	int curentAddr = 0;
	for (auto item : this->maps.sizeMap) {
		if (item.size == 0) {
			this->maps.labelMap[item.opcode.substr(0, item.opcode.size()-1)] = curentAddr;
		}
		else {
			curentAddr += item.size;
		}
	}
}

std::vector<args_type_t> Parser::GetArgType(std::vector<std::string> _args) {
	std::vector<args_type_t> args_type;

	for (auto arg : _args) {
		remove_if(arg.begin(), arg.end(), isspace);
		if (register_tab.find(arg) != register_tab.end()) {
			args_type.push_back(T_REGISTER);
		}
		else if (!arg.compare(0, 1, "[") && !arg.compare(arg.size()-1, 1, "]") ) {
			if (!arg.compare(0, 2, "[A") || !arg.compare(0, 2, "[B") || !arg.compare(0, 2, "[C") || !arg.compare(0, 2, "[D"))
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

int Parser::getValue(std::string _str, maps_t _map) {
	if ( _map.labelMap.find(_str) != _map.labelMap.end() ) {
		return _map.labelMap[_str];
	} else { // not in label map
		if ( register_tab.find(_str) != register_tab.end() ) {
			return register_tab[_str];
		} else { // not a register
			if (!_str.compare(0, 1, "[") && !_str.compare(_str.size()-1, 1, "]") ) {
				return -1;
			}
			else {
				return getNumber(_str);
			}
		}
	}
	return -1;
}

std::vector<Tryte> Parser::NOP(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab = {op_tab["NOP"].value};
	return memTab;
}
std::vector<Tryte> Parser::HLT(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab = {op_tab["HLT"].value};
	return memTab;
}

std::vector<Tryte> Parser::MOV(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;

	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if ((args_type[0] == T_ADDRESS || args_type[0] == T_REGISTER_ADDRESS) && (args_type[1] == T_ADDRESS || args_type[1] == T_REGISTER_ADDRESS)) {
		throw -1;
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["MOV"].value);
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["MOV"].value + 1);;
	if (args_type[0] == T_REGISTER && args_type[1] == T_ADDRESS) 			memTab.push_back(op_tab["MOV"].value + 2);
	if (args_type[0] == T_REGISTER && args_type[1] == T_CONSTANT) 			memTab.push_back(op_tab["MOV"].value + 3);
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_REGISTER) 	memTab.push_back(op_tab["MOV"].value + 4);
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_CONSTANT) 	memTab.push_back(op_tab["MOV"].value + 5);
	if (args_type[0] == T_ADDRESS && args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["MOV"].value + 6);
	if (args_type[0] == T_ADDRESS && args_type[1] == T_CONSTANT) 			memTab.push_back(op_tab["MOV"].value + 7);
	
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	
	return memTab;
}

std::vector<Tryte> Parser::DB(std::vector<std::string> _opMap, maps_t maps) {
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

std::vector<Tryte> Parser::CMP(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["CMP"].value);

	return memTab;
}

std::vector<Tryte> Parser::JMP(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JMP"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JMP"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JC(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JNC(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JUC(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JZ(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JNZ(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JUZ(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::PUSH(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) 		memTab.push_back(op_tab["PUSH"].value);
	if (args_type[0] == T_REGISTER_ADDRESS) memTab.push_back(op_tab["PUSH"].value + 1);
	if (args_type[0] == T_ADDRESS) 			memTab.push_back(op_tab["PUSH"].value + 2);
	if (args_type[0] == T_CONSTANT) 		memTab.push_back(op_tab["PUSH"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::POP(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["POP"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::CALL(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["CALL"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::RET(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["RET"].value);
	return memTab;
}

std::vector<Tryte> Parser::INC(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["INC"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::DEC(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["DEC"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::ADD(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["ADD"].value);

	return memTab;
}
std::vector<Tryte> Parser::SUB(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["SUB"].value);

	return memTab;
}
std::vector<Tryte> Parser::MUL(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["MUL"].value);

	return memTab;
}
std::vector<Tryte> Parser::DIV(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["DIV"].value);

	return memTab;
}

std::vector<Tryte> Parser::AND(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["AND"].value);

	return memTab;
}
std::vector<Tryte> Parser::OR(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["OR"].value);

	return memTab;
}
std::vector<Tryte> Parser::XOR(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["XOR"].value);

	return memTab;
}

std::vector<Tryte> Parser::NOT(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOT"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::NOTT(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOTT"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}
std::vector<Tryte> Parser::NOTF(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOTF"].value);
	memTab.push_back(getValue(_opMap[2], maps));

	return memTab;
}

std::vector<Tryte> Parser::SHL(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["SHL"].value);

	return memTab;
}
std::vector<Tryte> Parser::SHR(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["SHR"].value);

	return memTab;
}