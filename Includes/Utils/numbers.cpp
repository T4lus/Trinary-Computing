#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Utils/utils.h>

inline int modulo(int a, int b) {
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

int heptdec(std::string s) {
    int value = 0;
    std::string str = s;

    std::reverse(str.begin(), str.end());
    for(int i = 0; i< str.size(); i++)
        value += ((int)HEPT_CHARS.find(str[i]) - 13) * std::pow(27, i);
    return value;
}

std::string dechept(int value) {
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

bool isNumber(std::string s) {
    if (isInteger(s) || isHex(s) || isHept(s))
        return true;
    return false;
}

int getNumber(std::string str) {
	if (isHex(str))
		return strtoul(str.c_str(), NULL, 16);
	if (isHept(str))
		return heptdec(str.substr(2, str.size()-1));
	if (isInteger(str))
		return stoi(str);
}