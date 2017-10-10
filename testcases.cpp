#include "catch.hpp"

#include "IParam.hpp"
#include "Module.hpp"


using namespace std;

TEST_CASE("test1") {
    REQUIRE( 1 == 1 );
}

TEST_CASE("test module init and Default IParam value of modules") {
    MemoryManager *memoryManger = new MemoryManager;
    BufferCache *bufferCache = new BufferCache;
    REQUIRE(memoryManger->memorySizeLimit.value == 100);
    REQUIRE(bufferCache->size.value == 50);
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