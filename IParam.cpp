#include "IParam.hpp"

void IParamSetter::setIParamIfPossible(IParam &iparam, string iParamName) {
    if(hasIParamNamed(iParamName))
        iparam.setValue(getValueOf(iParamName));
}