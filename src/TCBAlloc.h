#ifndef TCBALLOC_H
#define TCBALLOC_H

#include <unordered_set>

#include "common.h"
#include "SecBlockAlloc.h"


namespace TC{
    class TCBAlloc : public SecBlockAlloc{
        private:
            uint32_t* TCBlocks[NUM_BLOCK];
            std::unordered_set<uint32_t *> FreeBlocks, UsedBlocks;

        public:
            TCBAlloc();
            ~TCBAlloc();

            SecBlock* AllocBlock(std::vector <uint32_t> & data);
            void FreeBlock(const SecBlock* block);
    };
}

#endif