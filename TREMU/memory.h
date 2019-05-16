/*
**
** Made by T4lus
** Trinary Memory
** 
*/


#ifndef MEMORY_H
#define MEMORY_H

#include <algorithm>
#include <cmath>
#include <string>
#include <map>

#include <Trinary/tryte.h>

class Memory {
    
    private:
        int size;
        std::map<int, Tryte> data;
        Tryte lastAccess;

    public:
        Memory(int size) {
            this->size = size;
            this->reset();
        }

        Tryte load(Tryte address){
            if (address.to_int() < -1*(this->size-1)/2 || address.to_int() > (this->size-1)/2) {
                throw "Memory access violation at " + address.str();
            }

            this->lastAccess = address;
            return this->data[address.to_int()];
        }

        void store(Tryte address, Tryte value) {
            if (address.to_int() < -1*(this->size-1)/2 || address.to_int() > (this->size-1)/2) {
                throw "Memory access violation at " + address.str();
            }

            this->lastAccess = address;
            this->data[address.to_int()] = value;
        }

        void reset() {
            this->lastAccess = 0;
            for (int i = 0; i <= this->size; i++) {
                this->data[i - this->size/2] = Tryte(0);
            }
        }

};

#endif