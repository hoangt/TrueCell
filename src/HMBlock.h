#ifndef HMBLOCK_H
#define HMBLOCK_H

#include "common.h"
#include "SecBlock.h"

namespace TC{
    class HMBlock : public SecBlock{
        private:
            uint32_t* const data;
            uint32_t* const parity;
            void verify(int bitid) const;

        public:
            HMBlock(uint32_t* const data);

            void set(std::vector<uint32_t> & data);
            bool access(int bitid) const;
            uint32_t * getDPtr() const;
    };
}

#endif