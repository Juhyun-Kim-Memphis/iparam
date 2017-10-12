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
            ic->init(iParam);
        }
    }

};

class MemoryManager : public Module {
public:
    MemoryManager(IParamSetter *iParamSetter, IParamContainer *ic = NULL)
    {
        //TODO: make this call to be unnecessary for concrete module;
        if(ic){
            memorySizeLimit = (IParamTyped<int> *)ic->getVal(string("MEMORY_SIZE_LIMIT"));
            iParamSetter->setIParamIfPossible(*memorySizeLimit);
        }
    }

    int getMemorySizeLimit() {
        return memorySizeLimit->value;
    }

private:
    IParamTyped<int> *memorySizeLimit;
};



#endif //IPARAM_MODULE_HPP
