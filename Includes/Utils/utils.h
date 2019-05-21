#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Trinary/tryte.h>

//Strings Utils
#define STR_PAD_RIGHT   1
#define STR_PAD_LEFT    2

void chomp(std::string& str);
std::string trim(const std::string& str, const std::string& whitespace = " \t");
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
std::string fromRaw(std::string raw);
std::string toRaw(std::string str);
std::string str_pad(std::string s, int pad_size, char pad_char = ' ', int pad_type = STR_PAD_RIGHT);
const std::vector<std::string> explode(const std::string& s, const char& c);

//Numbers Utils

inline int modulo(int a, int b);

static const std::string HEPT_CHARS = "0123456789ABCDEFGHKMNPRTVXZ";
int heptdec(std::string s);
std::string dechept(int value);

bool isNumber(std::string s);
bool isInteger(std::string s);
bool isHept(std::string s);
bool isHex(std::string s);

int getNumber(std::string str);

#endif