//
// Created by user on 2017-10-10.
//

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
    IParam() {}

    virtual void setValue(string in) = 0;
    virtual bool isValid() = 0;

    string getName() {
        return name;
    }

    string name;
};

template <typename T>
class IParamTyped : public IParam {
public:
    IParamTyped() {}
    IParamTyped(string name_, T value_) : IParam(name_), value(value_) {}

    void setValue(string in) {
        stringstream ss(in);
        ss >> value;
    }

    bool isValid() { return  true; }

    T value;
};

class IParamSetter {
public:
    IParamSetter(map<string, string> m) : iParamMap(m) {}
    void setIParamIfPossible(IParam &iparam, string iParamName);
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
    void addNew(IParam *iParam);

//private:
    vector<IParam*> iParams;
};

#endif //IPARAM_IPARAM_HPP
