//
// Created by user on 2017-10-11.
//

#ifndef IPARAM_MODULE_HPP
#define IPARAM_MODULE_HPP

#include "IParam.hpp"

#include <string>
#include <sstream>
#include <vector>

using namespace std;


class Module {
public:
    Module() {}
protected:
    void addIParamsToContainer(IParamContainer *ic, vector<IParam*> &iparamsOfModule) {
        for (vector<IParam *>::iterator it = iparamsOfModule.begin() ; it != iparamsOfModule.end(); ++it){
            IParam *iParam = *it;
            ic->addNew(iParam);
        }
    }

};

class MemoryManager : public Module {
public:
    MemoryManager(IParamSetter *iParamSetter, IParamContainer *ic = NULL)
            : memorySizeLimit(string("MEMORY_SIZE_LIMIT"), 100)
    {
        iParamSetter->setIParamIfPossible(memorySizeLimit, string("MEMORY_SIZE_LIMIT"));

        //TODO: make this call to be unnecessary for concrete module;
        if(ic){
            vector<IParam*> myIParams;
            myIParams.push_back(&memorySizeLimit);
            addIParamsToContainer(ic, myIParams);
        }
    }

    int getMemorySizeLimit() {
        return memorySizeLimit.value;
    }

private:
    IParamTyped<int> memorySizeLimit;
};

class BufferCache : public Module {
public:
    BufferCache(IParamSetter *iParamSetter, IParamContainer *ic = NULL)
            : name(string("BUFFER_CACHE_NAME"), string("default_value")),
              size(string("BUFFER_CACHE_SIZE"), 50)
    {
        iParamSetter->setIParamIfPossible(size, string("BUFFER_CACHE_SIZE"));
        iParamSetter->setIParamIfPossible(name, string("BUFFER_CACHE_NAME"));

        //TODO: make this call to be unnecessary for concrete module;
        if(ic){
            vector<IParam*> myIParams;
            myIParams.push_back(&size);
            myIParams.push_back(&name);
            addIParamsToContainer(ic, myIParams);
        }
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
