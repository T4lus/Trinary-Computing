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
#include <cmath>

#include <assert.h>
#include <string.h>

#include "trit.h"

#define TRYTE_CTRIT 9
#define TRYTE_MAX	(std::pow(3, TRYTE_CTRIT) - 1)/2

class Tryte {
public:
	Tryte() {
	}

	Tryte(int int8) {
		int ival = int8;
		bool fneg = ival < 0;

		if (abs(int8) >= TRYTE_MAX)
			ival = 0;

		if (fneg)
			ival = -ival;

		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit) {
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
		assert(cch <= TRYTE_CTRIT);
		int itrit = 0;
		while (cch > 0) {
			--cch;
			rgdigit[itrit] = sz[cch];
			++itrit;
		}
	}

	Trit &operator[](int idx) {
		assert(idx >= 0 && idx < TRYTE_CTRIT);
		return rgdigit[idx];
	}

	Tryte operator~() {
		Tryte Tryte;
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit)
		{
			Tryte.rgdigit[idigit] = ~rgdigit[idigit];
		}
		return Tryte;
	}

	Tryte operator&(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] & other.rgdigit[idigit];
		return Tryte;
	}
	Tryte operator|(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] | other.rgdigit[idigit];
		return Tryte;
	}
	Tryte operator^(Tryte &other) {
		Tryte Tryte;
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit)
			Tryte[idigit] = rgdigit[idigit] ^ other.rgdigit[idigit];
		return Tryte;
	}

	Tryte operator+(Tryte &other) {
		return Tryte(to_int() + other.to_int());
	}

	Tryte operator++(int) {
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit) {
			rgdigit[idigit]++;
			if ((char)rgdigit[idigit] != 'F')
				break;
		}
		return *this;
	}

	Tryte operator--(int) {
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit) {
			rgdigit[idigit]--;
			if ((char)rgdigit[idigit] != 'T')
				break;
		}
		return *this;
	}

	bool operator==(Tryte &other) {
		for (int idigit = 0; idigit < TRYTE_CTRIT; ++idigit) {
			if (((char)rgdigit[idigit] != (char)other.rgdigit[idigit]))
				return false;
		}
		return true;
	}

	static Tryte SHR(Tryte &t1, unsigned int nb) {
		std::string start = t1.str().substr(0, t1.str().size()-nb );
		start.insert(0, nb, 'U');
		t1 = start.c_str();
		return t1;
	}

	static Tryte SHL(Tryte &t1, unsigned int nb) {
		std::string start = t1.str().substr( nb, t1.str().size() );
		start.append(nb, 'U');
		t1 = start.c_str();
		return t1;
	}

	operator bool() {
		return this->to_int() != 0;
	}

	operator int() {
		return this->to_int();
	}

	int to_int() {
		int iret = 0;
		for (int idigit = TRYTE_CTRIT - 1; idigit >= 0; --idigit) {
			iret += ((char)rgdigit[idigit] == 'T' ? 1 : (char)rgdigit[idigit] == 'F' ? -1 : 0) * std::pow(3, idigit);
		}
		return iret;
	}

	std::string str() {
		reinterpret_cast<char&>(rgdigit[TRYTE_CTRIT]) = '\0';
		std::string str((char*)rgdigit);
		std::reverse(str.begin(), str.end());
		return str;
	}

private:
	Trit rgdigit[TRYTE_CTRIT + 1];
};

#endif