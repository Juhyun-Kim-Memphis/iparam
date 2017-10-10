//
// Created by user on 2017-10-11.
//

#ifndef IPARAM_MODULE_HPP
#define IPARAM_MODULE_HPP

#include "IParam.hpp"

#include <string>
using namespace std;

class Module {
};

class MemoryManager : public Module {
public:
    MemoryManager() : memorySizeLimit(string("MEMORY_SIZE_LIMIT"), 100) {}
    IParam memorySizeLimit;
};

class BufferCache : public Module {
public:
    BufferCache() : size(string("BUFFER_CACHE_SIZE"), 50) {}
    IParam size;
};

#endif //IPARAM_MODULE_HPP
