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
#include <Utils/utils.h>

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
                throw std::string("Memory access violation at " + dechept(address.to_int()));
            }

            this->lastAccess = address;
            return this->data[address.to_int()];
        }

        void store(Tryte address, Tryte value) {
            if (address.to_int() < -1*(this->size-1)/2 || address.to_int() > (this->size-1)/2) {
                throw std::string("Memory access violation at " + dechept(address.to_int()));
            }

            this->lastAccess = address;
            this->data[address.to_int()] = value;
        }

        void reset() {
            this->lastAccess = 0;
            for (int i = 0; i <= this->size-1; i++) {
                this->data[i - this->size/2] = Tryte(0);
            }
        }

        std::map<int, Tryte>getData() {
            return this->data;
        }

        int getSize() {
            return this->size;
        }

};

#endif