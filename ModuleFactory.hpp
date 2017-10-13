//
// Created by juhyun on 17. 10. 12.
//

#ifndef IPARAM_MODULEFACTORY_HPP
#define IPARAM_MODULEFACTORY_HPP


#include "IParam.hpp"
#include "Module.hpp"
#include "BufferCache.hpp"
#include "MemoryManager.hpp"

class ModuleFactory {
public:
    void boot() {
        //Instanciating IParam Container to store all the references for IParam objects
        map<string, string> tipFile;
        IParamSetter *iParamSetter = new IParamSetter(tipFile);

        memSizeLim = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
        iParamContainer.init(memSizeLim);
        memoryManager = new MemoryManager(iParamSetter,&iParamContainer);

        bufCacheSize = new BufferCacheSize(string("BUFFER_CACHE_SIZE"), 50);
        bufCacheSize->setRef(memSizeLim);
        iParamContainer.init(bufCacheSize);
        bufferCache = new BufferCache(iParamSetter, &iParamContainer);
    }

    IParamContainer iParamContainer;
    IParamTyped<int> *memSizeLim;
    MemoryManager *memoryManager;
    BufferCacheSize *bufCacheSize;
    BufferCache *bufferCache;
};


#endif //IPARAM_MODULEFACTORY_HPP
