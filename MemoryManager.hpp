#ifndef IPARAM_MEMORYMANAGER_HPP
#define IPARAM_MEMORYMANAGER_HPP

#include "IParam.hpp"
#include "Module.hpp"

class MemoryManager : public Module {
public:
    MemoryManager(IParamTyped<int> *memSizeLimInput, IParamSetter &initializer)
            : memorySizeLimit(memSizeLimInput) {
        initializer.setIParamIfPossible(*memorySizeLimit);
        memorySizeLimit = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
    }

    explicit MemoryManager(IParamSetter &initializer) {
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
    /** @ingroup IParam */
    IParamTyped<int> *memorySizeLimit;
};

#endif //IPARAM_MEMORYMANAGER_HPP
