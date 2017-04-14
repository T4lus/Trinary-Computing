
#ifndef UTILS_H
#define UTILS_H

std::string trim(const std::string& str, const std::string& whitespace = " \t");
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
std::string fromRaw(std::string raw);

bool isInteger(const std::string & s);
bool isHex(std::string const& s);

int getNumber(std::string);

#endif