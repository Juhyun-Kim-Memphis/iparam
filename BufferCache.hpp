//
// Created by juhyun on 17. 10. 12.
//

#ifndef IPARAM_BUFFERCACHE_HPP
#define IPARAM_BUFFERCACHE_HPP

#include <iostream>
#include "Module.hpp"

class BufferCacheSize : public IParamTyped<int> {
public:
    BufferCacheSize(string name_, int value_)
            : IParamTyped<int>(name_, value_) {}

    void setValue(string in) {
        int res = ref->value;
        stringstream ss(in);
        int inputVal;
        ss >> inputVal;
        if(res > inputVal){
            IParamTyped<int>::setValue(in);
        } else {
            std::cout << " Fail to setValue \n";
        }
    }

    void setRef(IParamTyped<int> *in){
        this->ref = in;
    }

private:

    IParamTyped<int> *ref;
};

class BufferCache : public Module {
public:
    BufferCache(IParamSetter *iParamSetter, IParamContainer *ic = NULL)
        : name(string("BUFFER_CACHE_NAME"), string("myBufferCache"))
    {


        //TODO: make this call to be unnecessary for concrete module;
        if(ic){
            size = (BufferCacheSize *)ic->getVal(string("BUFFER_CACHE_SIZE"));

            iParamSetter->setIParamIfPossible(*size);
            iParamSetter->setIParamIfPossible(name);
        }
    }

    int getSize() {
        return size->value;
    }

    string getName() {
        return name.value;
    }

private:
    BufferCacheSize *size;
    IParamTyped<string> name;
};


#endif //IPARAM_BUFFERCACHE_HPP
