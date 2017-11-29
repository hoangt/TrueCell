
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

#include <unistd.h>

#include "SecBlock.h"
#include "SecBlockAlloc.h"

#include <chrono>
class TimeMeasure{
    private:
        std::chrono::steady_clock::time_point tp;

    public:
        TimeMeasure(){
            reset();
        }


        void reset(){
            tp = std::chrono::steady_clock::now();
        }

        uint32_t report(){
            auto intv =
                std::chrono::duration_cast<std::chrono::nanoseconds>
                    (std::chrono::steady_clock::now() - tp);
            reset();
            return (uint32_t) intv.count();
        }
};

uint32_t rand_access(uint32_t times){
    uint32_t sum = 0;

    return sum;
}


void exitUsage(const char *progName){
    std::cout << "Usage: " << progName << " AllocTimes AccessTimes";
    exit(-1);
}

int strtoint(const char *str){
    for (const char *p = str; *p; p++)
        if (*p <'0' || *p > '9') return -1;
    return atoi(str);
}


void TestAlloc(const char* desp, uint32_t times, TC::SecBlockAlloc* alloc){
    std::vector<uint32_t> data;
    for (uint32_t i = 0; i < (BLOCK_SIZE >> 2); i++)
        data.push_back(rand());

    TimeMeasure tm;
    tm.reset();
    for (uint32_t i = 0; i < times; i++){
        TC::SecBlock* newBlock = alloc->AllocBlock(data);
        alloc->FreeBlock(newBlock);
    }
    uint32_t nanoSec = tm.report();
    std::cout << desp << ": \t" << nanoSec << std::endl;
}

void TestAccess(const char* desp, uint32_t times, TC::SecBlockAlloc *alloc){
    uint32_t numBlock = (NUM_BLOCK + rand()%NUM_BLOCK) / 2;
    TC::SecBlock* blocks[numBlock];
    std::vector<uint32_t> data[numBlock];

    for (uint32_t i = 0; i < numBlock; i++){
        data[i].clear();
        for (uint32_t j = 0; j < (BLOCK_SIZE >> 2); j++){
            data[i].push_back(rand());
        }
        blocks[i] = alloc->AllocBlock(data[i]);
    }
    TimeMeasure tm;
    tm.reset();
    for (uint32_t i = 0; i < times; i++){
        uint32_t id = rand() % numBlock;
        uint32_t bitid = rand() % (BLOCK_SIZE * 8);
        assert(blocks[id]->access(bitid) ==
            ((data[id][bitid >> 5] >> (bitid & ((1 << 5) - 1))) & 1));

    }
    uint32_t nanoSec = tm.report();
    std::cout << desp << ":\t" << nanoSec << std::endl;

    for (uint32_t i = 0; i < numBlock; i++)
        alloc->FreeBlock(blocks[i]);
}

int main(int argc, char *argv[]){
    int AllocTimes = 1 << 20;
    int AccessTimes = 1 << 20;

    if (argc > 1){
        if (argc > 3)
            exitUsage(argv[0]);
        if (argc >= 2){
            if (-1 == (AllocTimes = strtoint(argv[1])))
                exitUsage(argv[0]);
        }
        if (argc == 3){
            if (-1 == (AccessTimes = strtoint(argv[2])))
                exitUsage(argv[0]);
        }
    }

    TimeMeasure tm;
    usleep(10);
    uint32_t nanoSec = tm.report();
    std::cout << "10us = " << nanoSec << "ns" << std::endl;


    TC::SecBlockAlloc *TCAlloc = TC::AllocBlockAllocator("TC");
    TC::SecBlockAlloc *HMAlloc = TC::AllocBlockAllocator("HM");

    TestAlloc("TCAlloc", AllocTimes, TCAlloc);
    TestAlloc("HMAlloc", AllocTimes, HMAlloc);

    TestAccess("TCAccess", AccessTimes, TCAlloc);
    TestAccess("HMAccess", AccessTimes, HMAlloc);

}