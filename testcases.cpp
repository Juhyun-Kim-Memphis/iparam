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
    IParamSetter iParamSetter(emptyTipFile);
    ModuleFactory *tlite = new TLiteModuleFactory(iParamSetter);

    BufferCache *bufferCache = tlite->getBufferCache();
    MemoryManager *memoryManager = tlite->getMemoryManager();
    IParamContainer *iParamContainer = tlite->getIParamContainer();

    REQUIRE(memoryManager->getMemorySizeLimit() == 100);
    REQUIRE(bufferCache->getSize() == 50);
    REQUIRE(bufferCache->getName() == "myBufferCache");

    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSetParsed["BUFFER_CACHE_NAME"] = string("other_name");
    IParamSetter *alterSystemSet = new IParamSetter(alterSystemSetParsed);
    iParamContainer->setIParams(alterSystemSet);

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
    /* Tibero booting */
    ModuleFactory *tibero = new TiberoModuleFactory();
    BufferCache *bufferCache = tibero->getBufferCache();
    MemoryManager *memoryManager = tibero->getMemoryManager();
    IParamContainer *iParamContainer = tibero->getIParamContainer();

    /* check IParam default  values */
    REQUIRE(bufferCache->getSize() == 50);
    REQUIRE(memoryManager->getMemorySizeLimit() == 100);

    /* change BUFFER_CACHE_SIZE to 40 (valid change) by alterSystemSet. */
    map<string, string> alterSystemSetParsed;
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("40");
    IParamSetter *alterSystemSet = new IParamSetter(alterSystemSetParsed);
    REQUIRE_NOTHROW(iParamContainer->setIParams(alterSystemSet));
    REQUIRE(bufferCache->getSize() == 40);

    /* try to change BUFFER_CACHE_SIZE to 999 (NOT allowed) */
    alterSystemSetParsed["BUFFER_CACHE_SIZE"] = string("999");
    alterSystemSet = new IParamSetter(alterSystemSetParsed);
    /* check this attempt throw exception and change doesn't happen. */
    REQUIRE_THROWS(iParamContainer->setIParams(alterSystemSet));
    REQUIRE(bufferCache->getSize() == 40);
    REQUIRE(iParamContainer->iParams.size() == 3);
    //TODO: errormsg in exception object
}

// TODO: bootstrapper (ModuleFactory) elaborate
// TODO: IParam with No value (no memoryOverhead) (fixAtNewMount<modifiable<dynamic)
// TODO: Module들이 iparam container한테 iparam 각출하는 코드를 concrete modoule class가 짜지 않아도 될 방법은 없나?
// TODO: doxygen으로 모든 IPARAM목록 띄워주는 법
// TODO: to document @desc, @range, @recommend, @syntax
// TODO: IDE에서 todo list, run with coverage.

// To Prove: customizablity of IParam, container for all iparam