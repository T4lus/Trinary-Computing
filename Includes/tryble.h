/*
**
** Made by T4lus
** Trinary Tryble Implementation
** TUF syntax
** 1 Tryble -> 3 Trit
** 
*/

#ifndef TRYBLE_H
#define TRYBLE_H

#include <algorithm>
#include <string>
#include <cmath>

#include <assert.h>
#include <string.h>

#include <trit.h>

#define TRYBLE_CTRIT 3
#define TRYBLE_MAX	(std::pow(3, TRYBLE_CTRIT) - 1)/2

class Tryble {
public:
	Tryble() {
	}

	Tryble(int int8) {
		int ival = int8;
		bool fneg = ival < 0;

		if (abs(int8) >= TRYBLE_MAX)
			ival = 0;

		if (fneg)
			ival = -ival;

		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit) {
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

	Tryble(const char *sz) {
		int cch = strlen(sz);
		assert(cch <= TRYBLE_CTRIT);
		int itrit = 0;
		while (cch > 0) {
			--cch;
			rgdigit[itrit] = sz[cch];
			++itrit;
		}
	}

	int to_int() {
		int iret = 0;
		for (int idigit = TRYBLE_CTRIT - 1; idigit >= 0; --idigit) {
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
		assert(idx >= 0 && idx < TRYBLE_CTRIT);
		return rgdigit[idx];
	}

	Tryble operator~() {
		Tryble Tryble;
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit)
		{
			Tryble.rgdigit[idigit] = ~rgdigit[idigit];
		}
		return Tryble;
	}

	Tryble operator&(Tryble &other) {
		Tryble Tryble;
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit)
			Tryble[idigit] = rgdigit[idigit] & other.rgdigit[idigit];
		return Tryble;
	}
	Tryble operator|(Tryble &other) {
		Tryble Tryble;
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit)
			Tryble[idigit] = rgdigit[idigit] | other.rgdigit[idigit];
		return Tryble;
	}
	Tryble operator^(Tryble &other) {
		Tryble Tryble;
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit)
			Tryble[idigit] = rgdigit[idigit] ^ other.rgdigit[idigit];
		return Tryble;
	}

	Tryble operator+(Tryble &other) {
		return Tryble(to_int() + other.to_int());
	}

	Tryble operator++(int) {
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit) {
			rgdigit[idigit]++;
			if ((char)rgdigit[idigit] != 'F')
				break;
		}
		return *this;
	}

	Tryble operator--(int) {
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit) {
			rgdigit[idigit]--;
			if ((char)rgdigit[idigit] != 'T')
				break;
		}
		return *this;
	}

	bool operator==(Tryble &other) {
		for (int idigit = 0; idigit < TRYBLE_CTRIT; ++idigit) {
			if (((char)rgdigit[idigit] != (char)other.rgdigit[idigit]))
				return false;
		}
		return true;
	}

	static Tryble SHR(Tryble &t1, unsigned int nb) {
		std::string start = t1.str().substr(0, t1.str().size()-nb );
		start.insert(0, nb, 'U');
		t1 = start.c_str();
		return t1;
	}

	static Tryble SHL(Tryble &t1, unsigned int nb) {
		std::string start = t1.str().substr( nb, t1.str().size() );
		start.append(nb, 'U');
		t1 = start.c_str();
		return t1;
	}

	operator bool() {
		return this->to_int() != 0;
	}

	operator int() = delete;

	std::string str() {
		reinterpret_cast<char&>(rgdigit[TRYBLE_CTRIT]) = '\0';
		std::string str((char*)rgdigit);
		std::reverse(str.begin(), str.end());
		return str;
	}

private:
	Trit rgdigit[TRYBLE_CTRIT + 1];

};

#endif