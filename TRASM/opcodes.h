/*
**
** Made by T4lus
** Trinary ASM OPCODE
** 
*/

#ifndef OPCODES_H
#define OPCODES_H

#include <functional>
#include <map>

#include <Trinary/tryte.h>
#include "parser.h"
#include "types.h"

#define OP_REGEX			"^[\\t ]*(?:([.A-Za-z0-9_]+[:]))?(?:[\\t ]*([A-Za-z]{2,4})(?:[\\t ]+(@[A-Za-z0-9_]+(?:(?:\\+|-)[0-9]+)?|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+)(?:[\\t ]*[,][\\t ]*(@[A-Za-z0-9_]+(?:(?:\\+|-)[0-9]+)?|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?(?:[\\t ]*[,][\\t ]*(@[A-Za-z0-9_]+(?:(?:\\+|-)[0-9]+)?|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?)?)?"
							//^[\t ]*(?:([.A-Za-z0-9_]+[:]))?(?:[\t ]*([A-Za-z]{2,4})(?:[\t ]+(\[[A-Za-z0-9_]+(?:(?:\+|-)[0-9]+)?\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+)(?:[\t ]*[,][\t ]*(\[[A-Za-z0-9_]+(?:(?:\+|-)[0-9]+)?\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?(?:[\t ]*[,][\t ]*(\[[A-Za-z0-9_]+(?:(?:\+|-)[0-9]+)?\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?)?)?


#define TOKEN_COMMENT		'#'
#define TOKEN_LABEL 		':'
#define TOKEN_SEPARATOR 	','
#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

// #define T_REGISTER				1
// #define T_REGISTER_ADDRESS     	2
// #define T_ADDRESS       			4
// #define T_NUMBER      			8

#define T_REGISTER_ADDRESS

#define T_REGISTER				1
#define T_NUMBER      			2
#define T_LABEL      			4
#define T_ADDRESS		     	8
#define T_OFFSET       			16


extern  std::map<std::string, op_t> op_tab;

#endif