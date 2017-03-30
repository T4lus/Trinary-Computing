/*
**
** Made by T4lus
** Trinary ASM OPCODE
** 
*/

#ifndef OPCODES_H
#define OPCODES_H

#include "trinary.h"

enum OPCODES : int
{
	// Arithmetic + Logic
	NONE	= -1,	// 0000T
	MOV		= 1,
	ADD		= 10,
	SUB		= 14,
	INC		= 18,
	DEC		= 19,
	CMP		= 20,
	JMP		= 30,
	PUSH	= 50,
	POP		= 54,
	CALL	= 55,
	RET		= 57,
	MUL		= 60,
	DIV		= 64,
	
	AND		= 70,
	OR		= 74,
	XOR		= 78,

	NOT		= 82,		//STI (U -> U)
	NOTT	= 83,		//PTI (U -> T)
	NOTF	= 84,		//NTI (U -> F)

	SHL		= 90,
	SHR		= 94
};

#endif