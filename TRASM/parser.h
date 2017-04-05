/*
**
** Made by T4lus
** Trinary ASM OPCODE
** 
*/

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

#include "trinary.h"
#include "opcodes.h"

std::string trim(const std::string& str, const std::string& whitespace = " \t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t") {
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

enum opMapCol {
    lineNumber,
    mnemonic,
    arg1,
    arg2,
    arg3,
    arg4
};

typedef std::vector<std::vector<std::string>> map_t;

class Parser {
private:
	std::string 				inFile;
	std::string 				outFile;

	int							nbError = 0;
	std::vector<std::string> 	errors;
	
	map_t						opMap;
	map_t						byteMap;

public:
	Parser(std::string _inFile, std::string _outFile) {
		this->inFile = _inFile;
		this->outFile = _outFile;
	}
	
	int parse1() {
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

	int parse2() {
		this->nbError = 0;
		std::cout << "Starting parse 2 ..." << std::endl;

		std::cout << "Parse 2 done, " << this->nbError << " error(s) detected" << std::endl;		
		if (this->nbError)
			return 1;
		return 0;
	}

	int compile() {

		return 0;
	}
	
};


#endif