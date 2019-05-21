
#ifndef OPCODES_H
#define OPCODES_H

namespace opcodes {
    enum opcodes {
        HLT = 9126,
        NOP = 0,

        MOV_REG_TO_REG = 1,
        MOV_REGADDRESS_TO_REG = 2,
        MOV_ADDRESS_TO_REG = 3,
        MOV_NUMBER_TO_REG = 4,
        MOV_REG_TO_REGADDRESS = 5,
        MOV_NUMBER_TO_REGADDRESS = 6,
        MOV_REG_TO_ADDRESS = 7,
        MOV_NUMBER_TO_ADDRESS = 8,
        
        DT = 10,
        DW = 11,
        DTW = 12,

        CMP_REG_WITH_REG = 20,
        CMP_REGADDRESS_WITH_REG = 21,
        CMP_ADDRESS_WITH_REG = 22,
        CMP_NUMBER_WITH_REG = 23,
        
        JMP_REGADDRESS = 30,
        JMP_ADDRESS = 31,
        
        JC_REGADDRESS = 32,
        JC_ADDRESS = 33,
        JNC_REGADDRESS = 34,
        JNC_ADDRESS = 35,
        JUC_REGADDRESS = 36,
        JUC_ADDRESS = 37,

        JZ_REGADDRESS = 38,
        JZ_ADDRESS = 39,
        JNZ_REGADDRESS = 40,
        JNZ_ADDRESS = 41,
        JUZ_REGADDRESS = 42,
        JUZ_ADDRESS = 43,
        
        PUSH_REG = 50,
        PUSH_REGADDRESS = 51,
        PUSH_ADDRESS = 52,
        PUSH_NUMBER = 53,
        POP_REG = 54,
        CALL_REGADDRESS = 55,
        CALL_ADDRESS = 56,
        RET = 57,
        
        INC_REG = 60,
        DEC_REG = 61,
        ADD_REG_TO_REG = 70,
        ADD_REGADDRESS_TO_REG = 71,
        ADD_ADDRESS_TO_REG = 72,
        ADD_NUMBER_TO_REG = 73,

        SUB_REG_FROM_REG = 75,
        SUB_REGADDRESS_FROM_REG = 76,
        SUB_ADDRESS_FROM_REG = 77,
        SUB_NUMBER_FROM_REG = 78,

        MUL_REG = 80,
        MUL_REGADDRESS = 81,
        MUL_ADDRESS = 82,
        MUL_NUMBER = 83,

        DIV_REG = 85,
        DIV_REGADDRESS = 86,
        DIV_ADDRESS = 87,
        DIV_NUMBER = 88,
        
        AND_REG_WITH_REG = 90,
        AND_REGADDRESS_WITH_REG = 91,
        AND_ADDRESS_WITH_REG = 92,
        AND_NUMBER_WITH_REG = 93,
        
        OR_REG_WITH_REG = 95,
        OR_REGADDRESS_WITH_REG = 96,
        OR_ADDRESS_WITH_REG = 97,
        OR_NUMBER_WITH_REG = 98,

        XOR_REG_WITH_REG = 100,
        XOR_REGADDRESS_WITH_REG = 101,
        XOR_ADDRESS_WITH_REG = 102,
        XOR_NUMBER_WITH_REG = 103,
        
        NOT_REG = 105,
        NOTT_REG = 106,
        NOTF_REG = 107,
        
        SHL_REG_WITH_REG = 110,
        SHL_REGADDRESS_WITH_REG = 111,
        SHL_ADDRESS_WITH_REG = 112,
        SHL_NUMBER_WITH_REG = 113,

        SHR_REG_WITH_REG = 115,
        SHR_REGADDRESS_WITH_REG = 116,
        SHR_ADDRESS_WITH_REG = 117,
        SHR_NUMBER_WITH_REG = 118
    };
}

#endif