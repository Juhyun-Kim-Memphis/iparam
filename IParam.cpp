#include <algorithm>
#include "IParam.hpp"

void IParamSetter::setIParamIfPossible(IParam &iparam) {
    string iParamName(iparam.getName());
    if(hasIParamNamed(iParamName))
        iparam.setValue(getValueOf(iParamName));
}

void IParamSetter::applyAll(vector<IParam *> &iParams) {
    for (vector<IParam *>::iterator it = iParams.begin() ; it != iParams.end(); ++it) {
        IParam *iParam = *it;
        setIParamIfPossible(*iParam);
    }
}

void IParamContainer::setIParams(IParamSetter *setter) {
    setter->applyAll(iParams);
}

void IParamContainer::init(IParam *iParam) {
    if(iParams.end() == find(iParams.begin(), iParams.end(), iParam))
        iParams.push_back(iParam);
}

