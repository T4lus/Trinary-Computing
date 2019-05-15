#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

#include <Trinary/tryble.h>

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

static const std::string HEPT_CHARS = "0123456789ABCDEFGHKMNPRTVXZ";
                                           
static const std::string HEPT_CHARS_NEG = "CBA9876543210";
static const std::string HEPT_CHARS_POS = "EFGHKMNPRTVXZ";

std::string heptEnc(const int &value){

}

int uheptDec(const std::string &s){
    int value = 0;

    std::string str = s;

    std::reverse(str.begin(), str.end());
    for(int i = 0; i< str.size(); i++) {
        value += HEPT_CHARS.find(str[i]) * std::pow(27, i);
    }
    return value;
}

int heptDec(const std::string &s){
    int value = 0;

    for(int i = s.size()-1; i>=0; --i) {
    
        if (s[i] == 'D')
            value += 0 * std::pow(14, (s.size() - 1) - i);
        else if (s.find_first_not_of(HEPT_CHARS_POS) == std::string::npos)
            value += (HEPT_CHARS_POS.find(s[i])+1) * std::pow(14, (s.size() - 1) - i);
        else if (s.find_first_not_of(HEPT_CHARS_NEG) == std::string::npos)
            value += -1 * (HEPT_CHARS_NEG.find(s[i])+1) * std::pow(14, (s.size() - 1) - i);
    }

    return value;
}

bool isInteger(const std::string & s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) 
		return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return *p == 0;
}

bool isHept(std::string const& s) {
	return s.compare(0, 2, "0t") == 0 && s.size() > 2 && s.find_first_not_of("0123456789ABCDEFGHKMNPRTVXZ", 2) == std::string::npos;	
}

bool isHex(std::string const& s) {
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