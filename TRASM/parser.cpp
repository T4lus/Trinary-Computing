#include <functional>
#include <regex>

#include <Trinary/tryte.h>
#include <Utils/utils.h>

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

	this->debug();

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
				if ( !op_tab[op[opMapCol::mnemonic]].opcode.compare("DT") ) {
					currentSize = this->DT(op, this->maps).size();
				} 
				else if ( !op_tab[op[opMapCol::mnemonic]].opcode.compare("DW") ) {
					currentSize = this->DT(op, this->maps).size() * 3;
				} 
				else if ( !op_tab[op[opMapCol::mnemonic]].opcode.compare("DTW") ) {
					currentSize = this->DT(op, this->maps).size() * 9;
				}
				else {
					std::vector<args_type_t> argType = getArgType({op[2]});
					if (argType[0] & T_REGISTER) 
						currentSize += 1;
					else if (argType[0] & T_NUMBER || argType[0] & T_LABEL)
						currentSize += 3;

					if (argType[0] & T_OFFSET) currentSize += 3;
				}
			}
			else {
				std::vector<args_type_t> argType = getArgType({op[2], op[3]});
				if ((argType[0] & T_REGISTER && argType[1] & T_REGISTER) || ((argType[0] & T_REGISTER && argType[0] & T_ADDRESS) && (argType[1] & T_REGISTER && argType[1] & T_ADDRESS))) {
					currentSize += 1;
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
					//std::cout << str_pad(dechept(mem.to_int()), 3, 'D', STR_PAD_LEFT) <<  " ";
					std::cout << mem.str() <<  " ";
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

std::vector<args_type_t> Parser::getArgType(std::vector<std::string> _args) {
	std::vector<args_type_t> args_type;

	for (auto arg : _args) {
		remove_if(arg.begin(), arg.end(), isspace);

		int type = 0;
		//main type
		if (isRegister(arg)) 
			type = type | T_REGISTER;
		else if (isNumber(arg)) 
			type = type | T_NUMBER;
		else
			type = type | T_LABEL;

		//attribute
		if (!arg.compare(0, 1, "@")) 
			type = type | T_ADDRESS;
		if (arg.find("+") != std::string::npos || arg.find("-") != std::string::npos) 
			type = type | T_OFFSET;

		args_type.push_back(type);
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

std::vector<Tryte> Parser::getValues(std::vector<std::string> operands, std::vector<args_type_t> operands_type, maps_t _map) {
	std::vector<Tryte> memTab;

	if (operands_type[0] & T_REGISTER) {
		Tryte tmp = parseRegister(operands[0], Tryte(0));
		if (operands_type[1] & T_REGISTER)
			tmp = parseRegister(operands[1], tmp);
		
		memTab.push_back(tmp);
	}

	return memTab;
}

std::vector<Tryte> Parser::NOP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab = {op_tab["NOP"].value};
	return memTab;
}
std::vector<Tryte> Parser::HLT(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	memTab = {op_tab["HLT"].value};
	return memTab;
}
std::vector<Tryte> Parser::MOV(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
	if ((args_type[0] & T_ADDRESS || args_type[0] & T_REGISTER & T_ADDRESS) && (args_type[1] & T_ADDRESS || args_type[1] & T_REGISTER & T_ADDRESS)) {
		throw -1;
	}
	if (args_type[0] & T_REGISTER && args_type[1] & T_REGISTER) 			memTab.push_back(op_tab["MOV"].value);
	if (args_type[0] & T_REGISTER && args_type[1] & T_REGISTER & T_ADDRESS) 	memTab.push_back(op_tab["MOV"].value + 1);
	if (args_type[0] & T_REGISTER && args_type[1] & T_ADDRESS) 			memTab.push_back(op_tab["MOV"].value + 2);
	if (args_type[0] & T_REGISTER && args_type[1] & T_NUMBER) 			memTab.push_back(op_tab["MOV"].value + 3);
	if (args_type[0] & T_REGISTER & T_ADDRESS && args_type[1] & T_REGISTER) 	memTab.push_back(op_tab["MOV"].value + 4);
	if (args_type[0] & T_REGISTER & T_ADDRESS && args_type[1] & T_NUMBER) 	memTab.push_back(op_tab["MOV"].value + 5);
	if (args_type[0] & T_ADDRESS && args_type[1] & T_REGISTER) 			memTab.push_back(op_tab["MOV"].value + 6);
	if (args_type[0] & T_ADDRESS && args_type[1] & T_NUMBER) 				memTab.push_back(op_tab["MOV"].value + 7);
	
	std::vector<Tryte> values = getValues({_opMap[2], _opMap[3]}, args_type, maps);

	memTab.insert(memTab.end(), values.begin(), values.end());

	//memTab.push_back(getValue(_opMap[2], maps));
	//memTab.push_back(getValue(_opMap[3], maps));
	
	return memTab;
}

std::vector<Tryte> Parser::DT(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;

	if (isInteger(_opMap[2]) || isHex(_opMap[2]) || isHept(_opMap[2])) {
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

std::vector<Tryte> Parser::DW(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;

	return memTab;
}

std::vector<Tryte> Parser::DTW(std::vector<std::string> _opMap, maps_t maps) {
	std::vector<Tryte> memTab;

	return memTab;
}

std::vector<Tryte> Parser::CMP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
	if (args_type[1] & T_REGISTER) 			memTab.push_back(op_tab["CMP"].value);
	if (args_type[1] & T_REGISTER & T_ADDRESS) 	memTab.push_back(op_tab["CMP"].value + 1);
	if (args_type[1] & T_ADDRESS) 				memTab.push_back(op_tab["CMP"].value + 2);
	if (args_type[1] & T_NUMBER) 				memTab.push_back(op_tab["CMP"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}