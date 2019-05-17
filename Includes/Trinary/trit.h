/*
**
** Made by T4lus
** Trinary Trit Implementation
** TUF syntax
** 
*/

#ifndef TRIT_H
#define TRIT_H

#include <assert.h>

class Trit {
public:
	Trit() {
		m_ch = 'U';
	}

	Trit(char ch) {
		switch (ch) {
			case 'U':
			case 'T':
			case 'F':
				this->m_ch = ch;
				break;
			default:
				assert(false);
		}
	}

	explicit operator char() {
		return this->m_ch;
	}

	char to_char() {
		return this->m_ch;
	}

	explicit operator bool() {
		return this->m_ch == 'T';
	}

	//------------------------------------------
	// Negation

	Trit operator~() {
		if (this->m_ch == 'T')
			return 'F';
		if (this->m_ch == 'F')
			return 'T';
		return *this;
	}

	static Trit NOT(Trit t1) {
		if (t1.m_ch == 'T')
			return 'F';
		if (t1.m_ch == 'F')
			return 'T';
		return t1;
	}

	static Trit NOTT(Trit t1) {
		if (t1.m_ch == 'T')
			return 'F';
		if (t1.m_ch == 'F' || t1.m_ch == 'U')
			return 'T';
	}

	static Trit NOTF(Trit t1) {
		if (t1.m_ch == 'T' || t1.m_ch == 'U')
			return 'F';
		if (t1.m_ch == 'F')
			return 'T';
	}

	//------------------------------------------
	// Decoder

	bool operator==(Trit other) {
		return (this->m_ch == other.m_ch);
	}

	bool operator!=(Trit other) {
		return (this->m_ch != other.m_ch);
	}

	/*
	** is false
	*/
	static Trit ISF(Trit t1) {
		if (t1.m_ch == 'F')
			return 'T';
		return 'F';
	}

	/*
	** is unknow
	*/
	static Trit ISU(Trit t1) {
		if (t1.m_ch == 'U')
			return 'T';
		return 'F';
	}

	/*
	** is true
	*/
	static Trit IST(Trit t1) {
		if (t1.m_ch == 'T')
			return 'T';
		return 'F';
	}

	/*
	** Switch true
	*/
	static Trit SWT(Trit t1) {
		if (t1.m_ch == 'T')
			return 'F';
		return 'U';
	}

	//------------------------------------------
	// Logical

	Trit operator&(Trit other) {
		if (this->m_ch == 'T' && other.m_ch == 'T')
			return 'T';
		if ((this->m_ch == 'U' && other.m_ch == 'U') || (this->m_ch == 'T' && other.m_ch == 'U') || (this->m_ch == 'U' && other.m_ch == 'T'))
			return 'U';
		return 'F';
	}
	Trit operator|(Trit other) {
		if (this->m_ch == 'T' || other.m_ch == 'T')
			return 'T';
		if ((this->m_ch == 'U' || other.m_ch == 'U'))
			return 'U';
		return 'F';
	}
	Trit operator^(Trit other) {
		return (*this | other) & ~(*this & other);
	}

	static Trit AND(Trit t1, Trit t2) {
		return t1 & t2;
	}

	static Trit OR(Trit t1, Trit t2) {
		return t1 | t2;
	}

	static Trit NAND(Trit t1, Trit t2) {
		return ~(t1 & t2);
	}

	static Trit NOR(Trit t1, Trit t2) {
		return ~(t1 | t2);
	}

	static Trit MOD3_SUM(Trit t1, Trit t2) {
		return ( ISF(t1) & DEC(t2) )   |   ( ISU(t1) & t2 )   |   ( IST(t1) & INC(t2) );
	}
	#define SUM MOD3_SUM

	static Trit CONS(Trit t1, Trit t2) {
		return ( t1 & t2 )   |   ( ~ISF(t1) & 'U' )   |   ( ~ISF(t2) & 'U' );
	}

	static Trit ANY(Trit t1, Trit t2) {
		if ((t1.m_ch == 'T' || t1.m_ch == 'U') && (t2.m_ch == 'T' || t2.m_ch == 'U') && !(t1.m_ch == 'U' && t2.m_ch == 'U'))
			return 'T';
		if ((t1.m_ch == 'F' || t1.m_ch == 'U') && (t2.m_ch == 'F' || t2.m_ch == 'U') && !(t1.m_ch == 'U' && t2.m_ch == 'U'))
			return 'F';
		return 'U';
	}

	static Trit EQ(Trit t1, Trit t2) {
		if (t1.m_ch == t2.m_ch)
			return 'T';
		return 'F';
	}
	
	//------------------------------------------
	// Increment and Decrement

	Trit operator++(int) {
		if (this->m_ch == 'F')
			this->m_ch = 'U';
		else if (this->m_ch == 'U')
			this->m_ch = 'T';
		else if (this->m_ch == 'T')
			this->m_ch = 'F';
		else
			assert(false);
		return *this;
	}

	Trit operator--(int) {
		if (this->m_ch == 'F')
			this->m_ch = 'T';
		else if (this->m_ch == 'U')
			this->m_ch = 'F';
		else if (this->m_ch == 'T')
			this->m_ch = 'U';
		else
			assert(false);
		return *this;
	}

	static Trit INC(Trit &t1) {
		switch (t1.m_ch) {
			case 'F':
				t1 = 'U';
			case 'U':
				t1 = 'T';
			case 'T':
				t1 = 'F';
		}
		return t1;
	}

	static Trit DEC(Trit &t1) {
		switch (t1.m_ch) {
			case 'F':
				t1 = 'T';
			case 'U':
				t1 = 'F';
			case 'T':
				t1 = 'U';
		}
		return t1;
	}

private:
	char m_ch;
};

#endif