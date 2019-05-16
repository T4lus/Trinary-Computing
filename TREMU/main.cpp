/*
**
** Made by T4lus
** Trinary Emulator
** 
*/

#include <fstream>
#include <iostream>
#include <sstream>

#include <Trinary/trinary.h>

#include "memory.h"

std::string execPath;

int main(int argc, char* argv[])
{
	std::cout << "=== TREMU v0.1.0 ===" << std::endl;

	char basePath[255] = "";
	realpath(argv[0], basePath);
	execPath = basePath;
	execPath = execPath.substr(0, execPath.find_last_of("\\/"));

	Memory *mem = new Memory(19683);

	//load 3asm into memory
	std::ifstream infile(argv[1]);

	std::string line;
	int addr = 0;
	while (!std::getline(infile, line).eof()) {
		addr++;
		mem->store(Tryte(addr) , Tryte(line.c_str()));
	}

	return 0;
}