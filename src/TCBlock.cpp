#include "TCBlock.h"

namespace TC{
    TCBlock::TCBlock(uint32_t* const TCs) : data(TCs){}
    void TCBlock::set(std::vector<uint32_t> & data){
        assert(data.size() * 4 <= BLOCK_SIZE);
        for (uint32_t i = 0; i < BLOCK_SIZE/4; i++)
            this->data[i] = (i < data.size()) ? data[i] : 0;
    }

    bool TCBlock::access(int bitid) const{
        return (data[bitid >> 5] >> (bitid & ((1 << 5) - 1))) & 1;
    }
    uint32_t * TCBlock::getDPtr() const{
        return this->data;
    }
}
