/*
**
** Made by T4lus
** Trinary Funtions Test
** 
*/

#include <iostream>
#include <string>

#include <Trinary/trinary.h>
#include <Utils/utils.h>

std::string execPath;

int main(int argc, char* argv[])
{
	std::cout << "=== TRTST v0.1.0 ===" << std::endl;

	char basePath[255] = "";
	realpath(argv[0], basePath);
	execPath = basePath;
	execPath = execPath.substr(0, execPath.find_last_of("\\/"));

	std::cout << std::endl;
	std::cout << "Trit test : " << std::endl;
	std::cout << "+---++-----+------+------+-----+-----+-----+" << std::endl;
	std::cout << "|   ||     |  PTI |  NTI |     |     |     |" << std::endl;
	std::cout << "| A || NOT | NOTT | NOTF | INC | DEC | SWT |" << std::endl;
	std::cout << "|   ||  ~  | NOTT | NOTF | INC | DEC | SWT |" << std::endl;
	std::cout << "+---++-----+------+------+-----+-----+-----+" << std::endl;

	Trit Z = 'F';
	for (int i = 0; i < 3; i++) {
		std::cout << "| " << char(Z) << " ||  " 
		<< char(~Z) << "  |   " 
		<< char(Trit::NOTT(Z)) << "  |   "
		<< char(Trit::NOTF(Z)) << "  |  " 
		<< char(Trit::INC(Z)) << "  |  "
		<< char(Trit::DEC(Z)) << "  |  "
		<< char(Trit::SWT(Z)) << "  |  "

		<< std::endl;
		Z++;
	}
	std::cout << "+---++-----+------+------+-----+-----+-----+" << std::endl;

//-------------------------
	std::cout << std::endl;
	std::cout << "+---+---++-----+-----+------+-----+-----+-----+------+-----+----+" << std::endl;
	std::cout << "|   |   || MIN | MAX |      |     |     |     |      |     |    |" << std::endl;
	std::cout << "| B | A || AND |  OR | NAND | NOR | XOR | SUM | CONS | ANY | EQ |" << std::endl;
	std::cout << "|   |   ||  &  |  |  |      |     |  ^  |     |      |     |    |" << std::endl;
	std::cout << "+---+---++-----+-----+------+-----+-----+-----+------+-----+----+" << std::endl;

	Trit A = 'F';
	Trit B = 'F';
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "| " << char(B) << " | " << char(A) << " ||  " 
			<< char(B & A) << "  |  " 
			<< char(B | A) << "  |   "
			<< char(~(B & A)) << "  |  " 
			<< char(~(B | A)) << "  |  "
			<< char(B ^ A) << "  |  "

			<< char(Trit::SUM(B, A)) << "  |   "
			<< char(Trit::CONS(B, A)) << "  |  "
			<< char(Trit::ANY(B, A)) << "  |  "
			<< char(Trit::EQ(B, A)) << " |"
			<< std::endl;
			A++;
		}
		A = 'F';
		B++;
	}
	std::cout << "+---+---++-----+-----+------+-----+-----+-----+------+-----+----+" << std::endl;

	std::cout << std::endl;
	std::cout << "Tryte test : " << std::endl;
	
	Tryte t_test;
	t_test = "TTTTTTTTT";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = "UUUUUUUUU";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = "FFFFFFFFF";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;

	std::cout << std::endl;
	std::cout << "Tryble test : " << std::endl;
	
	Tryble tr_test = "FFF";
	std::cout << tr_test.str() << " : " << tr_test.to_int() << std::endl;
	tr_test = "UUU";
	std::cout << tr_test.str() << " : " << tr_test.to_int() << std::endl;
	tr_test = "TTT";
	std::cout << tr_test.str() << " : " << tr_test.to_int() << std::endl;

	std::cout << std::endl;
	std::cout << "Utils test : " << std::endl;
	std::cout << "uheptDec(1) - 1: " << uheptDec("1") << std::endl;
	std::cout << "uheptDec(15) - 32: " << uheptDec("15") << std::endl; 
	std::cout << "uheptDec(KZ) - 512: " << uheptDec("KZ") << std::endl;
	std::cout << "uheptDec(1AX) - 1024: " << uheptDec("1AX") << std::endl;
	std::cout << "uheptDec(DDD) - 9841: " << uheptDec("DDD") << std::endl;
	std::cout << "uheptDec(ZZZ) - 19682: " << uheptDec("ZZZ") << std::endl;
	std::cout << std::endl;
	std::cout << "heptDec(000) - -9841: " << heptDec("000") << std::endl;
	std::cout << "heptDec(CC) - -15: " << heptDec("CC") << std::endl; 
	std::cout << "heptDec(CD) - -14: " << heptDec("CD") << std::endl; 
	std::cout << "heptDec(0) - -13: " << heptDec("0") << std::endl; 
	std::cout << "heptDec(C) - -1: " << heptDec("C") << std::endl; 
	std::cout << "heptDec(D) - 0: " << heptDec("D") << std::endl;
	std::cout << "heptDec(E) - 1: " << heptDec("E") << std::endl;
	std::cout << "heptDec(Z) - 13: " << heptDec("Z") << std::endl;
	std::cout << "heptDec(ED) - 14: " << heptDec("ED") << std::endl;
	std::cout << "heptDec(EE) - 15: " << heptDec("EE") << std::endl;
	std::cout << "heptDec(ZZZ) - 9841: " << heptDec("ZZZ") << std::endl;

	return 0;
}