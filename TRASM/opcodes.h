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

#include <tryte.h>

#define OP_REGEX			"^[\\t ]*(?:([.A-Za-z0-9_]+[:]))?(?:[\\t ]*([A-Za-z]{2,4})(?:[\\t ]+(\\[[A-Za-z0-9_]+((\\+|-)[0-9]+)?\\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+)(?:[\\t ]*[,][\\t ]*(\\[[A-Za-z0-9_]+((\\+|-)[0-9]+)?\\]|\".+?\"|\'.+?\'|[.A-Za-z0-9_]+))?)?)?"

#define TOKEN_COMMENT		'#'
#define TOKEN_LABEL 		':'
#define TOKEN_SEPARATOR 	','
#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

#define T_REGISTER				1
#define T_ADDRESS       		2
#define T_REGISTER_ADDRESS     	4
#define T_CONSTANT      		8

typedef char    args_type_t;

typedef struct  op_s {
	std::string		opcode;
	char 			nbr_args;
	args_type_t	 	type[4];
	int 			code;
	std::function<std::vector<Tryte>(std::vector<std::string>)>  fct;
} op_t;

extern  std::vector<op_t> op_tab;
extern  std::map<std::string, Tryte> register_tab;

#endif