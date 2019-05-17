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
	std::cout << "Tryte ++ test : " << std::endl;
	
	t_test = 1093;
	std::cout << t_test.str() << " : " << t_test.to_int() << " : " << dechept(t_test.to_int()) << std::endl;

	Tryte tr_test = heptdec("000");
	for (int i = 0; i < 30; i++, tr_test++)
		std::cout << tr_test.str() << " : " << tr_test.to_int() << " : " << dechept(tr_test.to_int()) << std::endl;
	
	t_test = -1093;
	std::cout << t_test.str() << " : " << t_test.to_int() << " : " << dechept(t_test.to_int()) << std::endl;

	// std::cout << std::endl;
	// std::cout << "Utils test : " << std::endl;
	// std::cout << "heptDec(000) - -9841: " << heptdec("000") << std::endl;
	// std::cout << "heptDec(DCX) - -15: " << heptdec("DCX") << std::endl;
	// std::cout << "heptDec(DCZ) - -14: " << heptdec("DCZ") << std::endl;
	// std::cout << "heptDec(DD0) - -13: " << heptdec("DD0") << std::endl; 
	// std::cout << "heptDec(DDC) - -1: " << heptdec("DDC") << std::endl; 
	// std::cout << "heptDec(DDD) - 0: " << heptdec("DDD") << std::endl;
	// std::cout << "heptDec(DDE) - 1: " << heptdec("DDE") << std::endl;
	// std::cout << "heptDec(DDZ) - 13: " << heptdec("DDZ") << std::endl;
	// std::cout << "heptDec(DE0) - 14: " << heptdec("DE0") << std::endl;
	// std::cout << "heptDec(DE1) - 15: " << heptdec("DE1") << std::endl;
	// std::cout << "heptDec(ZZZ) - 9841: " << heptdec("ZZZ") << std::endl;

	// std::cout << std::endl;
	// std::cout << "dechept(-9841) - 000: " << dechept(-9841) << std::endl;
	// std::cout << "dechept(-15) - CX: " << dechept(-15) << std::endl;
	// std::cout << "dechept(-14) - CZ: " << dechept(-14) << std::endl;
	// std::cout << "dechept(-13) - 0: " << dechept(-13) << std::endl; 
	// std::cout << "dechept(-1) - C: " << dechept(-1) << std::endl; 
	// std::cout << "dechept(0) - D: " << dechept(0) << std::endl;
	// std::cout << "dechept(1) - E: " << dechept(1) << std::endl;
	// std::cout << "dechept(13) - Z: " << dechept(13) << std::endl;
	// std::cout << "dechept(14) - E0: " << dechept(14) << std::endl;
	// std::cout << "dechept(15) - E1: " << dechept(15) << std::endl;
	// std::cout << "dechept(9841) - ZZZ: " << dechept(9841) << std::endl;

	return 0;
}