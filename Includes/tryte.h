/*
**
** Made by T4lus
** Trinary Tryte Implementation
** TUF syntax
** 1 Tryte -> 9 Trit
** 
*/

#ifndef TRYTE_H
#define TRYTE_H

#include <algorithm>
#include <string>

#include <assert.h>
#include <string.h>

#include "trinary.h"

class Tryte {
public:
	static const int CTRIT = 9;
	static const int Tryte_MAX = 19683;

	Tryte() {
	}

	Tryte(int int8) {
		int ival = int8;
		bool fneg = ival < 0;

		if (int8 >= Tryte_MAX)
			ival = 0;

		if (fneg)
			ival = -ival;

		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			switch (ival % 3) {
				case 0:
					rgdigit[idigit] = 'U';
					break;

				case 1:
					rgdigit[idigit] = 'T';
					break;

				case 2:
					rgdigit[idigit] = 'F';
					++ival;
					break;
			}
			ival /= 3;
		}
		assert(ival == 0);
		if (fneg)
			*this = ~(*this);
	}

	Tryte(const char *sz) {
		int cch = strlen(sz);
		assert(cch <= CTRIT);
		int itrit = 0;
		while (cch > 0) {
			--cch;
			rgdigit[itrit] = sz[cch];
			++itrit;
		}
	}

	int to_int() {
		int iret = 0;
		for (int idigit = CTRIT - 1; idigit >= 0; --idigit) {
			iret *= 3;
			switch ((char)rgdigit[idigit]) {
				case 'T':
					iret++;
					break;
				case 'F':
					iret--;
					break;
			}
		}
		return iret;
	}

	Trit &operator[](int idx) {
		assert(idx >= 0 && idx < CTRIT);
		return rgdigit[idx];
	}

	Tryte operator~() {
		Tryte Tryte;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
		{
			Tryte.rgdigit[idigit] = ~rgdigit[idigit];
		}
		return Tryte;
	}

	Tryte operator&(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] & other.rgdigit[idigit];
		return Tryte;
	}
	Tryte operator|(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] | other.rgdigit[idigit];
		return Tryte;
	}
	Tryte operator^(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] ^ other.rgdigit[idigit];
		return Tryte;
	}

	Tryte operator+(Tryte &other) {
		return Tryte(to_int() + other.to_int());
	}

	Tryte operator++(int) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			rgdigit[idigit]++;
			if ((char)rgdigit[idigit] != 'F')
				break;
		}
		return *this;
	}

	Tryte operator--(int) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			rgdigit[idigit]--;
			if ((char)rgdigit[idigit] != 'T')
				break;
		}
		return *this;
	}

	bool operator==(Tryte &other) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			if (((char)rgdigit[idigit] != (char)other.rgdigit[idigit]))
				return false;
		}
		return true;
	}

	/*
	** TODO
	*/
	static Tryte SHR(Tryte &t1) {
		t1++;
		return t1;
	}

	/*
	** TODO
	*/
	static Tryte SHL(Tryte &t1) {
		t1++;
		return t1;
	}

	operator bool() {
		return this->to_int() != 0;
	}

	operator int() = delete;

	std::string str() {
		reinterpret_cast<char&>(rgdigit[CTRIT]) = '\0';
		std::string str((char*)rgdigit);
		std::reverse(str.begin(), str.end());
		return str;
	}

private:
	Trit rgdigit[CTRIT + 1];
};

#endif