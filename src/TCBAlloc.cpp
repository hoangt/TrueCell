#include "TCBAlloc.h"
#include "TCBlock.h"

namespace TC{
    TCBAlloc::TCBAlloc(){
        FreeBlocks.clear();
        UsedBlocks.clear();

        for(int i = 0; i < NUM_BLOCK; i++){
            TCBlocks[i] = new uint32_t[BLOCK_SIZE >> 2];
            FreeBlocks.insert(TCBlocks[i]);
        }
    }

    SecBlock *TCBAlloc::AllocBlock(std::vector <uint32_t> & data){
        assert(FreeBlocks.size());
        std::unordered_set<uint32_t*>::iterator pblock = FreeBlocks.begin();
        SecBlock *newBlock = new TCBlock(*pblock);
        newBlock->set(data);
        FreeBlocks.erase(newBlock->getDPtr());
        UsedBlocks.insert(newBlock->getDPtr());
        return newBlock;
    }

    void TCBAlloc::FreeBlock(const SecBlock * block){
        assert(!FreeBlocks.count(block->getDPtr()));
        assert(UsedBlocks.count(block->getDPtr()));
        UsedBlocks.erase(block->getDPtr());
        FreeBlocks.insert(block->getDPtr());
    }
}
