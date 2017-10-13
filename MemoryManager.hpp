//
// Created by user on 2017-10-13.
//

#ifndef IPARAM_MEMORYMANAGER_HPP
#define IPARAM_MEMORYMANAGER_HPP

#include "IParam.hpp"
#include "Module.hpp"

class MemoryManager : public Module {
public:
    MemoryManager(IParamTyped<int> *memSizeLimInput, IParamSetter &initializer)
            : memorySizeLimit(memSizeLimInput)
    {
        //TODO: make this call to be unnecessary for concrete module;
        initializer.setIParamIfPossible(*memorySizeLimit);
        memorySizeLimit = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
    }

    MemoryManager(IParamSetter &initializer) {
        memorySizeLimit = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
        initializer.setIParamIfPossible(*memorySizeLimit);
    }

    vector<IParam *> getIParams() {
        vector<IParam *> myIParams;
        myIParams.push_back(memorySizeLimit);
        return myIParams;
    }

    int getMemorySizeLimit() {
        return memorySizeLimit->value;
    }

private:
    IParamTyped<int> *memorySizeLimit;
};

#endif //IPARAM_MEMORYMANAGER_HPP
