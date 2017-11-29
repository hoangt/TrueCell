#ifndef SECBLOCK_H
#define SECBLOCK_H

#include <vector>

#include "common.h"

namespace TC{
    class SecBlock{
        private:
            uint32_t* const data;
        public:
            SecBlock(): data(nullptr){}

            virtual void set(std::vector<uint32_t> & data) = 0;
            virtual bool access(int bitid) const = 0;
            virtual uint32_t * getDPtr() const = 0;
    };
}

#endif