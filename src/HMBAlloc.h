#ifndef HMBALLOC_H
#define HMBALLOC_H

#include "common.h"
#include "SecBlockAlloc.h"

#include <unordered_set>

namespace TC{
    class HMBAlloc : public SecBlockAlloc{
        private:
            uint32_t* HMBlocks[NUM_BLOCK];
            std::unordered_set<uint32_t *> FreeBlocks, UsedBlocks;

        public:
            HMBAlloc();
            ~HMBAlloc();

            SecBlock* AllocBlock(std::vector <uint32_t> & data);
            void FreeBlock(const SecBlock* block);
    };
}

#endif