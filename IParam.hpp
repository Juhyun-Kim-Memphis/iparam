//
// Created by user on 2017-10-10.
//

#ifndef IPARAM_IPARAM_HPP
#define IPARAM_IPARAM_HPP

#include <string>
#include <map>
#include <sstream>

using namespace std;

class IParam {

public:
    virtual void setValue(string in) = 0;
};

template <typename T>
class IParamTyped : public IParam {
public:
    IParamTyped() {}
    IParamTyped(string name_, T value_) : name(name_), value(value_) {}

    void setValue(string in) {
        stringstream ss(in);
        ss >> value;
    }

    string name;
    T value;
};

class IParamSetter {
public:
    IParamSetter(map<string, string> m) : iParamMap(m) {}

    void setIParamIfPossible(IParam &iparam, string iParamName);

private:
    bool hasIParamNamed(string name) {
        return iParamMap.find(name) != iParamMap.end();
    }

    string getValueOf(string name) {
        return iParamMap[name];
    }
    map<string, string> iParamMap;
};

#endif //IPARAM_IPARAM_HPP
