#ifndef TYPES_H
#define TYPES_H

enum opMapCol {
    lineNumber,
    mnemonic,
    arg1,
    arg2,
    arg3,
    arg4
};

typedef char    								args_type_t;
typedef std::vector<std::vector<std::string>> 	map_t;

typedef struct op_size_s {
	std::string		opcode;
	int 			size;
} op_size_t;

typedef struct maps_s {
	map_t						opMap;
	map_t						byteMap;
	std::vector<op_size_t>		sizeMap;
	std::map<std::string, int>	labelMap;
} maps_t;

typedef struct op_s {
	std::string		opcode;
	char 			nb_args;
	args_type_t	 	type[4];
	int 			value;
	std::function<std::vector<Tryte>(std::vector<std::string>, maps_t)>  fct;
} op_t;

#endif