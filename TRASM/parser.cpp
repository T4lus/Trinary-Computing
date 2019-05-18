#include <functional>
#include <regex>

#include <Trinary/tryte.h>
#include <Utils/utils.h>
#include <Utils/string.h>

#include "parser.h"



Parser::Parser(std::string _inFile, std::string _outFile) {
	this->inFile = _inFile;
	this->outFile = _outFile;
}

int Parser::parse() {
	this->nbError = 0;
	int lineNumber = 0;
	std::cout << "Starting ..." << std::endl;

	std::string line;
	std::regex op_reg(OP_REGEX);
	std::smatch m;

	//load File
	std::ifstream infile(this->inFile.c_str());
	while (std::getline(infile, line)) {
		lineNumber++;
		line = line.substr(0, line.find("#"));
		chomp(line);

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

	
	this->buildSizeMap();		// create size map
	this->buildLabelMap();		// create label map
	this->buildCode();			// create code

	//this->debug();

	std::cout << "Done, " << this->nbError << " error(s) detected" << std::endl;		
	if (this->nbError)
		return 1;
	return 0;
}

int Parser::saveTrin() {
	std::ofstream outfile(this->outFile.c_str());
	int lineOffset = 0;
	for (auto item : this->code) {
		outfile << item;
		lineOffset++;
		if (!(lineOffset % 13))
			outfile << std::endl;
		else
			outfile << " ";
	}
}

void Parser::buildSizeMap() {
	std::cout << "Building size map ... ";
	for (auto op : this->maps.opMap) {
		int currentSize = 1;
		
		if (op_tab.find(op[opMapCol::mnemonic]) != op_tab.end()) {
			if (op_tab[op[opMapCol::mnemonic]].nb_args < 1) {
				currentSize = 1;
			}
			else if (op_tab[op[opMapCol::mnemonic]].nb_args < 2) {
				if ( !op_tab[op[opMapCol::mnemonic]].opcode.compare("DATA") ) {
					currentSize = this->DATA(op, this->maps).size();
				} 
				else {
					std::vector<args_type_t> argType = GetArgType({op[2]});
					switch (argType[0]) {
						case T_REGISTER : 
						case T_REGISTER_ADDRESS : 
						case T_ADDRESS : 
						case T_NUMBER : currentSize += 1; break;
					}
				}
			}
			else {
				std::vector<args_type_t> argType = GetArgType({op[2], op[3]});
				switch (argType[0]) {
					case T_REGISTER : 
					case T_REGISTER_ADDRESS : 
					case T_ADDRESS : 
					case T_NUMBER : currentSize += 1; break;
				}
				switch (argType[1]) {
					case T_REGISTER : 
					case T_REGISTER_ADDRESS : 
					case T_ADDRESS : 
					case T_NUMBER : currentSize += 1; break;
				}
			}
		}
		else {
			currentSize = 0;
		} 
		this->maps.sizeMap.push_back({op[opMapCol::mnemonic], currentSize});
	}
	std::cout << "done !" << std::endl;
}

void Parser::buildLabelMap() {
	std::cout << "Building label map ... ";
	int curentAddr = 0;
	for (auto item : this->maps.sizeMap) {
		if (item.size == 0) {
			this->maps.labelMap[item.opcode.substr(0, item.opcode.size()-1)] = curentAddr;
		}
		else {
			curentAddr += item.size;
		}
	}
	std::cout << "done !" << std::endl;
}

void Parser::buildCode() {
	std::cout << "Building code ... ";
	for (auto op : this->maps.opMap) {
		if (op_tab.find(op[opMapCol::mnemonic]) != op_tab.end()) {
			try {
				std::vector<Tryte> opmem = op_tab[op[opMapCol::mnemonic]].fct(op, this->maps);
				for (auto mem : opmem) {
					this->code.push_back(str_pad(dechept(mem.to_int()), 3, 'D', STR_PAD_LEFT) );
				}
			}
			catch(std::string const& e) {
				std::cout << e << std::endl;;
				this->nbError++;
			}
		}
	}
	std::cout << "done !" << std::endl;
}

void Parser::debug() {
	std::cout << std::endl << " === DEBUG START === " << std::endl;
	std::cout << " -- label -- " << std::endl;
	for (auto& item : this->maps.labelMap) {
		std::cout << item.first << "\t : " << str_pad(dechept(Tryte(item.second).to_int()), 3, 'D', STR_PAD_LEFT) << std::endl;
	}
	std::cout << std::endl;
	std::cout << " -- memory -- " << std::endl;
	for (auto op : this->maps.opMap) {
		if (op_tab.find(op[opMapCol::mnemonic]) != op_tab.end()) {
			std::cout << op_tab[op[opMapCol::mnemonic]].opcode << "\t : ";
			try {
				std::vector<Tryte> opmem = op_tab[op[opMapCol::mnemonic]].fct(op, this->maps);
				for (auto mem : opmem) {
					std::cout << str_pad(dechept(mem.to_int()), 3, 'D', STR_PAD_LEFT) <<  " ";
				}
			}
			catch(std::string const& e) {
				std::cout << e;
				this->nbError++;
			}
			
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << " -- code -- " << std::endl;
	int lineOffset = 0;
	for (auto item : this->code) {
		std::cout << item;
		lineOffset++;
		if (!(lineOffset % 13))
			std::cout << std::endl;
		else
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << " === DEBUG END === " << std::endl << std::endl;
}

void Parser::checkNbArg(std::vector<std::string> _opMap) {
	if (op_tab[_opMap[opMapCol::mnemonic]].nb_args + 2 != _opMap.size()) {
		throw std::string("Line " + _opMap[opMapCol::lineNumber] + " - " + _opMap[opMapCol::mnemonic] + ": too many arguments ("+std::to_string(_opMap.size() - 2)+")");
	}
}

std::vector<args_type_t> Parser::GetArgType(std::vector<std::string> _args) {
	std::vector<args_type_t> args_type;

	for (auto arg : _args) {
		remove_if(arg.begin(), arg.end(), isspace);
		if (register_tab.find(arg) != register_tab.end()) {
			args_type.push_back(T_REGISTER);
		}
		else if (!arg.compare(0, 1, "@")) {
			if (register_tab.find(arg.substr(1, 3)) != register_tab.end())
				args_type.push_back(T_REGISTER_ADDRESS);
			else
				args_type.push_back(T_ADDRESS);
		} 
		else if (isInteger(arg) || isHex(arg) || isHept(arg)) {
			args_type.push_back(T_NUMBER);
		}
		else {
			args_type.push_back(T_NUMBER);
		}
	}
	return args_type;
}

int Parser::parseAddress(std::string value) {
	if (register_tab.find(value) != register_tab.end()) { // Register
		return register_tab[value];
	}
	else if (register_tab.find(value.substr(0, 2)) != register_tab.end()) { //Offset Adressing
		int m = 0;
		int base = register_tab[value.substr(0, 2)];

		if(!value.compare(2, 1, "-"))
			m = -1;
		else if(!value.compare(2, 1, "+"))
			m = 1;
		else
			throw std::string("bad offset operation");

		int offset = m * getNumber(value.substr(3, value.size()-1));

		if (offset < (-1*TRYTE_MAX - 27) || offset > (TRYTE_MAX - 27))
		 	throw std::string("offset must be a value between -TRYTE_MAX and TRYTE_MAX");
		
		return offset * 27 + base; //sift offset 3 trit and add code for register
	}
	else 
		return getNumber(value);
}

int Parser::getValue(std::string _str, maps_t _map) {
	if ( _map.labelMap.find(_str) != _map.labelMap.end() ) { // Label
		return _map.labelMap[_str];
	} 
	else if (register_tab.find(_str) != register_tab.end()) { // Register
		return register_tab[_str];
	} 
	else if (isInteger(_str) || isHex(_str) || isHept(_str) ) { // Number
		return getNumber(_str);
	}
	else if (!_str.compare(0, 1, "@")) { // Address
		return parseAddress(_str.substr(1, _str.size()-1));
	}
	else if (!_str.compare(0, 1, "'") && !_str.compare(_str.size()-1, 1, "'")) { // Char 
		if (_str.size() > 3)
			throw std::string("Only one character is allowed.");
		return (int)_str[1];
	}
	else {
		return -1;
	}
	return -1;
}

std::vector<Tryte> Parser::NOOP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab = {op_tab["NOOP"].value};
	return memTab;
}
std::vector<Tryte> Parser::HALT(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab = {op_tab["HALT"].value};
	return memTab;
}
std::vector<Tryte> Parser::LOAD(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if ((args_type[0] == T_ADDRESS || args_type[0] == T_REGISTER_ADDRESS) && (args_type[1] == T_ADDRESS || args_type[1] == T_REGISTER_ADDRESS)) {
		throw -1;
	}
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["LOAD"].value);
	if (args_type[0] == T_REGISTER && args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["LOAD"].value + 1);
	if (args_type[0] == T_REGISTER && args_type[1] == T_ADDRESS) 			memTab.push_back(op_tab["LOAD"].value + 2);
	if (args_type[0] == T_REGISTER && args_type[1] == T_NUMBER) 			memTab.push_back(op_tab["LOAD"].value + 3);
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_REGISTER) 	memTab.push_back(op_tab["LOAD"].value + 4);
	if (args_type[0] == T_REGISTER_ADDRESS && args_type[1] == T_NUMBER) 	memTab.push_back(op_tab["LOAD"].value + 5);
	if (args_type[0] == T_ADDRESS && args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["LOAD"].value + 6);
	if (args_type[0] == T_ADDRESS && args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["LOAD"].value + 7);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::DATA(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;

	if (isInteger(_opMap[2]) || isHex(_opMap[2])) {
		memTab.push_back(Tryte(getNumber(_opMap[2])));
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
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["CMP"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["CMP"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["CMP"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["CMP"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::JMP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JMP"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JMP"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JNC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JUC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JNZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::JUZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::PUSH(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) 		memTab.push_back(op_tab["PUSH"].value);
	if (args_type[0] == T_REGISTER_ADDRESS) memTab.push_back(op_tab["PUSH"].value + 1);
	if (args_type[0] == T_ADDRESS) 			memTab.push_back(op_tab["PUSH"].value + 2);
	if (args_type[0] == T_NUMBER) 			memTab.push_back(op_tab["PUSH"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::POP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["POP"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::CALL(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["CALL"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["CALL"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::RET(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["RET"].value);
	return memTab;
}
std::vector<Tryte> Parser::INC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["INC"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::DEC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["DEC"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::ADD(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["ADD"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["ADD"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["ADD"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["ADD"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::SUB(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["SUB"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["SUB"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["SUB"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["SUB"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::MUL(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["MUL"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["MUL"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["MUL"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["MUL"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::DIV(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["DIV"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["DIV"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["DIV"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["DIV"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::AND(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["AND"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["AND"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["AND"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["AND"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::OR(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["OR"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["OR"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["OR"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["OR"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::XOR(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["XOR"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["XOR"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["XOR"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["XOR"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::NOT(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOT"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::NOTT(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOTT"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::NOTF(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab.push_back(op_tab["NOTF"].value);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}
std::vector<Tryte> Parser::SHL(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["SHL"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["SHL"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["SHL"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["SHL"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}
std::vector<Tryte> Parser::SHR(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = GetArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["SHR"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["SHR"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["SHR"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["SHR"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}