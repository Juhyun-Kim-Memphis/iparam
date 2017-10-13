//
// Created by user on 2017-10-13.
//

#ifndef IPARAM_MEMORYMANAGER_HPP
#define IPARAM_MEMORYMANAGER_HPP

#include "IParam.hpp"
#include "Module.hpp"

class MemoryManager : public Module {
public:
    MemoryManager(IParamSetter *iParamSetter, IParamContainer *ic) {
        //TODO: make this call to be unnecessary for concrete module;
        if(ic){
            memorySizeLimit = (IParamTyped<int> *)ic->getVal(string("MEMORY_SIZE_LIMIT"));
            if(memorySizeLimit)
                iParamSetter->setIParamIfPossible(*memorySizeLimit);
            else {
                memorySizeLimit = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
                ic->init(memorySizeLimit);
            }
        }
    }

    MemoryManager(IParamSetter *iParamSetter) {
        memorySizeLimit = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
    }

    int getMemorySizeLimit() {
        return memorySizeLimit->value;
    }

private:
    IParamTyped<int> *memorySizeLimit;
};

#endif //IPARAM_MEMORYMANAGER_HPP
