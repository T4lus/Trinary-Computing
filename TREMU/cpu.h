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
        bool zero;
        bool carry;
        bool fault;
        Memory *memory;

        int checkGPR(int reg) {
            if (reg < 0 || reg >= this->gpr.size()) {
                throw std::string("Invalid register: " + reg);
            } else {
                return reg;
            }
        }

        int checkGPR_SP (int reg) {
            if (reg < 0 || reg >= 1 + this->gpr.size()) {
                throw std::string("Invalid register: " + reg);
            } else {
                return reg;
            }
        };

        void setGPR_SP(int reg, Tryte value) {
            if(reg >= 0 && reg < this->gpr.size()) {
                this->gpr[reg] = value;
            } else if(reg == this->gpr.size()) {
                this->sp = value;

                // Not likely to happen, since we always get here after checkOpertion().
                if (this->sp < MIN_SP) {
                    throw "Stack overflow";
                } else if (this->sp > MAX_SP) {
                    throw "Stack underflow";
                }
            } else {
                throw std::string("Invalid register: " + reg);
            }
        }

        Tryte getGPR_SP (int reg) {
            if(reg >= 0 && reg < this->gpr.size()) {
                return this->gpr[reg];
            } else if(reg == this->gpr.size()) {
                return this->sp;
            } else {
                throw std::string("Invalid register: " + reg);
            }
        }

        void jump(Tryte newIP) {

            if (newIP < -1*(this->memory->getSize()-1)/2 || newIP > (this->memory->getSize()-1)/2) {
                throw "IP outside memory";
            } else {
                this->ip = newIP;
            }
        }


    public:
        CPU(Memory *memory) {
            this->memory = memory;
            this->reset();
        }

        void reset() {
            this->ip = Tryte(heptdec("C00"));
            this->sp = MAX_SP;
            this->gpr.resize(4, Tryte(heptdec("DDD")));
            this->carry = false;
            this->zero = false;
            this->fault = false;
        }

        void step() {
            Tryte instr = this->memory->load(this->ip);

            switch (instr.to_int())
            {
            case opcodes::HALT:
                return;
                break;
            case opcodes::NOOP:
                this->ip++;
                break;
            // case opcodes::LOAD_REG_TO_REG:
            //     Tryte regTo = checkGPR_SP(memory->load(++this->ip));
            //     Tryte regFrom = checkGPR_SP(memory->load(++this->ip));
            //     setGPR_SP(regTo,getGPR_SP(regFrom));
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_ADDRESS_TO_REG:
            //     Tryte regTo = checkGPR_SP(memory->load(++this->ip));
            //     Tryte memFrom = memory->load(++this->ip);
            //     setGPR_SP(regTo,memory->load(memFrom));
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_REGADDRESS_TO_REG:
            //     Tryte regTo = checkGPR_SP(memory->load(++this->ip));
            //     Tryte regFrom = memory->load(++this->ip);
            //     setGPR_SP(regTo,memory->load(indirectRegisterAddress(regFrom)));
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_REG_TO_ADDRESS:
            //     Tryte memTo = memory->load(++this->ip);
            //     Tryte regFrom = checkGPR_SP(memory->load(++this->ip));
            //     memory->store(memTo, getGPR_SP(regFrom));
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_REG_TO_REGADDRESS:
            //     Tryte regTo = memory->load(++this->ip);
            //     Tryte regFrom = checkGPR_SP(memory->load(++this->ip));
            //     memory->store(indirectRegisterAddress(regTo), getGPR_SP(regFrom));
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_NUMBER_TO_REG:
            //     Tryte regTo = checkGPR_SP(memory->load(++this->ip));
            //     Tryte number = memory->load(++this->ip);
            //     setGPR_SP(regTo,number);
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_NUMBER_TO_ADDRESS:
            //     Tryte memTo = memory->load(++this->ip);
            //     Tryte number = memory->load(++this->ip);
            //     memory->store(memTo, number);
            //     this->ip++;
            //     break;
            // case opcodes::LOAD_NUMBER_TO_REGADDRESS:
            //     Tryte regTo = memory->load(++this->ip);
            //     Tryte number = memory->load(++this->ip);
            //     memory->store(indirectRegisterAddress(regTo), number);
            //     this->ip++;
            //     break;

            case opcodes::JMP_REGADDRESS: {
                Tryte regTo = checkGPR(this->memory->load(++this->ip));
                this->jump(this->gpr[regTo.to_int()]);
                break;
            }
            case opcodes::JMP_ADDRESS: {
                Tryte number = this->memory->load(++this->ip);
                this->jump(number);
                break;
            }
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

};

#endif