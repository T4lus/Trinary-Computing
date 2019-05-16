#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Trinary/tryte.h>

std::string trim(const std::string& str, const std::string& whitespace = " \t") {
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t"){
	// trim first
	auto result = trim(str, whitespace);

	// replace sub ranges
	auto beginSpace = result.find_first_of(whitespace);
	while (beginSpace != std::string::npos)
	{
		const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
		const auto range = endSpace - beginSpace;

		result.replace(beginSpace, range, fill);

		const auto newStart = beginSpace + fill.length();
		beginSpace = result.find_first_of(whitespace, newStart);
	}

	return result;
}

std::string fromRaw(std::string raw){
	std::string str;
	std::string::const_iterator it = raw.begin();
	
	while (it != raw.end()) {
		char c = *it++;
		if (c == '\\' && it != raw.end()) {
			switch (*it++) {
				case '\\': c = '\\'; break;
				case 'n': c = '\n'; break;
				case 't': c = '\t'; break;
				case '"': c = '"'; break;
				default: continue;
			}
		}
		str += c;
	}
	return str;
}

inline int modulo(int a, int b) {
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

static const std::string HEPT_CHARS = "0123456789ABCDEFGHKMNPRTVXZ";                                        
static const std::string HEPT_CHARS_NEG = "CBA9876543210";
static const std::string HEPT_CHARS_POS = "EFGHKMNPRTVXZ";

int heptDec(std::string s) {
    int value = 0;
    std::string str = s;

    std::reverse(str.begin(), str.end());
    for(int i = 0; i< str.size(); i++)
        value += ((int)HEPT_CHARS.find(str[i]) - 13) * std::pow(27, i);
    return value;
}

std::string heptEnc(Tryte value) {
    return heptEnc(value.to_int());
}
std::string heptEnc(int value) {
    std::string result = "";

    do {
        int pos = value % 27;
        result = std::string(HEPT_CHARS[modulo(pos + 13, 27)] + result);
        value = (value + pos) / 27;
    } while (value != 0);

    return result;
}

bool isInteger(std::string s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) 
		return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return *p == 0;
}

bool isHept(std::string s) {
	return s.compare(0, 2, "3x") == 0 && s.size() > 2 && s.find_first_not_of("0123456789ABCDEFGHKMNPRTVXZ", 2) == std::string::npos;	
}

bool isHex(std::string s) {
  return s.compare(0, 2, "0x") == 0 && s.size() > 2 && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

int getNumber(std::string str) {
	if (isHex(str))
		return strtoul(str.c_str(), NULL, 16);
	if (isHept(str))
		return heptDec(str.substr(2, str.size()-1));
	if (isInteger(str))
		return stoi(str);
}

#endif