; ----------------------------------------------------------------------------
;Micro-Soft Altair BASIC 3.2 (4K) - Annotated Disassembly
;	
;Copyright 1975, Bill Gates, Paul Allen, Monte Davidoff
;Source: http://altairbasic.org/ compiled by Reuben Harris
;Additional cleanup, relocation by Charles Mangin, March, 2019
; ----------------------------------------------------------------------------
           	
    Start:
    	DI	
    JMP Init	   
    DW 0490h	
    DW 07F9h	
    
    SyntaxCheck:
        MOV A,M	;A=Byte of BASIC program.
        XTHL	;HL=return address.
        CMP M	;Compare to byte expected.
        INX H	;Return address++;
        XTHL	;
    JNZ SyntaxError	;Error if not what was expected.
    
    NextChar:
        INX H	
        MOV A,M	
        CPI 0x3A	
        RNC	
    JMP NextChar_tail	
    
    OutChar:
        PUSH PSW	
    LDA TERMINAL_X	
    JMP OutChar_tail	
        NOP	
    
    CompareHLDE:
        MOV A,H	
        SUB D	
        RNZ	
        MOV A,L	
        SUB E	
        RET	
    TERMINAL_Y:
        DB 01	
    TERMINAL_X:
        DB 00	
  	FTestSign:
      	LDA FACCUM+3	
      		ORA A	
  		JNZ FTestSign_tail	
      		RET	
      	PushNextWord:
          	XTHL	
  		SHLD L003A+1	
      		POP H	
      		MOV C,M	
      		INX H	
      		MOV B,M	
      		INX H	
      		PUSH B	
  	L003A:
      	JMP L003A	
    KW_INLINE_FNS:
        DW Sgn	
        DW Int	
        DW Abs	
        DW FunctionCallError	
        DW Sqr	
        DW Rnd	
        DW Sin	
    KW_ARITH_OP_FNS:
        DB 79h
        DW FAdd	;+
        DB 79h
        DW FSub	;-
        DB 7Ch 
        DW FMul	;*
        DB 7Ch 
        DW FDiv	;/
  	KEYWORDS	
        DB 454EC4h	            ;"END"	80
  		DB 464FD2h	            ;"FOR"
		DB 4E4558D4h	        ;"NEXT"	82
		DB 444154C1h	        ;"DATA"	83
		DB 494E5055D4h	        ;"INPUT"	84      	
  		DB 4449CDh	            ;"DIM"	85
		DB 524541C4h	        ;"READ"	86
  		DB 4C45D4h	            ;"LET"	87
		DB 474F54CFh	        ;"GOTO"	88
  		DB 5255CEh	            ;"RUN"	89
    	DB 49C6h	            ;"IF"	8A
		DB 524553544F52C5h      ;"RESTORE"	8B
		DB 474F5355C2h	        ;"GOSUB"	8C      	
		DB 5245545552CEh	    ;"RETURN"	8D
  		DB 5245CDh	            ;"REM"	8E
		DB 53544FD0h	        ;"STOP"	8F
		DB 5052494ED4h	        ;"PRINT"	90
		DB 4C4953D4h	        ;"LIST"	91
		DB 434C4541D2h	        ;"CLEAR"	92
  		DB 4E45D7h	            ;"NEW"	93
		DB 544142A8h	        ;"TAB("	94
    	DB 54CFh	            ;"TO"	95
		DB 544845CEh	        ;"THEN"	96
		DB 535445D0h	        ;"STEP"	97
        DB 0xAB	                ; "+"	98
        DB 0xAD	                ; "-"	99
        DB 0xAA	                ; "*"	9A
        DB 0xAF	                ; "/"	9B
        DB 0xBE	                ; ">"	9C
        DB 0xBD	                ; "="	9D
        DB 0xBC	                ; "<"	9E 
  		DB 5347CEh	; 	"SGN"	9F
  		DB 494ED4h	; 	"INT"	A0
  		DB 4142D3h	; 	"ABS"	A1
  		DB 5553D2h	; 	"USR"	A2
  		DB 5351D2h	; 	"SQR"	A3
  		DB 524EC4h	; 	"RND"	A4
  		DB 5349CEh	; 	"SIN"	A5
      	DB 0x00	; 	 	

    	KW_GENERAL_FNS:
        	DW Stop	;END
    		DW For	;FOR
    		DW Next	;NEXT
    		DW FindNextStatement	;DATA
    		DW Input	;INPUT
    		DW Dim	;DIM
    		DW Read	;READ
    		DW Let	;LET
    		DW Goto	;GOTO
    		DW Run	;RUN
    		DW If	;IF
    		DW Restore	;RESTORE
    		DW Gosub	;GOSUB
    		DW Return	;RETURN
    		DW Rem	;REM
    		DW Stop	;STOP
    		DW Print	;PRINT
    		DW List	;LIST
    		DW Clear	;CLEAR
    		DW New	;NEW
              	
    	ERROR_CODES:
        	DB 4EC6h	;"NF"	NEXT without FOR.
    		DB 53CEh	;"SN"	Syntax Error
    		DB 52C7h	;"RG"	RETURN without GOSUB.
    		DB 4FC4h	;"OD"	Out of Data
    		DB 46C3h	;"FC"	Illegal Function Call
    		DB 4FD6h	;"OV"	Overflow.
    		DB 4FCDh	;"OM"	Out of memory.
    		DB 55D3h	;"US"	Undefined Subroutine
    		DB 42D3h	;"BS"	Bad Subscript
    		DB 44C4h	;"DD"	Duplicate Definition
    		DB 2FB0h	;"\0"	Division by zero.
    		DB 49C4h	;"ID"	Invalid in Direct mode. 	
      	 	DB ','	; 
	LINE_BUFFER:
    	DW 0000,0000,0000,0000h	;72 chars
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;
		DW 0000,0000,0000,0000h	;		
	
              	
      	DIM_OR_EVAL	DB 00h	; 
      	INPUT_OR_READ	DB 00h	; 
    	PROG_PTR_TEMP	DW 0000h	;
    	L015F	DW 0000h	;
    	CURRENT_LINE	DW 0000h	;
    	STACK_TOP	DW 0F1Ah	; RELOCATE***
    	PROGRAM_BASE	DW 0000h	;
    	VAR_BASE	DW 0000h	;
    	VAR_ARRAY_BASE	DW 0000h	;
    	VAR_TOP	DW 0000h	;
    	DATA_PROG_PTR	DW 0000h	;
	FACCUM	DB 00000000h	;
    FTEMP	DB 00h	;
	FBUFFER	DW 0000,0000,0000
    	
		DW 0000,0000,0000
    	
      		DB 00	;
	szError	DB 0x20,0x45,0x52,0x52,0x4F,0xD2,0x00	;" ERROR\0"	 
  	
	szIn	DB 0x20,0x49,0x4E,0xA0,0x00	;" IN \0"
      	
	szOK	DB 0x0D,0x4F,0xCB,0x0D,0x00	;"\rOK\r\0"	 
      	
  	GetFlowPtr	LXI H,0004h	;HL=SP+4 (ie get word
      		DAD SP	;just past return addr)
      		MOV A,M	;
      		INX H	;
    		CPI 0x81	;'FOR'?
      		RNZ	;Return if not 'FOR'
      		RST 6	; RST PushNextWord	;PUSH (HL)
      		XTHL	;POP HL (ie HL=(HL))
      		RST 4	; RST CompareHLDE	;HL==DE?
  		LXI B,000Dh	;
      		POP H	;Restore HL
      		RZ	;Return if var ptrs match.
      		DAD B	;HL+=000D
  		JMP GetFlowPtr+4	;Loop
  	CopyMemoryUp	CALL CheckEnoughMem;
      		PUSH B	;Exchange BC with HL.
      		XTHL	;
      		POP B	;
      	CopyMemLoop	RST 4	;HL==DE?
      		MOV A,M	;
      		STAX B	;
      		RZ	;Exit if DE reached.
      		DCX B	;
      		DCX H	;
  		JMP CopyMemLoop	;
      	CheckEnoughVarSpace	PUSH H	;
  		LHLD VAR_TOP	;
    		MVI B,00h	;BC=C*4
      		DAD B	;
      		DAD B	;
  		CALL CheckEnoughMem;
      		POP H	;
      		RET	;
      	CheckEnoughMem	PUSH D	;
      		XCHG	;
  		LXI H,0xFFDE	;HL=-34 (extra 2 bytes for return address)
      		DAD SP	;
      		RST 4	;
      		XCHG	;
      		POP D	;
      		RNC	;
    	OutOfMemory	MVI E,0Ch	;
      		DB 01	;LXI B,....	;
    	SyntaxError	MVI E,02h	;
      		DB 01	;LXI B,....	;
    	DivideByZero	MVI E,14h	;
  	Error	CALL ResetStack	;
  		CALL NewLine	;
  		LXI H,ERROR_CODES	;
      		MOV D,A	;
    		MVI A,'?'	;Print '?'
      		RST 03	;RST OutChar	;
      		DAD D	;HL points to error code.
      		MOV A,M	;
      		RST 03	;RST OutChar 11 011 111	;Print first char of code.
      		RST 02	;RST NextChar 11 010 111	;
      		RST 03	;RST OutChar	;Print second char of code.
  		LXI H,szError	;Print " ERROR".
  		CALL PrintString	;
  		LHLD CURRENT_LINE	;
      		MOV A,H	;
      		ANA L	;
      		INR A	;
  		CNZ PrintIN	;
      		DB 01	;LXI B,....	;LXI over Stop and fall into Main
      	Stop	RNZ	;Syntax Error if args.
      		POP B	;Lose return address.
  	Main	LXI H,szOK	; 
  		CALL Init	;
  	GetNonBlankLine	LXI H,0xFFFF	;
  		SHLD CURRENT_LINE	;
  		CALL InputLine	; 
      		RST 02	;RST NextChar	; 
      		INR A	;
      		DCR A	; 
  		JZ GetNonBlankLine	; 
      		PUSH PSW	 
  		CALL LineNumberFromStr	 
      		PUSH D	 
  		CALL Tokenize	 
      		MOV B,A	
      		POP D	 
      		POP PSW	 
  		JNC Exec	 
      	StoreProgramLine	PUSH D	;Push line number
      		PUSH B	;Push line length
      		RST 02	;RST NextChar	;Get first char of line
      		ORA A	;Zero set if line is empty (ie removing a line)
      		PUSH PSW	;Preserve line-empty flag
  		CALL FindProgramLine	;Get nearest program line address in BC.
      		PUSH B	;Push line address.
  		JNC InsertProgramLine	;If line doesn't exist, jump ahead to insert it.
      	RemoveProgramLine	XCHG	;DE=Next line address.
  		LHLD VAR_BASE	;
      	RemoveLine	LDAX D	;Move byte of program remainder down
      		STAX B	;in memory.
      		INX B	;
      		INX D	;
      		RST 4	;Loop until DE==VAR_BASE, ie whole
  		JNZ RemoveLine	;program remainder done.
      		MOV H,B	;
      		MOV L,C	;Update VAR_BASE from BC.
  		SHLD VAR_BASE	;
      	InsertProgramLine	POP D	;DE=Line address (from 224)
      		POP PSW	;Restore line-empty flag (see above)
  		JZ UpdateLinkedList;If line is empty, then we don't need to insert it so can jump ahead.
  		LHLD VAR_BASE	;
      		XTHL	;HL = Line length (see 21D)
      		POP B	;BC = VAR_BASE
      		DAD B	;HL = VAR_BASE + line length.
      		PUSH H	;
  		CALL CopyMemoryUp	;Move remainder of program so there's enough space for the new line.
      		POP H	;
  		SHLD VAR_BASE	;Update VAR_BASE
      		XCHG	;HL=Line address, DE=VAR_BASE
      		MOV M,H	;???
      		INX H	;Skip over next line ptr (updated below)
      		INX H	;
      		POP D	;DE = line number (see 21C)
      		MOV M,E	;Write line number to program line memory.
      		INX H	;
      		MOV M,D	;
      		INX H	;
  	CopyFromBuffer	LXI D,LINE_BUFFER	;Copy the line into the program.
      		LDAX D	;
      		MOV M,A	;
      		INX H	;
      		INX D	;
      		ORA A	;
  		JNZ CopyFromBuffer+3;
  	UpdateLinkedList	CALL ResetAll	;
      		INX H	;
      		XCHG	;
      	L0265	MOV H,D	;
      		MOV L,E	;
      		MOV A,M	;If the pointer to the next line is a null
      		INX H	;word then we've reached the end of the
      		ORA M	;program, job is done, and we can jump back
  		JZ GetNonBlankLine	;to let the user type in the next line.
      		INX H	;Skip over line number.
      		INX H	;
      		INX H	;
      		XRA A	;
      	L0271	CMP M	;
      		INX H	;
  		JNZ L0271	;
      		XCHG	;
      		MOV M,E	;
      		INX H	;
      		MOV M,D	;
  		JMP L0265	;
  	FindProgramLine	LHLD PROGRAM_BASE	;
      		MOV B,H	;BC=this line
      		MOV C,L	;
      		MOV A,M	;If we've found two consecutive
      		INX H	;null bytes, then we've reached the end
      		ORA M	;of the program and so return.
      		DCX H	;
      		RZ	;
      		PUSH B	;Push this line address
      		RST 6	;Push (next line address)
      		RST 6	;Push (this line number)
      		POP H	;HL = this line number
      		RST 4	;Compare line numbers
      		POP H	;HL = next line address
      		POP B	;BC = this line address
      		CMC	;
      		RZ	;Return carry set if line numbers match.
      		CMC	;
      		RNC	;Return if we've reached a line number greater than the one required.
  		JMP FindProgramLine+3	
      	New	RNZ	 
  		LHLD PROGRAM_BASE	 
      		XRA A	
      		MOV M,A	
      		INX H	
      		MOV M,A	
      		INX H	 
  		SHLD VAR_BASE	 
      	Run	RNZ	
  	ResetAll	LHLD PROGRAM_BASE	
      		DCX H	
  	Clear	SHLD PROG_PTR_TEMP	
  		CALL Restore	
  		LHLD VAR_BASE	
  		SHLD VAR_ARRAY_BASE	
  		SHLD VAR_TOP	
      	ResetStack	POP B	
  		LHLD STACK_TOP	
      		SPHL	
      		XRA A	
      		MOV L,A	
      		PUSH H	
      		PUSH B	
  		LHLD PROG_PTR_TEMP	
      		RET	
    	InputLineWith	MVI A,'?'	;Print '?'
      		RST 03	;RST OutChar	;
    		MVI A,' '	;Print ' '
      		RST 03	;RST OutChar	;
  		CALL InputLine	;
      		INX H	;
    	Tokenize	MVI C,05	;Initialise line length to 5.
  		LXI D,LINE_BUFFER	;ie, output ptr is same as input ptr at start.
      		MOV A,M	;
    		CPI ' '	;
  		JZ WriteChar	;
      		MOV B,A	;
    		CPI '"'	;
  		JZ FreeCopy	;
      		ORA A	;
  		JZ Exit	;
      		PUSH D	;Preserve output ptr.
    		MVI B,00	;Initialise Keyword ID to 0.
  		LXI D,KEYWORDS-1	;
      		PUSH H	;Preserve input ptr.
      		DB 3Eh	;LXI over get-next-char
      	KwCompare	RST 02 	; RST 01	; SyntaxCheck0	;Get next input char
      		INX D	;
      		LDAX D	;Get keyword char to compare with.
    		ANI 7Fh	;Ignore bit 7 of keyword char.
  		JZ NotAKeyword	;If keyword char==0, then end of keywords reached.
      		CMP M	;Keyword char matches input char?
  		JNZ NextKeyword	;If not, jump to get next keyword.
      		LDAX D	;
      		ORA A	;
  		JP KwCompare	;
      		POP PSW	;Remove input ptr from stack. We don't need it.
      		MOV A,B	;A=Keyword ID
    		ORI 0x80	;Set bit 7 (indicates a keyword)
      		DB 0xF2	;JP ....	;LXI trick again.
      	NotAKeyword	POP H	;Restore input ptr
      		MOV A,M	;and get input char
      		POP D	;Restore output ptr
      	WriteChar	INX H	;Advance input ptr
      		STAX D	;Store output char
      		INX D	;Advance output ptr
      		INR C	;C++ (arf!).
    		SUI 8Eh	;If it's not the
  		JNZ Tokenize+5	;
      		MOV B,A	;B=0
      	FreeCopyLoop	MOV A,M	;A=Input char
      		ORA A	;If char is null then exit
  		JZ Exit	;
      		CMP B	;If input char is term char then
  		JZ WriteChar	;we're done free copying.
      	FreeCopy	INX H	;
      		STAX D	;
      		INR C	;
      		INX D	;
  		JMP FreeCopyLoop	;
      	NextKeyword	POP H	;Restore input ptr
      		PUSH H	;
      		INR B	;Keyword ID ++;
      		XCHG	;HL=keyword table ptr
      	NextKwLoop	ORA M	;Loop until
      		INX H	;bit 7 of previous
  		JP NextKwLoop	;keyword char is set.
      		XCHG	;DE=keyword ptr, HL=input ptr
  		JMP KwCompare+2	;
  	Exit	LXI H,LINE_BUFFER-1	;
      		STAX D	;
      		INX D	;
      		STAX D	;
      		INX D	;
      		STAX D	;
      		RET	;
      	Backspace	DCR B	;Char count--;
      		DCX H	;Input ptr--;
      		RST 03	;RST OutChar	;Print backspace char.
  		JNZ InputNext	;
      	ResetInput	RST 03	;RST OutChar	;
  		CALL NewLine	;
  	InputLine	LXI H,LINE_BUFFER	;
    		MVI B,01	;
  	InputNext	CALL InputChar	;
    		CPI 0x0D	;
  		JZ TerminateInput	;
    		CPI ' '	;If < ' '
  		JC InputNext	;or
    		CPI 0x7D	;> '}'
  		JNC InputNext	;then loop back.
    		CPI '@'	;
  		JZ ResetInput	;
    		CPI '_'	;
  		JZ Backspace	;
      		MOV C,A	;
      		MOV A,B	;
    		CPI 0x48	;
    		MVI A,07	;
  		JNC L036A	;
      		MOV A,C	;Write char to LINE_BUFFER.
      		MOV M,C	;
      		INX H	;
      		INR B	;
      	L036A	RST 03	;RST OutChar	;
  		JMP InputNext	;
    	OutChar_tail	CPI 0x48	;
  		CZ NewLine	;
      		INR A	;
  		STA TERMINAL_X	;
    	WaitTermReady	IN 00	;
    		ANI 80h	;
  		JNZ WaitTermReady	;
      		POP PSW	;
    		OUT 01	;
      		RET	;
    	InputChar	IN 00	; 
    		ANI 01	; 
  		JNZ InputChar	;
    		IN 01	; 
    		ANI 7Fh	; 
      		RET	;
  	List	CALL LineNumberFromStr	
      		RNZ	
      		POP B	;?why get return address?
  		CALL FindProgramLine	
      		PUSH B	
      	ListNextLine	POP H	
      		RST 6	
      		POP B	
      		MOV A,B	
      		ORA C	
  		JZ Main	
  		CALL TestBreakKey	
      		PUSH B	
  		CALL NewLine	
      		RST 6	
      		XTHL	
  		CALL PrintInt	
    		MVI A,' '	
      		POP H	
      	ListChar	RST 03	;RST OutChar	
      		MOV A,M	
      		ORA A	
      		INX H	
  		JZ ListNextLine	
  		JP ListChar	
    		SUI 7Fh	;A is now keyword index + 1.
      		MOV C,A	
      		PUSH H	
  		LXI D,KEYWORDS	
      		PUSH D	
      	ToNextKeyword	LDAX D	
      		INX D	
      		ORA A	
  		JP ToNextKeyword	
      		DCR C	
      		POP H	
  		JNZ ToNextKeyword-1	
      	PrintKeyword	MOV A,M	
      		ORA A	
  		JM ListChar-1	
      		RST 03	;RST OutChar	
      		INX H	
  		JMP PrintKeyword	
  	For	CALL Let	
      		XTHL	
  		CALL GetFlowPtr	
      		POP D	
  		JNZ L03E2	
      		DAD B	
      		SPHL	
      	L03E2	XCHG	
    		MVI C,08	
  		CALL CheckEnoughVarSpace	
      		PUSH H	
  		CALL FindNextStatement	
      		XTHL	
      		PUSH H	
  		LHLD CURRENT_LINE	
      		XTHL	
      		RST 01	; SyntaxCheck; SyntaxCheck	
      		DB 95h	;KWID_TO	
  		CALL EvalExpression	
      		PUSH H	
  		CALL FCopyToBCDE	
      		POP H	
      		PUSH B	
      		PUSH D	
  		LXI B,8100h	
      		MOV D,C	
      		MOV E,D	
      		MOV A,M	
    		CPI 0x97	;KWID_STEP	
    		MVI A,01h	
  		JNZ PushStepValue	
  		CALL EvalExpression+1	
      		PUSH H	
  		CALL FCopyToBCDE	
      		RST 05	; FTestSign	
      		POP H	
      	PushStepValue	PUSH B	
      		PUSH D	
      		PUSH PSW	
      		INX SP	
      		PUSH H	
  		LHLD PROG_PTR_TEMP	
      		XTHL	
    	EndOfForHandler	MVI B,0x81	
      		PUSH B	
      		INX SP	
  	ExecNext	CALL TestBreakKey	
      		MOV A,M	
    		CPI ':'	
  		JZ Exec	
      		ORA A	
  		JNZ SyntaxError	
      		INX H	
      		MOV A,M	
      		INX H	
      		ORA M	
      		INX H	
  		JZ Main	
      		MOV E,M	
      		INX H	
      		MOV D,M	
      		XCHG	
  		SHLD CURRENT_LINE	
      		XCHG	
      	Exec	RST 02	;RST NextChar	
  		LXI D,ExecNext	
      		PUSH D	
      		RZ	
    		SUI 80h	
  		JC Let	
    		CPI 0x14	
  		JNC SyntaxError	
      		RLC	;BC = A*2
      		MOV C,A	
    		MVI B,00h	
      		XCHG	
  		LXI H,KW_GENERAL_FNS	
      		DAD B	
      		MOV C,M	
      		INX H	
      		MOV B,M	
      		PUSH B	
      		XCHG	
      		RST 02	;RST NextChar	
      		RET	
    	NextChar_tail	CPI ' '	
  		JZ NextChar	
    		CPI '0'	
      		CMC	
      		INR A	
      		DCR A	
      		RET	
      	Restore	XCHG	
  		LHLD PROGRAM_BASE	
      		DCX H	
  	L046E	SHLD DATA_PROG_PTR	
      		XCHG	
      		RET	
    	TestBreakKey	IN 00	;Exit if no key pressed.
    		ANI 01	;
      		RNZ	;
  		CALL InputChar	;
    		CPI 0x03	;Break key?
  		JMP Stop	
      	CharIsAlpha	MOV A,M	
    		CPI 'A'	
      		RC	
    		CPI 'Z'+1	
      		CMC	
      		RET	
      	GetSubscript	RST 02	;RST NextChar	
  		CALL EvalExpression	
      		RST 05	; FTestSign	
  		JM FunctionCallError	
  		LDA FACCUM+3	
    		CPI 0x90	
  		JC FAsInteger	
    	FunctionCallError	MVI E,08h	
  		JMP Error	
      	LineNumberFromStr	DCX H	
  		LXI D,0000	
      	NextLineNumChar	RST 02	;RST NextChar	
      		RNC	
      		PUSH H	
      		PUSH PSW	;Preserve flags
  		LXI H,1998h	;Decimal 6552
      		RST 4	
  		JC SyntaxError	
      		MOV H,D	
      		MOV L,E	
      		DAD D	
      		DAD H	
      		DAD D	
      		DAD H	
      		POP PSW	
    		SUI '0'	
      		MOV E,A	
    		MVI D,00h	
      		DAD D	
      		XCHG	
      		POP H	
  		JMP NextLineNumChar	
    	Gosub	MVI C,03h	
  		CALL CheckEnoughVarSpace	
      		POP B	
      		PUSH H	
      		PUSH H	
  		LHLD CURRENT_LINE	
      		XTHL	
    		MVI D,0x8C	
      		PUSH D	
      		INX SP	
      		PUSH B	
  	Goto	CALL LineNumberFromStr	
      		RNZ	
  		CALL FindProgramLine	
      		MOV H,B	
      		MOV L,C	
      		DCX H	
      		RC	
    		MVI E,0Eh	
  		JMP Error	
      	Return	RNZ	
    		MVI D,0xFF	
  		CALL GetFlowPtr	
      		SPHL	
    		CPI 0x8C	
    		MVI E,04h	
  		JNZ Error	
      		POP H	
  		SHLD CURRENT_LINE	
  		LXI H,ExecNext	
      		XTHL	
    	FindNextStatement	DB 013Ah ;LXI B,..3A	
      	Rem	DB 10h	
      		NOP	
      	FindNextStatementLoop	MOV A,M	
      		ORA A	
      		RZ	
      		CMP C	
      		RZ	
      		INX H	
  		JMP FindNextStatementLoop	
  	Let	CALL GetVar	
      		RST 01	; SyntaxCheck	
      		DB 9Dh	
      	AssignVar	PUSH D	
  		CALL EvalExpression	
      		XTHL	
  		SHLD PROG_PTR_TEMP	
      		PUSH H	
  		CALL FCopyToMem	
      		POP D	
      		POP H	
      		RET	
  	If	CALL EvalExpression	
      		MOV A,M	
  		CALL FPush	
    		MVI D,00	
    	GetCompareOpLoop	SUI 9Ch	; KWID_>	
  		JC GotCompareOp	
    		CPI 0x03	
  		JNC GotCompareOp	
    		CPI 0x01	
      		RAL	
      		ORA D	
      		MOV D,A	
      		RST 02	;RST NextChar	
  		JMP GetCompareOpLoop	
      	GotCompareOp	MOV A,D	
      		ORA A	
  		JZ SyntaxError	
      		PUSH PSW	
  		CALL EvalExpression	
      		RST 01	; SyntaxCheck	
      		DB 96h	;KWID_THEN	
      		DCX H	
      		POP PSW	
      		POP B	
      		POP D	
      		PUSH H	
      		PUSH PSW	
  		CALL FCompare	
      		INR A	
      		RAL	
      		POP B	
      		ANA B	
      		POP H	
  		JZ Rem	
      		RST 02	;RST NextChar	
  		JC Goto	
  		JMP Exec+5	
      		DCX H	
      		RST 02	;RST NextChar	
  	Print	JZ NewLine	
      		RZ	
    		CPI '"'	
  		CZ PrintString-1	
  		JZ Print-2	
    		CPI 0x94	;KWID_TAB	 
  		JZ Tab	
      		PUSH H	
    		CPI ','	
  		JZ ToNextTabBreak	
    		CPI ';'	
  		JZ ExitTab	
      		POP B	
  		CALL EvalExpression	
      		PUSH H	
  		CALL FOut	
  		CALL PrintString	
    		MVI A,' '	
      		RST 03	;RST OutChar	
      		POP H	
  		JMP Print-2	
    	TerminateInput	MVI M,00h	
  		LXI H,LINE_BUFFER-1	
    	NewLine	MVI A,0Dh	
  		STA TERMINAL_X	
      		RST 03	;RST OutChar	
    		MVI A,0Ah	
      		RST 03	;RST OutChar	
  		LDA TERMINAL_Y	
      	PrintNullLoop	DCR A	
  		STA TERMINAL_X	
      		RZ	
      		PUSH PSW	
      		XRA A	
      		RST 03	;RST OutChar	
      		POP PSW	
  		JMP PrintNullLoop	
      		INX H	
      	PrintString	MOV A,M	
      		ORA A	
      		RZ	
      		INX H	
    		CPI '"'	
      		RZ	
      		RST 03	;RST OutChar	
    		CPI 0x0D	
  		CZ NewLine	
  		JMP PrintString	
  	ToNextTabBreak	LDA TERMINAL_X	
    		CPI 0x38	
  		CNC NewLine	
  		JNC ExitTab	
    	CalcSpaceCount	SUI 0Eh	
  		JNC CalcSpaceCount	
      		CMA	
  		JMP PrintSpaces	
  	Tab	CALL GetSubscript	
      		RST 01	; SyntaxCheck	
      		DB 29h	;')'	
      		DCX H	
      		PUSH H	
  		LDA TERMINAL_X	
      		CMA	
      		ADD E	
  		JNC ExitTab	
      	PrintSpaces	INR A	
      		MOV B,A	
    		MVI A,' '	
      	PrintSpaceLoop	RST 03	;RST OutChar	
      		DCR B	
  		JNZ PrintSpaceLoop	
      	ExitTab	POP H	
      		RST 02	;RST NextChar	
  		JMP Print+3	
      	Input	PUSH H	
  		LHLD CURRENT_LINE	
    		MVI E,16h	
      		INX H	
      		MOV A,L	
      		ORA H	
  		JZ Error	
  		CALL InputLineWith	
  		JMP L05FA+1	
      	Read	PUSH H	
  		LHLD DATA_PROG_PTR	
    	L05FA	ORI 0xAF	
              		;XRA A	
  		STA INPUT_OR_READ	
      		XTHL	
      		DB 01	;LXI B,....	
      	ReadNext	RST 01	; SyntaxCheck	
      		DB 2Ch	;','	
  		CALL GetVar	
      		XTHL	
      		PUSH D	
      		MOV A,M	
    		CPI ','	
  		JZ GotDataItem	
      		ORA A	
  		JNZ SyntaxError	
  		LDA INPUT_OR_READ	
      		ORA A	
      		INX H	
  		JNZ NextDataLine+1	
    		MVI A,'?'	
      		RST 03	;RST OutChar	
  		CALL InputLineWith	
      	GotDataItem	POP D	
      		INX H	
  		CALL AssignVar	
      		XTHL	
      		DCX H	
      		RST 02	;RST NextChar	
  		JNZ ReadNext	
      		POP D	
  		LDA INPUT_OR_READ	
      		ORA A	
      		RZ	
      		XCHG	
  		JNZ L046E	
      	NextDataLine	POP H	
      		RST 6	
      		MOV A,C	
      		ORA B	
    		MVI E,06h	
  		JZ Error	
      		INX H	
      		RST 02	;RST NextChar	
    		CPI 0x83	;KWID_DATA	 
  		JNZ NextDataLine	
      		POP B	
  		JMP GotDataItem	
  	Next	CALL GetVar	
  		SHLD PROG_PTR_TEMP	
  		CALL GetFlowPtr	
      		SPHL	
      		PUSH D	
      		MOV A,M	
      		INX H	
      		PUSH PSW	
      		PUSH D	
    		MVI E,00h	
  		JNZ Error	
  		CALL FLoadFromMem	
      		XTHL	
      		PUSH H	
  		CALL FAddMem	
      		POP H	
  		CALL FCopyToMem	
      		POP H	
  		CALL FLoadBCDEfromMem	
      		PUSH H	
  		CALL FCompare	
      		POP H	
      		POP B	
      		SUB B	
  		CALL FLoadBCDEfromMem	
  		JZ ForLoopIsComplete	
      		XCHG	
  		SHLD CURRENT_LINE	
      		MOV L,C	
      		MOV H,B	
  		JMP EndOfForHandler	
      	ForLoopIsComplete	SPHL	
  		LHLD PROG_PTR_TEMP	
  		JMP ExecNext	
      	EvalExpression	DCX H	
    		MVI D,00h	
      		PUSH D	
    		MVI C,01h	
  		CALL CheckEnoughVarSpace	
  		CALL EvalTerm	
  		SHLD L015F	
  	ArithParse	LHLD L015F	
      		POP B	
      		MOV A,M	
    		MVI D,00h	
    		SUI 0x98	;KWID_PLUS	
      		RC	
    		CPI 0x04	
      		RNC	
      		MOV E,A	
      		RLC	
      		ADD E	
      		MOV E,A	
  		LXI H,KW_ARITH_OP_FNS	
      		DAD D	
      		MOV A,B	
      		MOV D,M	
      		CMP D	
      		RNC	
      		INX H	
      		PUSH B	
  		LXI B,ArithParse	
      		PUSH B	
      		MOV C,D	;???
  		CALL FPush	
      		MOV D,C	
      		RST 6	
  		LHLD L015F	
  		JMP EvalExpression+3	
      	EvalTerm	RST 02	;RST NextChar	
  		JC FIn	
  		CALL CharIsAlpha	
  		JNC EvalVarTerm	
    		CPI 0x98	;KWID_PLUS	
  		JZ EvalTerm	
    		CPI '.'	
  		JZ FIn	
    		CPI 0x99	;KWID_MINUS	
  		JZ EvalMinusTerm	
    		SUI 9Fh	
  		JNC EvalInlineFn	
      	EvalBracketed	RST 01	; SyntaxCheck	
      		DB 28h	;'('	
  		CALL EvalExpression	
      		RST 01	; SyntaxCheck	
      		DB 29h	;')'	
      		RET	
  	EvalMinusTerm	CALL EvalTerm	
      		PUSH H	
  		CALL FNegate	
      		POP H	
      		RET	
  	EvalVarTerm	CALL GetVar	
      		PUSH H	
      		XCHG	
  		CALL FLoadFromMem	
      		POP H	
      		RET	
    	EvalInlineFn	MVI B,00h	
      		RLC	
      		MOV C,A	
      		PUSH B	
      		RST 02	;RST NextChar	
  		CALL EvalBracketed	
      		XTHL	
  		LXI D,06F1h	
      		PUSH D	
  		LXI B,KW_INLINE_FNS	
      		DAD B	
      		RST 6	
      		RET	
      	DimContd	DCX H	
      		RST 02	;RST NextChar	
      		RZ	
      		RST 01	; SyntaxCheck	
      		DB 2Ch	;','	
  	Dim	LXI B,DimContd	
      		PUSH B	
      		DB 0xF6	
      	GetVar	XRA A	
  		STA DIM_OR_EVAL	
      		MOV B,M	
  		CALL CharIsAlpha	
  		JC SyntaxError	
      		XRA A	
      		MOV C,A	
      		RST 02	;RST NextChar	
  		JNC 072Eh	
      		MOV C,A	
      		RST 02	;RST NextChar	
    		SUI '('	
  		JZ GetArrayVar	
      		PUSH H	
  		LHLD VAR_ARRAY_BASE	
      		XCHG	
  		LHLD VAR_BASE	
      	FindVarLoop	RST 4	
  		JZ AllocNewVar	
      		MOV A,C	
      		SUB M	
      		INX H	
  		JNZ L0747	
      		MOV A,B	
      		SUB M	
      	L0747	INX H	
  		JZ L0782	
      		INX H	
      		INX H	
      		INX H	
      		INX H	
  		JMP FindVarLoop	
      	AllocNewVar	POP H	;HL=prog ptr
      		XTHL	;(SP)=prog ptr, HL=ret.addr.
      		PUSH D	;
  		LXI D,06F6h	;an address inside EvalTerm
      		RST 4	;
      		POP D	;
  		JZ AlreadyAllocd	;
      		XTHL	;(SP)=ret.addr, HL=prog ptr.
      		PUSH H	;Prog ptr back on stack
      		PUSH B	;Preserve var name on stack
  		LXI B,0006h	
  		LHLD VAR_TOP	
      		PUSH H	
      		DAD B	
      		POP B	
      		PUSH H	
  		CALL CopyMemoryUp	
      		POP H	
  		SHLD VAR_TOP	
      		MOV H,B	
      		MOV L,C	
  		SHLD VAR_ARRAY_BASE	
      	InitVarLoop	DCX H	
    		MVI M,00h	
      		RST 4	
  		JNZ InitVarLoop	
      		POP D	
      		MOV M,E	
      		INX H	
      		MOV M,D	
      		INX H	
      	L0782	XCHG	
      		POP H	
      		RET	
  	AlreadyAllocd	STA FACCUM+3	;A was set to zero at 075A.
      		POP H	
      		RET	
      	GetArrayVar	PUSH B	
  		LDA DIM_OR_EVAL	
      		PUSH PSW	
  		CALL GetSubscript	
      		RST 01	; SyntaxCheck	
      		DB 29h	;')'	
      		POP PSW	
  		STA DIM_OR_EVAL	
      		XTHL	
      		XCHG	
      		DAD H	
      		DAD H	
      		PUSH H	
  		LHLD VAR_ARRAY_BASE	
      		DB 0x01	;LXI B,....	
      	FindArray	POP B	
      		DAD B	
      		XCHG	
      		PUSH H	
  		LHLD VAR_TOP	
      		RST 4	
      		XCHG	
      		POP D	
  		JZ AllocArray	
      		RST 6	
      		XTHL	
      		RST 4	
      		POP H	
      		RST 6	
  		JNZ FindArray	
  		LDA DIM_OR_EVAL	
      		ORA A	
    		MVI E,12h	
  		JNZ Error	
      	L07BF	POP D	
      		DCX D	
      		XTHL	
      		RST 4	
    		MVI E,10h	
  		JNC Error	
      		POP D	
      		DAD D	
      		POP D	
      		XCHG	
      		RET	
      	AllocArray	MOV M,E	
      		INX H	
      		MOV M,D	
      		INX H	
  		LXI D,002Ch	
  		LDA DIM_OR_EVAL	
      		ORA A	
  		JZ L07E1
      		POP D	
      		PUSH D	
      		INX D	
      		INX D	
      		INX D	
      		INX D	
      	L07E1	PUSH D	
      		MOV M,E	
      		INX H	
      		MOV M,D	
      		INX H	
      		PUSH H	
      		DAD D	
  		CALL CheckEnoughMem	
  		SHLD VAR_TOP	
      		POP D	
      	InitElements	DCX H	
    		MVI M,00h	
      		RST 4	
  		JNZ InitElements	
  		JMP L07BF	
      	FWordToFloat	MOV D,B	
    		MVI E,00h	
    		MVI B,90h	;exponent=2^16
  		JMP FCharToFloat+5	;
  	FAddOneHalf	LXI H,ONE_HALF	;Load BCDE with (float) 0.5.
  	FAddMem	CALL FLoadBCDEfromMem	
  		JMP FAdd+2	
      	FSub	POP B	;Get lhs in BCDE.
      		POP D	;
  		CALL FNegate	;Negate rhs and slimily
      		DB 0x21	;LXI H,....	;LXI into FAdd + 2.
      	FAdd	POP B	;Get lhs in BCDE.
      		POP D	;
      		MOV A,B	;If lhs==0 then we don't need
      		ORA A	;to do anything and can just
      		RZ	;exit.
  		LDA FACCUM+3	;If rhs==0 then exit via a copy
      		ORA A	;of lhs to FACCUM.
  		JZ FLoadFromBCDE	;
      		SUB B	;A=rhs.exponent-lhs.exponent.
  		JNC L082C	;If rhs' exponent >= lhs'exponent, jump ahead.
      		CMA	;Two's complement the exponent
      		INR A	;difference, so it's correct.
      		XCHG	;
  		CALL FPush	;Push old rhs
      		XCHG	;
  		CALL FLoadFromBCDE	;rhs = old lhs
      		POP B	;lhs = old rhs.
      		POP D	;
      	L082C	PUSH PSW	;Preserve exponent diff
  		CALL FUnpackMantissas	
      		MOV H,A	;H=sign relationship
      		POP PSW	;A=exponent diff.
  		CALL FMantissaRtMult	;Shift lhs mantissa right by (exponent diff) places.
      		ORA H	;A=0 after last call, so this tests
  		LXI H,FACCUM	;the sign relationship.
  		JP FSubMantissas	;Jump ahead if we need to subtract.
  		CALL FAddMantissas	;
  		JNC FRoundUp	;Jump ahead if that didn't overflow.
      		INX H	;Flip the sign in FTEMP_SIGN.
      		INR M	; 
  		JZ Overflow	;Error out if exponent overflowed.
  		CALL FMantissaRtOnce;Shift mantissa one place right
  		JMP FRoundUp	;Jump ahead.
      	FSubMantissas	XRA A	;B=0-B
      		SUB B	;
      		MOV B,A	;
      		MOV A,M	;E=(FACCUM)-E
      		SBB E	;
      		MOV E,A	;
      		INX H	;
      		MOV A,M	;D=(FACCUM+1)-D
      		SBB D	
      		MOV D,A	
      		INX H	
      		MOV A,M	;C=(FACCUM+2)-C
      		SBB C	;
      		MOV C,A	;
  	FNormalise	CC FNegateInt	; 
    	 	MVI H,00h	;
      		MOV A,C	;Test most-significant bit of mantissa
      		ORA A	;and jump ahead if it's 1.
  		JM FRoundUp	;
    	NormLoop	CPI 0xE0	;If we've shifted 32 times,
  		JZ FZero	;then the number is 0.
      		DCR H	;
      		MOV A,B	;Left-shift extra mantissa byte
      		ADD A	; 
      		MOV B,A	; 
  		CALL FMantissaLeft	;Left-shift mantissa.
      		MOV A,H	;
  		JP NormLoop	;Loop
  		LXI H,FACCUM+3	;
      		ADD M	;
      		MOV M,A	;Since A was a -ve number, that certainly should
  		JNC FZero	;have carried, hence the extra check for zero.
      		RZ	;?why?
      	FRoundUp	MOV A,B	;A=extra mantissa byte
  		LXI H,FACCUM+3	;
      		ORA A	;If bit 7 of the extra mantissa byte
  		CM FMantissaInc	;is set, then round up the mantissa.
      		MOV B,M	;B=exponent
      		INX H	;
      		MOV A,M	;A=FTEMP_SIGN
    		ANI 0x80	;
      		XRA C	;Bit 7 of C is always 1. Thi
      		MOV C,A	;
  		JMP FLoadFromBCDE	;Exit via copying BCDE to FACCUM.
      	FMantissaLeft	MOV A,E	
      		RAL	
      		MOV E,A	
      		MOV A,D	
      		RAL	
      		MOV D,A	
      		MOV A,C	
      		ADC A	
      		MOV C,A	
      		RET	
      	FMantissaInc	INR E	
      		RNZ	
      		INR D	
      		RNZ	
      		INR C	
      		RNZ	
    		MVI C,80h	;Mantissa overflowed to zero, so set it
      		INR M	;to 1 and increment the exponent.
      		RNZ	;And if the exponent overflows...
    	Overflow	MVI E,0Ah	
  		JMP Error	
      	FAddMantissas	MOV A,M	
      		ADD E	
      		MOV E,A	
      		INX H	
      		MOV A,M	
      		ADC D	
      		MOV D,A	
      		INX H	
      		MOV A,M	
      		ADC C	
      		MOV C,A	
      		RET	
  	FNegateInt	LXI H,FTEMP	
      		MOV A,M	
      		CMA	
      		MOV M,A	
      		XRA A	
      		MOV L,A	
      		SUB B	
      		MOV B,A	
      		MOV A,L	
      		SBB E	
      		MOV E,A	
      		MOV A,L	
      		SBB D	
      		MOV D,A	
      		MOV A,L	
      		SBB C	
      		MOV C,A	
      		RET	
    	FMantissaRtMult	MVI B,00h	;Initialise extra mantissa byte
      		INR A	
      		MOV L,A	
      	RtMultLoop	XRA A	
      		DCR L	
      		RZ	
  		CALL FMantissaRtOnce	
  		JMP RtMultLoop	
      	FMantissaRtOnce	MOV A,C	
      		RAR	
      		MOV C,A	
      		MOV A,D	
      		RAR	
      		MOV D,A	
      		MOV A,E	
      		RAR	
      		MOV E,A	
      		MOV A,B	;NB: B is the extra
      		RAR	;mantissa byte.
      		MOV B,A	;
      		RET	;
      	FMul	POP B	;Get lhs in BCDE
      		POP D	;
      		RST 05	; FTestSign	;If rhs==0 then exit
      		RZ	;
    		MVI L,00h	;L=0 to signify exponent add
  		CALL FExponentAdd	
      		MOV A,C	
  		STA FMulInnerLoop+13	
      		XCHG	
  		SHLD FMulInnerLoop+8	
  		LXI B,0000h	
      		MOV D,B	
      		MOV E,B	
  		LXI H,FNormalise+3	
      		PUSH H	
  		LXI H,FMulOuterLoop	
      		PUSH H	
      		PUSH H	
  		LXI H,FACCUM	
      	FMulOuterLoop	MOV A,M	;A=FACCUM mantissa byte
      		INX H	;
      		PUSH H	;Preserve FACCUM ptr
    		MVI L,08h	;8 bits to do
      	FMulInnerLoop	RAR	;Test lowest bit of mantissa byte
      		MOV H,A	;Preserve mantissa byte
      		MOV A,C	;A=result mantissa's high byte
  		JNC L0919	;If that bit of multiplicand was 0, then skip over adding mantissas.
      		PUSH H	;
  		LXI H,0000h	;
      		DAD D	;
      		POP D	;
    		ACI 00	;A=result mantissa high byte. This gets back to C
      		XCHG	;in the call to FMantissaRtOnce+1.
  	L0919	CALL FMantissaRtOnce+1	
      		DCR L	
      		MOV A,H	;Restore mantissa byte and
  		JNZ FMulInnerLoop	;jump back if L is not yet 0.
      	PopHLandReturn	POP H	;Restore FACCUM ptr
      		RET	;Return to FMulOuterLoop, or if finished that then exit to FNormalise
  	FDivByTen	CALL FPush	;
  		LXI B,8420h	;BCDE=(float)10;
  		LXI D,0000h	
  		CALL FLoadFromBCDE	
      	FDiv	POP B	 
      		POP D	
      		RST 05	; FTestSign	 
  		JZ DivideByZero	
    		MVI L,0xFF	 
  		CALL FExponentAdd	
      		INR M	 
      		INR M	
      		DCX H	
      		MOV A,M	
  		STA L095F+1	
      		DCX H	
      		MOV A,M	
  		STA L095F-3	
      		DCX H	
      		MOV A,M	
  		STA L095F-7	
      		MOV B,C	
      		XCHG	
      		XRA A	
      		MOV C,A	
      		MOV D,A	
      		MOV E,A	
  		STA L095F+4	
      	FDivLoop	PUSH H	
      		PUSH B	
      		MOV A,L	
    		SUI 00h	
      		MOV L,A	
      		MOV A,H	
    		SBI 00	
      		MOV H,A	
      		MOV A,B	
    	L095F	SBI 00	
      		MOV B,A	
    		MVI A,00h	
    		SBI 00	
      		CMC	
  		JNC L0971	
  		STA L095F+4h	
      		POP PSW	
      		POP PSW	
      		STC	
      		DB 0xD2	;JNC ....	
      	L0971	POP B	
      		POP H	
      		MOV A,C	
      		INR A	
      		DCR A	
      		RAR	
  		JM FRoundUp+1	
      		RAL	
  		CALL FMantissaLeft	
      		DAD H	
      		MOV A,B	
      		RAL	
      		MOV B,A	
  		LDA L095F+4h	
      		RAL	
  		STA L095F+4h	
      		MOV A,C	
      		ORA D	
      		ORA E	
  		JNZ FDivLoop	
      		PUSH H	
  		LXI H,FACCUM+3	
      		DCR M	
      		POP H	
  		JNZ FDivLoop	
  		JMP Overflow	
      	FExponentAdd	MOV A,B	 
      		ORA A	
  		JZ FExponentAdd+31	
      		MOV A,L	;A=0 for add, FF for subtract.
  		LXI H,FACCUM+3	;
      		XRA M	;XOR with FAccum's exponent.
      		ADD B	;Add exponents
      		MOV B,A	;
      		RAR	;Carry (after the add) into bit 7.
      		XRA B	;XOR with old bit 7.
      		MOV A,B	;
  		JP FExponentAdd+30	;If
    		ADI 0x80	 
      		MOV M,A	 
  		JZ PopHLandReturn	 
  		CALL FUnpackMantissas	
      		MOV M,A	
      		DCX H	
      		RET	
      		ORA A	
      		POP H	;Ignore return address so we'll end
  		JM Overflow	
      	FZero	XRA A	
  		STA FACCUM+3	
      		RET	
  	FMulByTen	CALL FCopyToBCDE	
      		MOV A,B	
      		ORA A	
      		RZ	
    		ADI 02	
  		JC Overflow	
      		MOV B,A	
  		CALL FAdd+2	
  		LXI H,FACCUM+3	
      		INR M	
      		RNZ	
  		JMP Overflow	
  	FTestSign_tail	LDA FACCUM+2	
      		DB 0xFE	
      	InvSignToInt	CMA	
      	SignToInt	RAL	
      		SBB A	
      		RNZ	
      		INR A	
      		RET	
      	Sgn	RST 05	; FTestSign	
    	FCharToFloat	MVI B,88h	;ie 2^8
  		LXI D,0000h	
  		LXI H,FACCUM+3	
      		MOV C,A	
      		MOV M,B	
    		MVI B,00h	
      		INX H	
    		MVI M,80h	
      		RAL	
  		JMP FNormalise	
      	Abs	RST 05	; FTestSign	
      		RP	
  	FNegate	LXI H,FACCUM+2	
      		MOV A,M	
    		XRI 0x80	
      		MOV M,A	
      		RET	
      	FPush	XCHG	
  		LHLD FACCUM	
      		XTHL	
      		PUSH H	
  		LHLD FACCUM+2	
      		XTHL	
      		PUSH H	
      		XCHG	
      		RET	
  	FLoadFromMem	CALL FLoadBCDEfromMem	
      	FLoadFromBCDE	XCHG	
  		SHLD FACCUM	
      		MOV H,B	
      		MOV L,C	
  		SHLD FACCUM+2	
      		XCHG	
      		RET	
  	FCopyToBCDE	LXI H,FACCUM	
      	FLoadBCDEfromMem	MOV E,M	
      		INX H	
      		MOV D,M	
      		INX H	
      		MOV C,M	
      		INX H	
      		MOV B,M	
      	IncHLReturn	INX H	
      		RET	
  	FCopyToMem	LXI D,FACCUM	
    		MVI B,04h	
      	FCopyLoop	LDAX D	
      		MOV M,A	
      		INX D	
      		INX H	
      		DCR B	
  		JNZ FCopyLoop	
      		RET	
  	FUnpackMantissas	LXI H,FACCUM+2	
      		MOV A,M	;
      		RLC	;Move FACCUM's sign to bit 0.
      		STC	;Set MSB of FACCUM mantissa,
      		RAR	;FACCUM's sign is now in carry.
      		MOV M,A	;
      		CMC	;Negate FACCUM's sign.
      		RAR	;Bit 7 of A is now FACCUM's sign.
      		INX H	;Store negated FACCUM sign at FTEMP_SIGN.
      		INX H	;
      		MOV M,A	;
      		MOV A,C	;
      		RLC	;Set MSB of BCDE mantissa,
      		STC	;BCDE's sign is now in carry.
      		RAR	;
      		MOV C,A	;
      		RAR	;Bit 7 of A is now BCDE's sign
      		XRA M	;XORed with FTEMP_SIGN.
      		RET	;
      	FCompare	MOV A,B	 
      		ORA A	
  		JZ FTestSign	
  		LXI H,InvSignToInt	 
      		PUSH H	
      		RST 05	; FTestSign	
      		MOV A,C	
      		RZ	
  		LXI H,FACCUM+2	
      		XRA M	
      		MOV A,C	
      		RM	
  		CALL FIsEqual	
      		RAR	
      		XRA C	
      		RET	
      	FIsEqual	INX H	
      		MOV A,B	
      		CMP M	
      		RNZ	
      		DCX H	
      		MOV A,C	
      		CMP M	
      		RNZ	
      		DCX H	
      		MOV A,D	
      		CMP M	
      		RNZ	
      		DCX H	
      		MOV A,E	
      		SUB M	
      		RNZ	;
      		POP H	;Lose 0A5E
      		POP H	;Lose 09DE
      		RET	;Return to caller
      	FAsInteger	MOV B,A	;
      		MOV C,A	
      		MOV D,A	
      		MOV E,A	
      		ORA A	
      		RZ	
      		PUSH H	
  		CALL FCopyToBCDE	
  		CALL FUnpackMantissas	
      		XRA M	;Get sign back
      		MOV H,A	
  		CM FMantissaDec	
    		MVI A,98h	
      		SUB B	;by (24-exponent) places?
  		CALL FMantissaRtMult	;WHY?
      		MOV A,H	
      		RAL	
  		CC FMantissaInc	
    		MVI B,00h	;Needed for FNegateInt.
  		CC FNegateInt	
      		POP H	
      		RET	
      	FMantissaDec	DCX D	;DE--
      		MOV A,D	;If DE!=0xFFFF...
      		ANA E	;
      		INR A	;
      		RNZ	;... then return
      		DCR C	;C--
      		RET	;
  	Int	LXI H,FACCUM+3	;
      		MOV A,M	;
    		CPI 0x98	;
      		RNC	;
  		CALL FAsInteger	;
    		MVI M,98h	;
      		MOV A,C	;
      		RAL	;
  		JMP FNormalise	;
      	FIn	DCX H	;
  		CALL FZero	;
      		MOV B,A	;B=count of fractional digits
      		MOV D,A	;D=exponent sign
      		MOV E,A	;E=exponent
      		CMA	;C=decimal_point_done (0xFF for no, 0x00 for yes)
      		MOV C,A	;
      	FInLoop	RST 02	;RST NextChar	
  		JC ProcessDigit	
    		CPI '.'	
  		JZ L0AE4	
    		CPI 'E'	
  		JNZ ScaleResult	
      	GetExponent	RST 02	;RST NextChar	
      		DCR D	
    		CPI 0x99	;KWID_MINUS	
  		JZ NextExponentDigit	
      		INR D	
    		CPI 0x98	;KWID_PLUS	
  		JZ NextExponentDigit	
      		DCX H	
      	NextExponentDigit	RST 02	;RST NextChar	
  		JC DoExponentDigit	
      		INR D	
  		JNZ ScaleResult	
      		XRA A	
      		SUB E	
      		MOV E,A	
      		INR C	;C was 0xFF, so here it
      	L0AE4	INR C	;becomes 0x01.
  		JZ FInLoop	;If C is now zero
      	ScaleResult	PUSH H	
      		MOV A,E	
      		SUB B	
  	DecimalLoop	CP DecimalShiftUp	
  		JP DecimalLoopEnd	
      		PUSH PSW	
  		CALL FDivByTen	
      		POP PSW	
      		INR A	
  	DecimalLoopEnd	JNZ DecimalLoop	
      		POP H	
      		RET	
      	DecimalShiftUp	RZ	
      		PUSH PSW	
  		CALL FMulByTen	
      		POP PSW	
      		DCR A	
      		RET	
      	ProcessDigit	PUSH D	
      		MOV D,A	
      		MOV A,B	
      		ADC C	
      		MOV B,A	
      		PUSH B	
      		PUSH H	
      		PUSH D	
  		CALL FMulByTen	
      		POP PSW	
    		SUI '0'	
  		CALL FPush	
  		CALL FCharToFloat	
      		POP B	
      		POP D	
  		CALL FAdd+2	
      		POP H	
      		POP B	
      		POP D	
  		JMP FInLoop	
      	DoExponentDigit	MOV A,E	
      		RLC	
      		RLC	
      		ADD E	
      		RLC	
      		ADD M	
    		SUI '0'	
      		MOV E,A	
  		JMP NextExponentDigit	
      	PrintIN	PUSH H	
  		LXI H,szIn	
  		CALL PrintString	
      		POP H	
      	PrintInt	XCHG	;DE=integer
      		XRA A	;A=0 (ends up in C)
    		MVI B,98h	;B (ie exponent) = 24
  		CALL FCharToFloat+5	
  		LXI H,PrintString-1	
      		PUSH H	
  	FOut	LXI H,FBUFFER	
      		PUSH H	
      		RST 05	; FTestSign	
    		MVI M,' '	
  		JP DoZero	
    		MVI M,'-'	
      	DoZero	INX H	
    		MVI M,'0'	
  		JZ NullTerm-3	
      		PUSH H	
  		CM FNegate	
      		XRA A	
      		PUSH PSW	
  		CALL ToUnder1000000	
  	ToOver100000	LXI B,9143h	;BCDE=(float)100,000.
  		LXI D,4FF8h	;
  		CALL FCompare	;If FACCUM >= 100,000
  		JPO PrepareToPrint	;then jump to PrepareToPrint.
      		POP PSW	;A=DecExpAdj
  		CALL DecimalShiftUp+1	;FACCUM*=10; DecExpAdj--;
      		PUSH PSW	;
  		JMP ToOver100000	
  	L0B71	CALL FDivByTen	
      		POP PSW	
      		INR A	;DecExpAdj++;
      		PUSH PSW	
  		CALL ToUnder1000000	
  	PrepareToPrint	CALL FAddOneHalf	
      		INR A	
  		CALL FAsInteger	
  		CALL FLoadFromBCDE	
  		LXI B,0206h	
      		POP PSW	;A=DecExpAdj+6.
      		ADD C	;
  		JM L0B95	;If A<1 or A>6 Then goto fixme.
    		CPI 0x07	;
  		JNC L0B95	;
      		INR A	;
      		MOV B,A	;
    		MVI A,01h	;A=1, indicating scientific notation.
      	L0B95	DCR A	;
      		POP H	;HL=output buffer
      		PUSH PSW	;Preserve decimal exponent adjustment (and preserve zero flag used to indicate scientific notation wanted).
  		LXI D,DECIMAL_POWERS	
      	NextDigit	DCR B	
    		MVI M,'.'	
  		CZ IncHLReturn	;0A27 just happens to inc HL and RET.
      		PUSH B	;
      		PUSH H	;
      		PUSH D	;DE=>decimal power
  		CALL FCopyToBCDE	;Store BCDE to FACCUM.
      		POP H	;HL=>decimal power.
    		MVI B,'0'-1	;
      	DigitLoop	INR B	;
      		MOV A,E	;
      		SUB M	;
      		MOV E,A	;
      		INX H	;
      		MOV A,D	;
      		SBB M	;
      		MOV D,A	;
      		INX H	;
      		MOV A,C	;
      		SBB M	;
      		MOV C,A	;
      		DCX H	;
      		DCX H	;
  		JNC DigitLoop	;
  		CALL FAddMantissas	;
      		INX H	;???
  		CALL FLoadFromBCDE	;
      		XCHG	;
      		POP H	;HL=output buffer
      		MOV M,B	;
      		INX H	;
      		POP B	;B=decimal point place
      		DCR C	;C=digits remaining, minus one.
  		JNZ NextDigit	;
      		DCR B	;
  		JZ L0BDB	;
      	L0BCF	DCX H	;
      		MOV A,M	;
    		CPI '0'	;
  		JZ L0BCF	;
    		CPI '.'	;
  		CNZ IncHLReturn	;
      	L0BDB	POP PSW	;
  		JZ NullTerm	;
    		MVI M,'E'	;Write 'E'
      		INX H	;
    		MVI M,'+'	;Write '+' or '-'
  		JP L0BEB	;
    		MVI M,'-'	;Write '-' if it's negative, also
      		CMA	;two's complement the decimal exponent
      		INR A	;so printing it will work.
    	L0BEB	MVI B,'0'-1	;
      	ExpDigitLoop	INR B	;
    		SUI 0Ah	;
  		JNC ExpDigitLoop	;
    		ADI 3Ah	;Adding '0'+10 gives us the 2nd digit
      		INX H	;of the exponent.
      		MOV M,B	;Write first digit.
      	 	INX H	;
      		MOV M,A	;Write second digit of exponent.
      		INX H	;
      	NullTerm	MOV M,C	;Null byte terminator.
      		POP H	;
      		RET	;
  	ToUnder1000000	LXI B,9474h	;
  		LXI D,23F7h	;
  		CALL FCompare	;
      		POP H	;
  		JPO L0B71	;
      		PCHL	;
	ONE_HALF	DB 0x00,0x00,0x00,0x80	; DD 0.5	 
  	DECIMAL_POWERS	DB 0xA0,0x86,0x01	; DT 100000	 
  		DB 0x10,0x27,0x00	; DT 10000	 
  		DB 0xE8,0x03,0x00	; DT 1000	 
  		DB 0x64,0x00,0x00	; DT 100	 
  		DB 0x0A,0x00,0x00	; DT 10	 
  		DB 0x01,0x00,0x00	; DT 1	 
      	Sqr	RST 05	; FTestSign	;
  		JM FunctionCallError;
      		RZ	;
  		LXI H,FACCUM+3	;
      		MOV A,M	;
      		RAR	;
      		PUSH PSW	;
      		PUSH H	;
    		MVI A,40h	;
      		RAL	;
      		MOV M,A	;
  		LXI H,FBUFFER	;
  		CALL FCopyToMem	;
    		MVI A,04h	;
      	SqrLoop	PUSH PSW	;
  		CALL FPush	;
  		LXI H,FBUFFER	;
  		CALL FLoadBCDEfromMem	
  		CALL FDiv+2	
      		POP B	
      		POP D	
  		CALL FAdd+2	
  		LXI B,8000h	
      		MOV D,C	
      		MOV E,C	
  		CALL FMul+2	
      		POP PSW	
      		DCR A	
  		JNZ SqrLoop	
      		POP H	
      		POP PSW	
    		ADI 0xC0	
      		ADD M	
      		MOV M,A	
      		RET	
      	Rnd	RST 05	; FTestSign	
  		JM L0C7C	
  		LXI H,RND_SEED	
  		CALL FLoadFromMem	
      		RZ	
  		LXI B,9835h	
  		LXI D,447Ah	
  		CALL FMul+2	
  		LXI B,0x6828	
  		LXI D,0xB146	
  		CALL FAdd+2	
  	L0C7C	CALL FCopyToBCDE	
      		MOV A,E	
      		MOV E,C	
      		MOV C,A	
    		MVI M,80h	
      		DCX H	
      		MOV B,M	
    		MVI M,80h	
  		CALL FNormalise+3	
  		LXI H,RND_SEED	
  		JMP FCopyToMem	
	RND_SEED	DB 52C74F80h	
  	Sin	CALL FPush	;ush x
  		LXI B,8349h	;CDE=2p
  		LXI D,0FDBh	;
  		CALL FLoadFromBCDE	;hs = 2p
      		POP B	;hs = x
      		POP D	;
  		CALL FDiv+2	;=x/2p
  		CALL FPush	;
  		CALL Int	;hs = INT(u)
      		POP B	;hs = u
      		POP D	;
  		CALL FSub+2	;=u-INT(u)
  		LXI B,7F00h	;CDE=0.25
      		MOV D,C	;
      		MOV E,C	;
  		CALL FSub+2	;
      		RST 05	; FTestSign	;
      		STC	;set carry (ie no later negate)
  		JP NegateIfPositive	;
  		CALL FAddOneHalf	;
      		RST 05	;
      		ORA A	;resets carry (ie later negate)
      	NegateIfPositive	PUSH PSW	;
  		CP FNegate	;
  		LXI B,7F00h	;CDE=0.25
      		MOV D,C	;
      		MOV E,C	;
  		CALL FAdd+2	;
      		POP PSW	;
  		CNC FNegate	;
  		CALL FPush	;
  		CALL FCopyToBCDE	;
  		CALL FMul+2	; = x*x
  		CALL FPush	;ush x*x
  		LXI H,TAYLOR_SERIES	;
  		CALL FLoadFromMem	;
      		POP B	;
      		POP D	;
    		MVI A,04h	;
      	TaylorLoop	PUSH PSW	;ush #terms remaining
      		PUSH D	;ush BCDE
      		PUSH B	;
      		PUSH H	;
  		CALL FMul+2	;
      		POP H	;
  		CALL FLoadBCDEfromMem	;
      		PUSH H	;
  		CALL FAdd+2	;
      		POP H	;
      		POP B	;
      		POP D	;
      		POP PSW	;op #terms remaining into A.
      		DCR A	;ecrement #terms and loop back if not
  		JNZ TaylorLoop	;one all 4 of them.
  		JMP FMul	;
	TAYLOR_SERIES	DB 0xBA,0xD7,0x1E,0x86	;DD 39.710670	 
		DB 0x64,0x26,0x99,0x87	;DD -76.574982	 
		DB 0x58,0x34,0x23,0x87	;DD 81.602234	 
		DB 0xE0,0x5D,0xA5,0x86	;DD -41.341675	 
		DB 0xDA,0x0F,0x49,0x83	;DD 6.283185	 
	L0D17	DB 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	;   DD 6.283185
...   	
  	Init	LXI H,0x0F1A	; *** STACK_TOP RELOCATE
      		SPHL	;
  		SHLD STACK_TOP	;
    		IN 01	;
    		MVI C,0xFF	;
  		LXI D,ConfigIOcode	;
      		PUSH D	;
  		LDA 0FFFh	; *** RELOCATE
      		MOV B,A	;
    		IN 0xFF	;
      		RAR	;
  		JC L0D42-1	;
    		ANI 0Ch	;
  		JZ L0D42	;
    		MVI B,10h	;
      		MOV A,B	;
  	L0D42	STA L0D8D-1	;
    		IN 0xFF	;
      		RAL	;
      		RAL	;
    		MVI B,20h	;
  	L0D4B	LXI D,0xCA02	;
      		RC	;
      		RAL	;
      		MOV B,E	;
      		DCR E	;
      		RC	;
      		RAL	;
  		JC L0D6F	;
      		MOV B,E	;
  		LXI D,0xC280	;
      		RAL	;
      		RNC	;
      		RAL	;
    		MVI A,03h	;
  		CALL L0D8B	;
      		DCR A	;
      		ADC A	;
      		ADD A	;
      		ADD A	;
      		INR A	;
  		CALL L0D8B	;
      		STC	;
  		JMP L0D4B	;
      	L0D6F	XRA A	;
  		CALL L0D8B	;
  		CALL L0D87	;
  		CALL L0D87	;
      		MOV C,E	;
      		CMA	;
  		CALL L0D87	;
    		MVI A,04h	;
      		DCR M	;
  		CALL L0D8B	;
      		DCR M	;
      		DCR M	;
      		DCR M	;
  	L0D87	LXI H,L0D8D-1	;
      		INR M	;
    	L0D8B	OUT 00	;
      	L0D8D	RET	;
      	ConfigIOcode	MOV H,D	;
      		MOV L,B	;
  		SHLD InputChar+3	;
      		MOV A,H	;
    		ANI 0xC8	;
      		MOV H,A	;
  		SHLD TestBreakKey+3	;
      		XCHG	;
  		SHLD WaitTermReady+3	;
  		LDA L0D8D-1	;
  		STA InputChar+1	;
  		STA TestBreakKey+1	;
      		INR A	;
  		STA InputChar+8	;
      		ADD C	;
  		STA WaitTermReady+1	;
      		INR A	;
  		STA InputChar-2	;
  		LXI H,0xFFFF	;
  		SHLD CURRENT_LINE	;
  		CALL NewLine	;
  		LXI H,szMemorySize	;
  		CALL PrintString	
  		CALL InputLineWith	
      		RST 02	;RST NextChar	
      		ORA A	
  		JNZ L0DDE	
  		LXI H,UnusedMemory	
      	FindMemTopLoop:
          	INX H	
    		MVI A,37h	
      		MOV M,A	
      		CMP M	
  		JNZ DoneMemSize	
      		DCR A	
      		MOV M,A	
      		CMP M	
  		JZ FindMemTopLoop	
  		JMP DoneMemSize	
  	L0DDE:
      	LXI H,LINE_BUFFER	
  		CALL LineNumberFromStr	
      		ORA A	
  		JNZ SyntaxError	
      		XCHG	
      		DCX H	
      	DoneMemSize:
          	DCX H	
      		PUSH H	
  	GetTerminalWidth:
      	LXI H,szTerminalWidth	
  		CALL PrintString	
  		CALL InputLineWith	
        RST 02	;RST NextChar	
        ORA A	
  		JZ DoOptionalFns	
  		LXI H,LINE_BUFFER	
  		CALL LineNumberFromStr	
      		MOV A,D	
      		ORA A	
  		JNZ GetTerminalWidth	
      		MOV A,E	
    		CPI 0x10	
  		JC GetTerminalWidth	
  		STA OutChar_tail+1	
    	CalcTabBrkSize	SUI 0Eh	
  		JNC CalcTabBrkSize	
    		ADI 1Ch	
      		CMA	
      		INR A	
      		ADD E	
  		STA ToNextTabBreak+4	
  	DoOptionalFns:
      	LXI H,OPT_FN_DESCS	
      	OptionalFnsLoop:
          	RST 6	
  		LXI D,szWantSin	
      		RST 4	
  		JZ L0E32	
      		RST 6	
      		XTHL	
  		CALL PrintString	
  		CALL InputLineWith	
      		RST 02	;RST NextChar	
      		POP H	
    		CPI 'Y'	
      	L0E32	POP D	
  		JZ InitProgramBase	
    		CPI 'N'	
  		JNZ DoOptionalFns	
      		RST 6	
      		XTHL	
  		LXI D,FunctionCallError	
      		MOV M,E	
      		INX H	
      		MOV M,D	
      		POP H	
  		JMP OptionalFnsLoop	
      	InitProgramBase:
          	XCHG	
    		MVI M,00h	
      		INX H	
  		SHLD PROGRAM_BASE	
        XTHL	
  		LXI D,0F1Ah	; *** RELOCATE STACK_TOP	
        RST 4	
  		JC OutOfMemory	
        POP D	
        SPHL	
  		SHLD STACK_TOP	
        XCHG	
  		CALL CheckEnoughMem	
        MOV A,E	
        SUB L	
        MOV L,A	
        MOV A,D	
        SBB H	
        MOV H,A	
  		LXI B,0xFFF0	
        DAD B	
  		CALL NewLine	
  		CALL PrintInt	
  		LXI H,szVersionInfo	
  		CALL PrintString	
  		LXI H,PrintString	
  		SHLD Main+4	
  		CALL New+1	
  		LXI H,Main	
  		SHLD Start+2	
        PCHL	
              	
    OPT_FN_DESCS:
        DW L0D17	
        DW szWantSin	
        DW KW_INLINE_FNS+12	
        DW Sin	
        DW szWantRnd	
        DW KW_INLINE_FNS+10	
        DW Rnd	
        DW szWantSqr	
        DW KW_INLINE_FNS+8	
        DW Sqr	
              	
	szWantSin:	
        DB 57414E54205349CE00h	; DS "WANT SIN\0"
	
	szWantRnd:	
        DB 57414E5420524EC400h	; DS "WANT RND\0"
	  	
	szWantSqr:	
        DB 57414E54205351D200h	; DS "WANT SQR\0"
	        	
	szTerminalWidth:
        DB 5445524D494E414C2057494454C800h	; DS "TERMINAL WIDTH\0"
	
	szVersionInfo:
        DB 0x20,0x42,0x59,0x54,0x45,0x53,0x20,0x46,0x52,0x45,0xC5,0x0D,0x0D	; DS " BYTES FREE\r\r"
		DB 0x42,0x41,0x53,0x49,0x43,0x20,0x56,0x45,0x52,0x53,0x49,0x4F,0x4E,0x20,0x33,0x2E	; "BASIC VERSION 3."
		DB 0xB2,0x0D,0x5B,0x34,0x4B,0x20,0x56,0x45,0x52,0x53,0x49,0x4F,0x4E,0xDD,0x0D,0x00	; "2\r[4K VERSION]\r\0"

	szMemorySize:
        DB 0x4D,0x45,0x4D,0x4F,0x52,0x59,0x20,0x53,0x49,0x5A,0xC5,0x00	; DS "MEMORY SIZE\0"
	          	
    UnusedMemory	DB 00
