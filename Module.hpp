//
// Created by user on 2017-10-11.
//

#ifndef IPARAM_MODULE_HPP
#define IPARAM_MODULE_HPP

#include "IParam.hpp"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Module {
public:
    Module() {}

protected:
    void addIParamsToContainer(IParamContainer *ic, vector<IParam*> &iparamsOfModule) {
        for( IParam *i : iparamsOfModule )
            ic->init(i);
    }
};

#endif //IPARAM_MODULE_HPP
