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

	t_test = "UUTFFF";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;

	t_test = 13;
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = 14;
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = 15;
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = 16;
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = -16;
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;

	std::cout << std::endl;
	std::cout << "Tryble test : " << std::endl;
	
	Tryble tr_test = "FFF";
	for (int i = 0; i < 27; i++, tr_test++)
		std::cout << tr_test.str() << " : " << tr_test.to_int() << std::endl;


	std::cout << std::endl;
	std::cout << "Utils test : " << std::endl;
	std::cout << "heptDec(000) - -9841: " << heptDec("000") << std::endl;
	std::cout << "heptDec(DCX) - -15: " << heptDec("CX") << std::endl;
	std::cout << "heptDec(DCZ) - -14: " << heptDec("CZ") << std::endl;
	std::cout << "heptDec(DD0) - -13: " << heptDec("0") << std::endl; 
	std::cout << "heptDec(DDC) - -1: " << heptDec("C") << std::endl; 
	std::cout << "heptDec(DDD) - 0: " << heptDec("D") << std::endl;
	std::cout << "heptDec(DDE) - 1: " << heptDec("E") << std::endl;
	std::cout << "heptDec(DDZ) - 13: " << heptDec("Z") << std::endl;
	std::cout << "heptDec(DE0) - 14: " << heptDec("E0") << std::endl;
	std::cout << "heptDec(DE1) - 15: " << heptDec("E1") << std::endl;
	std::cout << "heptDec(ZZZ) - 9841: " << heptDec("ZZZ") << std::endl;

	std::cout << std::endl;
	std::cout << "heptEnc(-9841) - 000: " << heptEnc(-9841) << std::endl;
	std::cout << "heptEnc(-15) - CX: " << heptEnc(-15) << std::endl;
	std::cout << "heptEnc(-14) - CZ: " << heptEnc(-14) << std::endl;
	std::cout << "heptEnc(-13) - 0: " << heptEnc(-13) << std::endl; 
	std::cout << "heptEnc(-1) - C: " << heptEnc(-1) << std::endl; 
	std::cout << "heptEnc(0) - D: " << heptEnc(0) << std::endl;
	std::cout << "heptEnc(1) - E: " << heptEnc(1) << std::endl;
	std::cout << "heptEnc(13) - Z: " << heptEnc(13) << std::endl;
	std::cout << "heptEnc(14) - E0: " << heptEnc(14) << std::endl;
	std::cout << "heptEnc(15) - E1: " << heptEnc(15) << std::endl;
	std::cout << "heptEnc(9841) - ZZZ: " << heptEnc(9841) << std::endl;

	return 0;
}