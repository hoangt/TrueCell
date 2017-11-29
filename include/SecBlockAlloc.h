#ifndef SECBLOCKALLOC_H
#define SECBLOCKALLOC_H

#include <vector>

#include "common.h"
#include "SecBlock.h"

namespace TC{
    class SecBlockAlloc{
        public:
            virtual SecBlock* AllocBlock(std::vector <uint32_t> & data) = 0;
            virtual void FreeBlock(const SecBlock* block) = 0;
    };

    SecBlockAlloc *AllocBlockAllocator(const char *typ);
}

#endif