//
// Created by juhyun on 17. 10. 12.
//

#ifndef IPARAM_BUFFERCACHE_HPP
#define IPARAM_BUFFERCACHE_HPP

#include <iostream>
#include "Module.hpp"

class BufferCacheSize : public IParamTyped<int> {
public:
    BufferCacheSize(string name_, int value_, IParamTyped<int> *refIn)
            : IParamTyped<int>(name_, value_), ref(refIn) {}

    void setValue(string in) {

        int res;
        if(ref == NULL){
            IParamTyped<int>::setValue(in);
            return;
        }

        res = ref->value;
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

    BufferCache(BufferCacheSize *in, IParamSetter &initializer)
        : size(in), name(string("BUFFER_CACHE_NAME"), string("myBufferCache")) {
        //TODO: make this call to be unnecessary for concrete module;
        initializer.setIParamIfPossible(*size);
        initializer.setIParamIfPossible(name);
    }

    explicit BufferCache(IParamSetter &initializer)
            : name(string("BUFFER_CACHE_NAME"), string("myBufferCache"))  {
        size = new BufferCacheSize(string("BUFFER_CACHE_SIZE"), 50, NULL);
        //TODO: remove null argument here.

        initializer.setIParamIfPossible(name);
        initializer.setIParamIfPossible(*size);
    }

    int getSize() {
        return size->value;
    }

    string getName() {
        return name.value;
    }

    vector<IParam *> getIParams() {
        vector<IParam *> myIParams;
        myIParams.push_back(size);
        myIParams.push_back(&name);
        return myIParams;
    }

private:
    BufferCacheSize *size;
    IParamTyped<string> name;
};


#endif //IPARAM_BUFFERCACHE_HPP
