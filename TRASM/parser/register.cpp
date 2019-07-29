#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "../parser.h"

std::map<std::string, int> tryte_register_tab = {
	{"hh", -10}, {"hm", -11}, {"hl", -12},
    {"gh",  -7}, {"gm",  -8}, {"gl",  -9},
    {"fh",  -4}, {"fm",  -5}, {"fl",  -6},
    {"eh",  -1}, {"em",  -2}, {"el",  -3},

    {"ah",   1}, {"am",   2}, {"al",   3},
    {"bh",   4}, {"bm",   5}, {"bl",   6},
    {"ch",   7}, {"cm",   8}, {"cl",   9},
    {"dh",  10}, {"dm",  11}, {"dl",  12}, 
};

std::map<std::string, int> word_register_tab = {
    {"hx", -4},
    {"gx", -3},
    {"fx", -2},
    {"ex", -1},
    
    {"ax",  1},	
	{"bx",  2},
	{"cx",  3},
	{"dx",  4},
};

std::map<int, std::map<std::string, int>> trinium_register = {
    {-1, tryte_register_tab},
    { 0, word_register_tab}
};

std::map<std::string, int> register_tab = {
	{"ra", 0},	
	{"rb", 1},
	{"rc", 2},
	{"rd", 3},

	{"sp", 4},		//stack pointer
	{"ip", 5},		//instruction pointer
	{"lr", 6},		//link register

	{"n2", 7},	    //@TODO
	{"n3", 8},	    //@TODO
};

#define T_REGISTER_TRYTE               -1
#define T_REGISTER_WORD                 0
#define T_REGISTER_                     1

#define T_ADDRESSING_MODE_OFFSET_SRC   -1
#define T_ADDRESSING_MODE_NONE          0
#define T_ADDRESSING_MODE_OFFSET_DST    1

bool Parser::isRegister(std::string value) {
    if ( trinium_register[-1].find(value) != trinium_register[-1].end() || trinium_register[0].find(value) != trinium_register[0].end() ) {
        return true;
    } else {
        return false;
    }
}

int Parser::getRegisterType(std::string value) {
    if ( trinium_register[-1].find(value) != trinium_register[-1].end()) {
        return T_REGISTER_TRYTE;
    } else if (trinium_register[0].find(value) != trinium_register[0].end()) {
        return T_REGISTER_WORD;
    } else {
        return true;
    }
}

Tryte Parser::parseRegister(std::string value, Tryte regDst) {
    return Tryte::SHL(regDst, 4).to_int() + ((getRegisterType(value) * 27) + trinium_register[getRegisterType(value)][value]);
}