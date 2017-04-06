
#include <iostream>

#include "utils.h"

std::string trim(const std::string& str, const std::string& whitespace) {
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str, const std::string& fill, const std::string& whitespace) {
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

std::string fromRaw(std::string raw) {
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

bool isInteger(const std::string & s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) 
		return false ;

	char * p ;
	strtol(s.c_str(), &p, 10) ;

	return (*p == 0) ;
}

bool isHex(std::string const& s) {
  return s.compare(0, 2, "0x") == 0
	  && s.size() > 2
	  && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}