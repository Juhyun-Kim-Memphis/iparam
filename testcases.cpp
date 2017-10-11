#include <map>
#include "catch.hpp"

#include "IParam.hpp"
#include "Module.hpp"


using namespace std;

TEST_CASE("test1") {
    REQUIRE( 1 == 1 );
}

TEST_CASE("test module init and Default IParam value of modules") {
    string bufferCacheSize("40");
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

TEST_CASE("test default value and alter system set ddl") {
    map<string, string> emptyTipFile;
    IParamContainer iParamContainer;

    IParamSetter *iParamSetter =new IParamSetter(emptyTipFile);
    MemoryManager *memoryManger = new MemoryManager(iParamSetter, &iParamContainer);
    BufferCache *bufferCache = new BufferCache(iParamSetter, &iParamContainer);

    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 50);
    REQUIRE(bufferCache->getName() == "default_value");

    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSetParsed["BUFFER_CACHE_NAME"] = string("myName");
    IParamSetter *alterSystemSet =new IParamSetter(alterSystemSetParsed);
    iParamContainer.setIParams(alterSystemSet);

    REQUIRE(iParamContainer.iParams.size() == 3);
    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 999);
    REQUIRE(bufferCache->getName() == "myName");
}


class ConditionedIParam : public IParamTyped<int> {
public:
    ConditionedIParam(string name_, int value_) : IParamTyped<int>(name_, value_) {}
    bool isValid(){
        return value > 200;
    }
};

TEST_CASE("test condition check") {
    IParam *iParam = new ConditionedIParam(string("TEST_VAL1"), 201);

    REQUIRE(iParam->isValid());
}

class DependingIParam : public IParamTyped<int> {
public:
    DependingIParam(string name_, int value_) : IParamTyped<int>(name_, value_) {}

    bool isValid(const IParamTyped<int> &dependedIParam){
        return value > dependedIParam.value;
    }
};


TEST_CASE("test dependent condition check") {
    DependingIParam *depending = new DependingIParam(string("I_SHOULD_BE_BIGGER"), 201);
    IParamTyped<int> depended(string("DONT_KNOW_ANYTHING"), 100);

    REQUIRE(depending->isValid(depended));
}



TEST_CASE("test Module with default iparam") {
    map<string, string> alterSystemSetParsed;
    IParamSetter *iParamSetter =new IParamSetter(alterSystemSetParsed);
}

// TODO: bootstrapper
// TODO: bool, int, string (primitive) type iparam
// TODO: alter system set
// TODO: Real example Module (Memory manager <-- buffer cache)
// TODO: tip file load
// TODO: condition check (simple, dependency)
// TODO: condition check in "alter system set"

// To Prove: customizablity of IParam, container for all iparam