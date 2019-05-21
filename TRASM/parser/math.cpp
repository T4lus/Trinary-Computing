#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "../parser.h"

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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2], _opMap[3]});
	if (args_type[1] == T_REGISTER) 			memTab.push_back(op_tab["DIV"].value);
	if (args_type[1] == T_REGISTER_ADDRESS) 	memTab.push_back(op_tab["DIV"].value + 1);
	if (args_type[1] == T_ADDRESS) 				memTab.push_back(op_tab["DIV"].value + 2);
	if (args_type[1] == T_NUMBER) 				memTab.push_back(op_tab["DIV"].value + 3);
	memTab.push_back(getValue(_opMap[2], maps));
	memTab.push_back(getValue(_opMap[3], maps));
	return memTab;
}