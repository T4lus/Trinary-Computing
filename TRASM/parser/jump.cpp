#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "../parser.h"

std::vector<Tryte> Parser::JMP(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JMP"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JMP"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JNC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JUC(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUC"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUC"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JNZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JNZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JNZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}

std::vector<Tryte> Parser::JUZ(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
	if (args_type[0] == T_REGISTER) memTab.push_back(op_tab["JUZ"].value);
	if (args_type[0] != T_REGISTER) memTab.push_back(op_tab["JUZ"].value + 1);
	memTab.push_back(getValue(_opMap[2], maps));
	return memTab;
}