#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "../parser.h"

std::vector<Tryte> Parser::AND(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["SHR"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["SHR"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["SHR"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["SHR"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}