#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "../parser.h"

std::vector<Tryte> Parser::PUSH(std::vector<std::string> _opMap, maps_t maps) {
	checkNbArg(_opMap);
	std::vector<Tryte> memTab;
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
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
	std::vector<args_type_t> args_type = getArgType({_opMap[2]});
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