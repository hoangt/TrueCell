#include "HMBlock.h"

namespace TC{

    HMBlock::HMBlock(uint32_t * const data) :
        data(data), parity(data+(BLOCK_SIZE/4)){}

    void HMBlock::verify(int bitid) const{
        int groupid = bitid >> 7;
        assert((data[(groupid << 2) + 1] ^ data[(groupid << 2) + 2] ^
            data[(groupid << 2) + 3]) == parity[groupid*3 + 0]);
        assert((data[(groupid << 2) + 0] ^ data[(groupid << 2) + 2] ^
            data[(groupid << 2) + 3]) == parity[groupid*3 + 1]);
        assert((data[(groupid << 2) + 0] ^ data[(groupid << 2) + 1] ^
            data[(groupid << 2) + 3]) == parity[groupid*3 + 2]);
    }

    void HMBlock::set(std::vector<uint32_t> & data){
        assert(data.size() * 4 <= BLOCK_SIZE);
        for (uint32_t i = 0; i < BLOCK_SIZE/4; i++)
            this->data[i] = (i < data.size()) ? data[i] : 0;
        for (int groupid = 0; groupid < (BLOCK_SIZE >> 4); groupid++){
            parity[groupid*3 + 0] = data[(groupid << 2) + 1] ^
                data[(groupid << 2) + 2] ^ data[(groupid << 2) + 3];
            parity[groupid*3 + 1] = data[(groupid << 2) + 0] ^
                data[(groupid << 2) + 2] ^ data[(groupid << 2) + 3];
            parity[groupid*3 + 2] = data[(groupid << 2) + 0] ^
                data[(groupid << 2) + 1] ^ data[(groupid << 2) + 3];
        }
    }

    bool HMBlock::access(int bitid) const{
        verify(bitid);
        return (data[bitid >> 5] >> (bitid & ((1 << 5) - 1))) & 1;
    }
    uint32_t * HMBlock::getDPtr() const{
        return data;
    }

}
