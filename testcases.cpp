#include <map>
#include "catch.hpp"

#include "IParam.hpp"
#include "Module.hpp"

using namespace std;

TEST_CASE("test module init and Default IParam value of modules") {
    map<string, string> tipFileResult;
    tipFileResult["BUFFER_CACHE_SIZE"] = string("40");
    tipFileResult["BUFFER_CACHE_NAME"] = string("another_name");

    IParamSetter *iParamSetter = new IParamSetter(tipFileResult);
    MemoryManager *memoryManger = new MemoryManager(iParamSetter);
    BufferCache *bufferCache = new BufferCache(iParamSetter);

    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 40);
    REQUIRE(bufferCache->getName() == "another_name");
}

TEST_CASE("test default value and alter system set") {
    map<string, string> emptyTipFile;
    IParamContainer iParamContainer;

    IParamSetter *iParamSetter = new IParamSetter(emptyTipFile);
    MemoryManager *memoryManger = new MemoryManager(iParamSetter, &iParamContainer);
    BufferCache *bufferCache = new BufferCache(iParamSetter, &iParamContainer);

    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSetParsed["BUFFER_CACHE_NAME"] = string("myName");
    IParamSetter *alterSystemSet = new IParamSetter(alterSystemSetParsed);
    iParamContainer.setIParams(alterSystemSet);

    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 999);
    REQUIRE(bufferCache->getName() == "myName");
}


bool isBigger200(int val){ return val > 200; }
TEST_CASE("test ConditionedIParam condition check") {
    IParam *iParam = new ConditionedIParam<isBigger200>(string("TEST_VAL1"), 201);
    REQUIRE(iParam->isValid());
}

TEST_CASE("test dependent condition check") {
    IParamTyped<int> depended(string("SMALLER"), 100);
    DependingIParam *depending = new DependingIParam(string("BIGGER"), 99, depended);

    REQUIRE(!depending->isValid());
    depending->setValue(string("101"));
    REQUIRE(depending->isValid());
}

TEST_CASE("test dependent condition check by Module") {

}


// TODO: condition check (simple, dependency (Memory manager <-- buffer cache))
// TODO: condition check in "alter system set"
// TODO: IParam with No value (no memoryOverhead) (fixAtNewMount<modifiable<dynamic)
// TODO: to document @desc, @range, @recommend, @syntax
// TODO: bootstrapper

// To Prove: customizablity of IParam, container for all iparam