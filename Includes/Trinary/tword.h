/*
**
** Made by T4lus
** Trinary TWord Implementation
** TUF syntax
** 1 TWord -> 27 Trit
** 
*/

#ifndef TWORD_H
#define TWORD_H

#include <algorithm>
#include <string>

#include <assert.h>
#include <string.h>

#include "trit.h"

class TWord {
public:
	static const int CTRIT = 27;
	static const int TWord_MAX = 9841;

	TWord() {
	}

	TWord(int int8) {
		int ival = int8;
		bool fneg = ival < 0;

		if (abs(int8) >= TWord_MAX)
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

	TWord(const char *sz) {
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

	TWord operator~() {
		TWord TWord;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
		{
			TWord.rgdigit[idigit] = ~rgdigit[idigit];
		}
		return TWord;
	}

	TWord operator&(TWord &other) {
		TWord TWord;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			TWord[idigit] = rgdigit[idigit] & other.rgdigit[idigit];
		return TWord;
	}
	TWord operator|(TWord &other) {
		TWord TWord;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			TWord[idigit] = rgdigit[idigit] | other.rgdigit[idigit];
		return TWord;
	}
	TWord operator^(TWord &other) {
		TWord TWord;
		for (int idigit = 0; idigit < CTRIT; ++idigit)
			TWord[idigit] = rgdigit[idigit] ^ other.rgdigit[idigit];
		return TWord;
	}

	TWord operator+(TWord &other) {
		return TWord(to_int() + other.to_int());
	}

	TWord operator++(int) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			rgdigit[idigit]++;
			if ((char)rgdigit[idigit] != 'F')
				break;
		}
		return *this;
	}

	TWord operator--(int) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			rgdigit[idigit]--;
			if ((char)rgdigit[idigit] != 'T')
				break;
		}
		return *this;
	}

	bool operator==(TWord &other) {
		for (int idigit = 0; idigit < CTRIT; ++idigit) {
			if (((char)rgdigit[idigit] != (char)other.rgdigit[idigit]))
				return false;
		}
		return true;
	}

	static TWord SHR(TWord &t1, unsigned int nb) {
		std::string start = t1.str().substr(0, t1.str().size()-nb );
		start.insert(0, nb, 'U');
		t1 = start.c_str();
		return t1;
	}

	static TWord SHL(TWord &t1, unsigned int nb) {
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
		reinterpret_cast<char&>(rgdigit[CTRIT]) = '\0';
		std::string str((char*)rgdigit);
		std::reverse(str.begin(), str.end());
		return str;
	}

private:
	Trit rgdigit[CTRIT + 1];
};

#endif