#ifndef IPARAM_IPARAM_HPP
#define IPARAM_IPARAM_HPP

#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

class IParam {
public:
    IParam(string name_) : name(name_) {}

    virtual void setValue(string in) = 0;
    virtual bool isValid() { return  true; }

    string getName() { return name; }

private:
    const string name;
};

template <typename T>
class IParamTyped : public IParam {
public:
    IParamTyped(string name_, T value_) : IParam(name_), value(value_) {}

    void setValue(string in) {
        stringstream ss(in);
        ss >> value;
    }

    T value;
};




class IParamSetter {
public:
    IParamSetter(map<string, string> m) : iParamMap(m) {}
    void setIParamIfPossible(IParam &iparam);

    void applyAll(vector<IParam *> &iParams);

private:
    bool hasIParamNamed(string name) {
        return iParamMap.find(name) != iParamMap.end();
    }

    string getValueOf(string name) {
        return iParamMap[name];
    }

    map<string, string> iParamMap;
};

class IParamContainer {
public:
    void setIParams(IParamSetter *setter);
    void init(IParam *iParam);
    IParam *getVal(string iParamName){
        for (vector<IParam *>::iterator it = iParams.begin() ; it != iParams.end(); ++it) {
            IParam *iParam = *it;
            if(iParam->getName() == iParamName)
                return iParam;
        }
        return NULL;
    }

//private:
    vector<IParam*> iParams;
};

typedef bool(*IntPredicate)(int);
template<IntPredicate isValidInt>
class ConditionedIParam : public IParamTyped<int> {
public:
    ConditionedIParam(string name_, int value_) : IParamTyped<int>(name_, value_) {}
    bool isValid(){
        return isValidInt(value);
    }
};

class DependingIParam : public IParamTyped<int> {
public:
    DependingIParam(string name_, int value_, const IParamTyped<int> &d)
            : IParamTyped<int>(name_, value_), dependedIParam(d) {}
    bool isValid() {
        return dependedIParam.value < value;
    }

private:
    const IParamTyped<int> &dependedIParam;
};

#endif //IPARAM_IPARAM_HPP
