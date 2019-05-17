#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

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

#define STR_PAD_RIGHT   1
#define STR_PAD_LEFT    2

std::string str_pad(std::string s, int pad_size, char pad_char = ' ', int pad_type = STR_PAD_RIGHT) {
    if (s.size() < pad_size && (pad_type == STR_PAD_RIGHT || pad_type == STR_PAD_LEFT)) {
        s.insert((pad_type == STR_PAD_LEFT ? s.begin() : s.end()), pad_size - s.size(), pad_char);
    }
    return s;
}

const std::vector<std::string> explode(const std::string& s, const char& c) {
	std::string buff{""};
	std::vector<std::string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

#endif