#ifndef TCBLOCK_H
#define TCBLOCK_H

#include "common.h"
#include "SecBlock.h"

namespace TC{
    class TCBlock: public SecBlock{
        private:
            uint32_t* const data;
        public:
            TCBlock(uint32_t* const TCs);

            void set(std::vector<uint32_t> & data);
            bool access(int bitid) const;
            uint32_t * getDPtr() const;

    };
}

#endif