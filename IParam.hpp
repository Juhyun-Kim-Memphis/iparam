//
// Created by user on 2017-10-10.
//

#ifndef IPARAM_IPARAM_HPP
#define IPARAM_IPARAM_HPP

#include <string>

using namespace std;

class IParam {
public:
    IParam(string name_, int value_) : name(name_), value(value_) {}

    string name;
    int value;
};

#endif //IPARAM_IPARAM_HPP
