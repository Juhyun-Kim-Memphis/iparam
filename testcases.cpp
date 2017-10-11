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

TEST_CASE("test default") {
    map<string, string> emptyTipFile;

    IParamSetter *iParamSetter =new IParamSetter(emptyTipFile);
    MemoryManager *memoryManger = new MemoryManager(iParamSetter);
    BufferCache *bufferCache = new BufferCache(iParamSetter);

    REQUIRE(memoryManger->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 50);
    REQUIRE(bufferCache->getName() == "default");
}

//TEST_CASE("test Module with default iparam") {
//    AlterSystemSetDDL("TEST_VAL1=")
//}

// TODO: bootstrapper
// TODO: bool, int, string (primitive) type iparam
// TODO: alter system set
// TODO: Real example Module (Memory manager <-- buffer cache)
// TODO: tip file load
// TODO: condition check (simple, dependency)
// TODO: condition check in "alter system set"

// To Prove: customizablity of IParam, container for all iparam