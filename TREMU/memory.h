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
#include <vector>

#include <tryte.h>

class Memory {
    
    private:
        std::vector<Tryte> data;
        Tryte lastAccess;

    public:
        Memory() {
            this->reset();
        }

        Tryte load(Tryte address){
            if (address.to_int() < -1*(TRYTE_MAX - 27) || address.to_int() > (TRYTE_MAX - 27)) {
                throw "Memory access violation at " + address.str();
            }

        }

        void store(Tryte address, Tryte value) {
            if (address.to_int() < -1*(TRYTE_MAX - 27) || address.to_int() > (TRYTE_MAX - 27)) {
                throw "Memory access violation at " + address.str();
            }

        }

        void reset() {
            this->lastAccess = 0;
            this->data.resize((TRYTE_MAX*2), 0);
        }

};

#endif