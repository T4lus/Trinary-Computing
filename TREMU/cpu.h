/*
**
** Made by T4lus
** Trinary CPU
** 
*/

#ifndef CPU_H
#define CPU_H

#include <algorithm>
#include <cmath>
#include <string>
#include <map>

#include <Trinary/trit.h>
#include <Trinary/tryte.h>
#include <Utils/utils.h>

#include "memory.h"
#include "opcodes.h"

#define MAX_SP 231
#define MIN_SP 0

class CPU {

    private:
        Tryte sp;
        Tryte ip;
        std::vector<Tryte> gpr;
        Trit zero;
        Trit carry;
        Trit fault;
        Memory *memory;

        Tryte checkGPR(Tryte reg) {
            if (reg.to_int() < 0 || reg.to_int() >= this->gpr.size()) {
                throw std::string("Invalid register: " + reg.to_int());
            } else {
                return reg;
            }
        }

        Tryte checkGPR_SP (Tryte reg) {
            if (reg.to_int() < 0 || reg.to_int() >= 1 + this->gpr.size()) {
                throw std::string("Invalid register: " + reg.to_int());
            } else {
                return reg;
            }
        };

        void setGPR_SP(Tryte reg, Tryte value) {
            if(reg.to_int() >= 0 && reg.to_int() < this->gpr.size()) {
                this->gpr[reg.to_int()] = value;
            } else if(reg.to_int() == this->gpr.size()) {
                this->sp = value;

                // Not likely to happen, since we always get here after checkOpertion().
                if (this->sp < MIN_SP) {
                    throw std::string("Stack overflow");
                } else if (this->sp > MAX_SP) {
                    throw std::string("Stack underflow");
                }
            } else {
                throw std::string("Invalid register: " + reg.to_int());
            }
        }

        Tryte getGPR_SP (Tryte reg) {
            if(reg.to_int() >= 0 && reg.to_int() < this->gpr.size()) {
                return this->gpr[reg.to_int()];
            } else if(reg.to_int() == this->gpr.size()) {
                return this->sp;
            } else {
                throw std::string("Invalid register: " + reg.to_int());
            }
        }

        Tryte indirectRegisterAddress(Tryte value) {
            Tryte reg = value % 27;
            
            Tryte base;
            if (reg.to_int() < this->gpr.size()) {
                base = this->gpr[reg.to_int()];
            } else {
                base = this->sp;
            }
            
            Tryte offset = floor(value / 27);
            
            return base + offset;
        };

        Tryte checkOperation(Tryte value) {
            this->zero = 'U';
            this->carry = 'U';

            if (value > 9841) {
                this->carry = 'T';
                value = value % 9841;
            } else if (value == 0) {
                this->zero = 'T';
            } else if (value < -9841) {
                this->carry = 'T';
                value = 9841 - (-value) % 9841;
            }
            return value;
        };

        void jump(Tryte newIP) {

            if (newIP < -1*(this->memory->getSize()-1)/2 || newIP > (this->memory->getSize()-1)/2) {
                throw "IP outside memory";
            } else {
                this->ip = newIP;
            }
        }

        void push (Tryte value) {
            this->memory->store(this->sp--, value);
            if (this->sp < MIN_SP) {
                throw std::string("Stack overflow");
            }
        };

        Tryte pop() {
            Tryte value = this->memory->load(this->sp++);
            if (this->sp > MAX_SP) {
                throw std::string("Stack underflow");
            }

            return value;
        }

        Tryte division(Tryte divisor) {
            if (divisor == 0) {
                throw std::string("Division by 0");
            }

            return floor(this->gpr[0] / divisor);
        }


    public:
        CPU(Memory *memory) {
            this->memory = memory;
            this->reset();
        }

        void reset() {
            this->ip = Tryte(heptdec("DDD"));
            this->sp = MAX_SP;
            this->gpr = {
                heptdec("DDD"),
                heptdec("DDD"),
                heptdec("DDD"),
                heptdec("DDD")
            };
            this->carry = 'U';
            this->zero = 'U';
            this->fault = 'U';
        }

        void step() {

             if (this->ip < -1*(this->memory->getSize()-1)/2 || this->ip > (this->memory->getSize()-1)/2) {
                throw std::string("Instruction pointer is outside of memory");
            }

            Tryte regTo, regFrom, memFrom, memTo, number;
            Tryte instr = this->memory->load(this->ip);

            switch (instr.to_int()) {
                case opcodes::HALT:
                    return;
                    break;
                case opcodes::NOOP:
                    this->ip++;
                    break;
                case opcodes::LOAD_REG_TO_REG:
                    regTo = checkGPR_SP(memory->load(++this->ip));
                    regFrom = checkGPR_SP(memory->load(++this->ip));
                    setGPR_SP(regTo, getGPR_SP(regFrom));
                    this->ip++;
                    break;
                case opcodes::LOAD_ADDRESS_TO_REG:
                    regTo = checkGPR_SP(memory->load(++this->ip));
                    memFrom = memory->load(++this->ip);
                    setGPR_SP(regTo, memory->load(memFrom));
                    this->ip++;
                    break;
                case opcodes::LOAD_REGADDRESS_TO_REG:
                    regTo = checkGPR_SP(memory->load(++this->ip));
                    regFrom = memory->load(++this->ip);
                    setGPR_SP(regTo,memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case opcodes::LOAD_REG_TO_ADDRESS:
                    memTo = memory->load(++this->ip);
                    regFrom = checkGPR_SP(memory->load(++this->ip));
                    memory->store(memTo, getGPR_SP(regFrom));
                    this->ip++;
                    break;
                case opcodes::LOAD_REG_TO_REGADDRESS:
                    regTo = memory->load(++this->ip);
                    regFrom = checkGPR_SP(memory->load(++this->ip));
                    memory->store(indirectRegisterAddress(regTo), getGPR_SP(regFrom));
                    this->ip++;
                    break;
                case opcodes::LOAD_NUMBER_TO_REG:
                    regTo = checkGPR_SP(memory->load(++this->ip));
                    number = memory->load(++this->ip);
                    setGPR_SP(regTo, number);
                    this->ip++;
                    break;
                case opcodes::LOAD_NUMBER_TO_ADDRESS:
                    memTo = memory->load(++this->ip);
                    number = memory->load(++this->ip);
                    memory->store(memTo, number);
                    this->ip++;
                    break;
                case opcodes::LOAD_NUMBER_TO_REGADDRESS:
                    regTo = memory->load(++this->ip);
                    number = memory->load(++this->ip);
                    memory->store(indirectRegisterAddress(regTo), number);
                    this->ip++;
                    break;

                case opcodes::CMP_REG_WITH_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = checkGPR_SP(this->memory->load(++this->ip));
                    checkOperation(getGPR_SP(regTo) - getGPR_SP(regFrom));
                    this->ip++;
                    break;
                case opcodes::CMP_REGADDRESS_WITH_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    checkOperation(getGPR_SP(regTo) - this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case opcodes::CMP_ADDRESS_WITH_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    checkOperation(getGPR_SP(regTo) - this->memory->load(memFrom));
                    this->ip++;
                    break;
                case opcodes::CMP_NUMBER_WITH_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    checkOperation(getGPR_SP(regTo) - number);
                    this->ip++;
                    break;

                

                case opcodes::JMP_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    this->jump(this->gpr[regTo.to_int()]);
                    break;
                case opcodes::JMP_ADDRESS:
                    number = this->memory->load(++this->ip);
                    this->jump(number);
                    break;
                case  opcodes::JC_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (this->carry) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JC_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (this->carry) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JNC_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (!this->carry) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JNC_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (!this->carry) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JUC_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (!this->carry) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JUC_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (!this->carry) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JZ_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (this->zero == Trit('T')) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JZ_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (this->zero == Trit('T')) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JNZ_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (this->zero != Trit('T')) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JNZ_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (this->zero != Trit('T')) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JUZ_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    if (!this->zero) {
                        jump(this->gpr[regTo.to_int()]);
                    } else {
                        this->ip++;
                    }
                    break;
                case  opcodes::JUZ_ADDRESS:
                    number = this->memory->load(++this->ip);
                    if (!this->zero) {
                        jump(number);
                    } else {
                        this->ip++;
                    }
                    break;

                case  opcodes::PUSH_REG:
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    push(this->gpr[regFrom.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::PUSH_REGADDRESS:
                    regFrom = this->memory->load(++this->ip);
                    push(this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::PUSH_ADDRESS:
                    memFrom = this->memory->load(++this->ip);
                    push(this->memory->load(memFrom));
                    this->ip++;
                    break;
                case  opcodes::PUSH_NUMBER:
                    number = this->memory->load(++this->ip);
                    push(number);
                    this->ip++;
                    break;
                case  opcodes::POP_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = pop();
                    this->ip++;
                    break;
                case  opcodes::CALL_REGADDRESS:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    push(this->ip+1);
                    jump(this->gpr[regTo.to_int()]);
                    break;
                case  opcodes::CALL_ADDRESS:
                    number = this->memory->load(++this->ip);
                    push(this->ip+1);
                    jump(number);
                    break;
                case  opcodes::RET:
                    jump(pop());
                    break;

                case  opcodes::INC_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) + 1));
                    this->ip++;
                    break;
                case  opcodes::DEC_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) - 1));
                    this->ip++;
                    break;
                case  opcodes::ADD_REG_TO_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = checkGPR_SP(this->memory->load(++this->ip));
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) + getGPR_SP(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::ADD_REGADDRESS_TO_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) + this->memory->load(indirectRegisterAddress(regFrom))));
                    this->ip++;
                    break;
                case  opcodes::ADD_ADDRESS_TO_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) + this->memory->load(memFrom)));
                    this->ip++;
                    break;
                case  opcodes::ADD_NUMBER_TO_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) + number));
                    this->ip++;
                    break;
                case  opcodes::SUB_REG_FROM_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = checkGPR_SP(this->memory->load(++this->ip));
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) - this->gpr[regFrom.to_int()]));
                    this->ip++;
                    break;
                case  opcodes::SUB_REGADDRESS_FROM_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) - this->memory->load(indirectRegisterAddress(regFrom))));
                    this->ip++;
                    break;
                case  opcodes::SUB_ADDRESS_FROM_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) - this->memory->load(memFrom)));
                    this->ip++;
                    break;
                case  opcodes::SUB_NUMBER_FROM_REG:
                    regTo = checkGPR_SP(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    setGPR_SP(regTo,checkOperation(getGPR_SP(regTo) - number));
                    this->ip++;
                    break;
                
                case  opcodes::MUL_REG: // A = A * REG
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[0] = checkOperation(this->gpr[0] * this->gpr[regFrom.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::MUL_REGADDRESS: // A = A * [REG]
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(this->gpr[0] * this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::MUL_ADDRESS: // A = A * [NUMBER]
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(this->gpr[0] * this->memory->load(memFrom));
                    this->ip++;
                    break;
                case  opcodes::MUL_NUMBER: // A = A * NUMBER
                    number = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(this->gpr[0] * number);
                    this->ip++;
                    break;
                case  opcodes::DIV_REG: // A = A / REG
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[0] = checkOperation(division(this->gpr[regFrom.to_int()]));
                    this->ip++;
                    break;
                case  opcodes::DIV_REGADDRESS: // A = A / [REG]
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(division(this->memory->load(indirectRegisterAddress(regFrom))));
                    this->ip++;
                    break;
                case  opcodes::DIV_ADDRESS: // A = A / [NUMBER]
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(division(this->memory->load(memFrom)));
                    this->ip++;
                    break;
                case  opcodes::DIV_NUMBER: // A = A / NUMBER
                    number = this->memory->load(++this->ip);
                    this->gpr[0] = checkOperation(division(number));
                    this->ip++;
                    break;

                case  opcodes::AND_REG_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] & this->gpr[regFrom.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::AND_REGADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] & this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::AND_ADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] & this->memory->load(memFrom));
                    this->ip++;
                    break;
                case  opcodes::AND_NUMBER_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] & number);
                    this->ip++;
                    break;
                case  opcodes::OR_REG_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] | this->gpr[regFrom.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::OR_REGADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] | this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::OR_ADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] | this->memory->load(memFrom));
                    this->ip++;
                    break;
                case  opcodes::OR_NUMBER_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] | number);
                    this->ip++;
                    break;
                case  opcodes::XOR_REG_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] ^ this->gpr[regFrom.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::XOR_REGADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] ^ this->memory->load(indirectRegisterAddress(regFrom)));
                    this->ip++;
                    break;
                case  opcodes::XOR_ADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] ^ this->memory->load(memFrom));
                    this->ip++;
                    break;
                case  opcodes::XOR_NUMBER_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(this->gpr[regTo.to_int()] ^ number);
                    this->ip++;
                    break;

                case  opcodes::NOT_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(~this->gpr[regTo.to_int()]);
                    this->ip++;
                    break;
                case  opcodes::NOTT_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::NOTT(this->gpr[regTo.to_int()]));
                    this->ip++;
                    break;
                case  opcodes::NOTF_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::NOTF(this->gpr[regTo.to_int()]));
                    this->ip++;
                    break;
                
                case  opcodes::SHL_REG_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHL(this->gpr[regTo.to_int()], this->gpr[regFrom.to_int()].to_int()));
                    this->ip++;
                    break;
                case  opcodes::SHL_REGADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHL(this->gpr[regTo.to_int()], this->memory->load(indirectRegisterAddress(regFrom)).to_int()));
                    this->ip++;
                    break;
                case  opcodes::SHL_ADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHL(this->gpr[regTo.to_int()], this->memory->load(memFrom).to_int()));
                    this->ip++;
                    break;
                case  opcodes::SHL_NUMBER_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHL(this->gpr[regTo.to_int()], number.to_int()));
                    this->ip++;
                    break;
                
                case  opcodes::SHR_REG_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = checkGPR(this->memory->load(++this->ip));
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHR(this->gpr[regTo.to_int()], this->gpr[regFrom.to_int()].to_int()));
                    this->ip++;
                    break;
                case  opcodes::SHR_REGADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    regFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHR(this->gpr[regTo.to_int()], this->memory->load(indirectRegisterAddress(regFrom)).to_int()));
                    this->ip++;
                    break;
                case  opcodes::SHR_ADDRESS_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    memFrom = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation(Tryte::SHR(this->gpr[regTo.to_int()], this->memory->load(memFrom).to_int() ));
                    this->ip++;
                    break;
                case  opcodes::SHR_NUMBER_WITH_REG:
                    regTo = checkGPR(this->memory->load(++this->ip));
                    number = this->memory->load(++this->ip);
                    this->gpr[regTo.to_int()] = checkOperation( Tryte::SHR(this->gpr[regTo.to_int()], number.to_int()) );
                    this->ip++;
                    break;

                default:
                    break;
            }

        }

        std::vector<Tryte> getGPR() {
            return this->gpr;
        }

        Tryte getIP() {
            return this->ip;
        }

        Tryte getSP() {
            return this->sp;
        }

        Trit getZero() {
            return this->zero;
        }
        Trit getCarry() {
            return this->carry;
        }
        Trit getFault() {
            return this->fault;
        }

};

#endif