/*
**
** Made by T4lus
** Trinary Funtions Test
** 
*/

#include <iostream>
#include <string>

#include <trinary.h>

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
	
	Tryte t_test = "FFFFFFFFF";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = "UUUUUUUUU";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = "TTTTTTTTT";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;
	t_test = "TUUUUUUUT";
	std::cout << t_test.str() << " : " << t_test.to_int() << std::endl;

	std::cout << std::endl;
	std::cout << " INC \t\t\t DEC" << std::endl;
	Tryte t_test1 = 0;
	Tryte t_test2 = 0;
	std::cout << t_test1.str() << " : " << t_test1.to_int() << "\t\t" << t_test2.str() << " : " << t_test2.to_int() << std::endl;
	for (int i = 0; i < 10; i++) {
		t_test1++;
		t_test2--;
		std::cout << t_test1.str() << " : " << t_test1.to_int() << "\t\t" << t_test2.str() << " : " << t_test2.to_int() << std::endl;
	}

	std::cout << std::endl;
	std::cout << " SHL \t\t\t SHR" << std::endl;
	Tryte t_test3 = "UUUUUUUUT";
	Tryte t_test4 = "TUUUUUUUU";
	std::cout << t_test3.str() << " : " << t_test3.to_int() << "\t\t" << t_test4.str() << " : " << t_test4.to_int() << std::endl;
	for (int i = 0; i < 10; i++) {
		Tryte::SHL(t_test3, 1);
		Tryte::SHR(t_test4, 1);
		std::cout << t_test3.str() << " : " << t_test3.to_int() << "\t\t" << t_test4.str() << " : " << t_test4.to_int() << std::endl;
	}

	return 0;
}