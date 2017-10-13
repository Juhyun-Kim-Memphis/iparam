#include <map>
#include "catch.hpp"

#include "IParam.hpp"
#include "BufferCache.hpp"
#include "ModuleFactory.hpp"

using namespace std;

TEST_CASE("test module insert and Default IParam value of modules") {
    map<string, string> tipFileResult;
    tipFileResult["BUFFER_CACHE_SIZE"] = string("90");
    tipFileResult["BUFFER_CACHE_NAME"] = string("another_name");

    IParamSetter iParamSetter(tipFileResult);
    MemoryManager *memoryManger = new MemoryManager(iParamSetter);
    BufferCache *bufferCache = new BufferCache(iParamSetter);

    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 90);
    REQUIRE(bufferCache->getName() == "another_name");
}

TEST_CASE("test default value and alter system set") {
    map<string, string> emptyTipFile;
    IParamContainer iParamContainer;

    IParamSetter iParamSetter(emptyTipFile);
    MemoryManager *memoryManager = new MemoryManager(iParamSetter);
    BufferCache *bufferCache = new BufferCache(iParamSetter);

    iParamContainer.insert(memoryManager->getIParams());
    iParamContainer.insert(bufferCache->getIParams());

    REQUIRE(memoryManager->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 50);
    REQUIRE(bufferCache->getName() == "myBufferCache");

    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSetParsed["BUFFER_CACHE_NAME"] = string("other_name");
    IParamSetter *alterSystemSet = new IParamSetter(alterSystemSetParsed);
    iParamContainer.setIParams(alterSystemSet);

    REQUIRE(memoryManager->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 999);
    REQUIRE(bufferCache->getName() == "other_name");
}


bool isBigger200(int val){ return val > 200; }
TEST_CASE("test ConditionedIParam condition check") {
    IParam *iParam = new ConditionedIParam<isBigger200>(string("TEST_VAL1"), 201);
    REQUIRE(iParam->isValid());
}

TEST_CASE("test dependent condition check") {
    IParamTyped<int> depended(string("SMALLER"), 100);
    DependingIParam *depending = new DependingIParam(string("BIGGER"), 101, depended);

    REQUIRE(depending->isValid());
    depending->setValue(string("99"));
    REQUIRE(!depending->isValid());
}

TEST_CASE("test dependent condition check by Module") {
    ModuleFactory moduleFactory;
    moduleFactory.boot();

    REQUIRE(moduleFactory.bufferCache->getSize() == 50);
    REQUIRE(moduleFactory.memoryManager->getMemorySizeLimit() == 100);

    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("40");
    IParamSetter *alterSystemSet = new IParamSetter(alterSystemSetParsed);
    moduleFactory.iParamContainer.setIParams(alterSystemSet);

    REQUIRE(moduleFactory.bufferCache->getSize() == 40);

    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSet = new IParamSetter(alterSystemSetParsed);
    moduleFactory.iParamContainer.setIParams(alterSystemSet);
    REQUIRE(moduleFactory.bufferCache->getSize() == 40);
    REQUIRE(moduleFactory.iParamContainer.iParams.size() == 3);
    //TODO: errormsg
}

// TODO: bootstrapper (ModuleFactory) elaborate
// TODO: IParam with No value (no memoryOverhead) (fixAtNewMount<modifiable<dynamic)
// TODO: to document @desc, @range, @recommend, @syntax
// TODO: bootstrapper
// TODO: Module들이 iparam container한테 iparam 각출하는 코드를 concrete modoule class가 짜지 않아도 될 방법은 없나?

// To Prove: customizablity of IParam, container for all iparam