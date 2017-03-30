/*
**
** Made by T4lus
** Trinary Emulator
** 
*/

#include <iostream>
#include <string>

#include <trinary.h>

std::string execPath;

int main(int argc, char* argv[])
{
	std::cout << "=== TREMU v0.1.0 ===" << std::endl;

	char basePath[255] = "";
	realpath(argv[0], basePath);
	execPath = basePath;
	execPath = execPath.substr(0, execPath.find_last_of("\\/"));

	return 0;
}