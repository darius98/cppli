#include <iostream>

#include "argument_impl.hpp"

using namespace std;

namespace cppli {

ArgumentImpl::ArgumentImpl(string _defaultValue, string _implicitValue):
        defaultValue(move(_defaultValue)),
        implicitValue(move(_implicitValue)) {}

ArgumentImpl::~ArgumentImpl() = default;

string ArgumentImpl::get() const {
    return value;
}

void ArgumentImpl::setDefault() {
    value = defaultValue;
}

void ArgumentImpl::setImplicit() {
    value = implicitValue;
}

bool ArgumentImpl::supportsValue() const {
    return true;
}

void ArgumentImpl::setValue(const string& _value) {
    value = _value;
}

}
