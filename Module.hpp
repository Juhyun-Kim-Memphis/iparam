//
// Created by user on 2017-10-11.
//

#ifndef IPARAM_MODULE_HPP
#define IPARAM_MODULE_HPP

#include "IParam.hpp"

#include <string>
#include <sstream>

using namespace std;


class Module {
public:
    Module(IParamSetter *iParamSetter){}
};

class MemoryManager : public Module {
public:
    MemoryManager(IParamSetter *iParamSetter)
            : memorySizeLimit(string("MEMORY_SIZE_LIMIT"), 100),
              Module(iParamSetter) {}

    int getMemorySizeLimit() {
        return memorySizeLimit.value;
    }

private:
    IParamTyped<int> memorySizeLimit;
};

class BufferCache : public Module {
public:
    BufferCache(IParamSetter *iParamSetter)
            : Module(iParamSetter),
              name(string("BUFFER_CACHE_NAME"), string("default string"))
    {
        iParamSetter->setIParamIfPossible(size, string("BUFFER_CACHE_SIZE"));
        iParamSetter->setIParamIfPossible(name, string("BUFFER_CACHE_NAME"));
    }

    int getSize() {
        return size.value;
    }

    string getName() {
        return name.value;
    }

private:
    IParamTyped<int> size;
    IParamTyped<string> name;
};

#endif //IPARAM_MODULE_HPP
