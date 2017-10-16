#ifndef IPARAM_BUFFERCACHE_HPP
#define IPARAM_BUFFERCACHE_HPP

#include <iostream>
#include "Module.hpp"

class BufferCacheSize : public IParamTyped<int> {
public:
    BufferCacheSize(string name_, int value_, IParamTyped<int> *refIn)
            : IParamTyped<int>(name_, value_), memorySizeLimit(refIn) {}

    void setValue(string in) override {
        int newBufferCacheSize = stringToValueType(in);

        if(isSmallerThanMemSizeLimit(newBufferCacheSize))
            IParamTyped<int>::setValue(in);
        else
            throw exception();
    }

private:
    IParamTyped<int> *memorySizeLimit;
    bool isSmallerThanMemSizeLimit(int bufferCacheSize) {
        int memSizeLimit = memorySizeLimit->value;
        return bufferCacheSize < memSizeLimit;
    }
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
            : name(string("BUFFER_CACHE_NAME"), string("myBufferCache")) {
        size = new IParamTyped<int>(string("BUFFER_CACHE_SIZE"), 50);
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
    /** @addtogroup IParam
     **  @{ */
    /** @brief BUFFER_CACHE_SIZE: size of this buffer cache.\n
     *  default: 50
     * */
    IParamTyped<int> *size;
    /** name of this buffer cache. */
    IParamTyped<string> name;
    /** @} */
};


#endif //IPARAM_BUFFERCACHE_HPP
