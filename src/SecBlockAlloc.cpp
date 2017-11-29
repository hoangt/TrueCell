#include "SecBlockAlloc.h"
#include "HMBAlloc.h"
#include "TCBAlloc.h"

#include <iostream>
#include <cstring>

namespace TC{
    SecBlockAlloc *AllocBlockAllocator(const char *typ){
        SecBlockAlloc *alloc;
        if (!strcmp(typ, "TC"))
            alloc = new TCBAlloc();
        else if (!strcmp(typ, "HM"))
            alloc = new HMBAlloc();
        else{
            std::cout << "No such type \"" << typ << "\"";
            exit(1);
        }
        return alloc;
    }
}
