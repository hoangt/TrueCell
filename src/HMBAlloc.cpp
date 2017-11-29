#include "HMBAlloc.h"
#include "HMBlock.h"

namespace TC{
    HMBAlloc::HMBAlloc(){
        FreeBlocks.clear();
        UsedBlocks.clear();

        for(int i = 0; i < NUM_BLOCK; i++){
            HMBlocks[i] = new uint32_t[(BLOCK_SIZE >> 4) * 7];
            FreeBlocks.insert(HMBlocks[i]);
        }
    }

    SecBlock *HMBAlloc::AllocBlock(std::vector <uint32_t> & data){
        assert(FreeBlocks.size());
        std::unordered_set<uint32_t*>::iterator pblock = FreeBlocks.begin();
        SecBlock *newBlock = new HMBlock(*pblock);
        newBlock->set(data);
        FreeBlocks.erase(newBlock->getDPtr());
        UsedBlocks.insert(newBlock->getDPtr());
        return newBlock;
    }

    void HMBAlloc::FreeBlock(const SecBlock * block){
        assert(!FreeBlocks.count(block->getDPtr()));
        assert(UsedBlocks.count(block->getDPtr()));
        UsedBlocks.erase(block->getDPtr());
        FreeBlocks.insert(block->getDPtr());
    }
}