#ifndef IPARAM_MODULEFACTORY_HPP
#define IPARAM_MODULEFACTORY_HPP


#include "IParam.hpp"
#include "Module.hpp"
#include "BufferCache.hpp"
#include "MemoryManager.hpp"

class ModuleFactory {
public:
    void boot() {
        //Instantiating IParam Container to store all the references for IParam objects
        map<string, string> tipFile;
        IParamSetter iParamInitializer(tipFile);

        IParamTyped<int> *memSizeLim = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
        memoryManager = new MemoryManager(memSizeLim, iParamInitializer);

        BufferCacheSize *bufCacheSize = new BufferCacheSize(string("BUFFER_CACHE_SIZE"), 50, memSizeLim);
        bufferCache = new BufferCache(bufCacheSize, iParamInitializer);

        iParamContainer.insert(memoryManager->getIParams());
        iParamContainer.insert(bufferCache->getIParams());
    }

    IParamContainer iParamContainer;
    MemoryManager *memoryManager;
    BufferCache *bufferCache;
};


#endif //IPARAM_MODULEFACTORY_HPP
