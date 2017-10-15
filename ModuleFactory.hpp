#ifndef IPARAM_MODULEFACTORY_HPP
#define IPARAM_MODULEFACTORY_HPP


#include "IParam.hpp"
#include "Module.hpp"
#include "BufferCache.hpp"
#include "MemoryManager.hpp"

class ModuleFactory {
public:
    MemoryManager *getMemoryManager() { return  memoryManager;}
    BufferCache *getBufferCache() { return  bufferCache;}
    IParamContainer *getIParamContainer() { return  iParamContainer;}

protected:
    MemoryManager *memoryManager;
    BufferCache *bufferCache;
    IParamContainer *iParamContainer;
};

class TiberoModuleFactory : public ModuleFactory {
public:
    TiberoModuleFactory() {
        // load tip file and parse to make map<string, string> object.
        map<string, string> tipFile;
        IParamSetter iParamInitializer(tipFile);

        IParamTyped<int> *memSizeLim = new IParamTyped<int>(string("MEMORY_SIZE_LIMIT"), 100);
        memoryManager = new MemoryManager(memSizeLim, iParamInitializer);

        BufferCacheSize *bufCacheSize = new BufferCacheSize(string("BUFFER_CACHE_SIZE"), 50, memSizeLim);
        bufferCache = new BufferCache(bufCacheSize, iParamInitializer);

        //Instantiating IParam Container to store all the references for IParam objects
        iParamContainer = new IParamContainer();
        iParamContainer->insert(memoryManager->getIParams());
        iParamContainer->insert(bufferCache->getIParams());
    }
};

class TLiteModuleFactory : public ModuleFactory {
public:
    TLiteModuleFactory(IParamSetter iParamInitializer) {
        memoryManager = new MemoryManager(iParamInitializer);
        bufferCache = new BufferCache(iParamInitializer);
        iParamContainer = new IParamContainer();
        iParamContainer->insert(memoryManager->getIParams());
        iParamContainer->insert(bufferCache->getIParams());
    }

private:
    TLiteModuleFactory(){};
};


#endif //IPARAM_MODULEFACTORY_HPP
