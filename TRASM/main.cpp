/*
**
** Made by T4lus
** Trinary Assembler
** 
*/

#include <iostream>
#include <string>

#include <trinary.h>

#include "opcodes.h"
#include "parser.h"

std::string execPath;

main(int argc, char* argv[])
{   
	std::cout << "=== TRASM v0.1.0 ===" << std::endl;

    char basePath[255] = "";
    realpath(argv[0], basePath);
    execPath = basePath;
    execPath = execPath.substr(0, execPath.find_last_of("\\/"));

    int ret = 0;

    Parser *parser = new Parser(argv[1], argv[2]);

    ret = parser->parse1();
    if (ret) {
        std::cout << "ASM abort !!!" << std::endl;
        return -1;
    }

    ret = parser->parse2();
    if (ret) {
        std::cout << "ASM abort !!!" << std::endl;
        return -1;
    }

    parser->compile();

}