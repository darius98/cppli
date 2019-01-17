#include <iostream>

#include "argument_impl.hpp"

using namespace std;

namespace cppli {

ArgumentImpl::ArgumentImpl(const string& _defaultValue, string _implicitValue):
        GenericArgumentImpl<string>(_defaultValue, _implicitValue) {}

ArgumentImpl::~ArgumentImpl() = default;

void ArgumentImpl::setValue(const string& _value) {
    value = _value;
}

FlagImpl::FlagImpl(): GenericArgumentImpl<bool>(false, true) {}

FlagImpl::~FlagImpl() = default;

void FlagImpl::setValue(const string& _value) {
    value = _value == "true"
            || _value == "1"
            || _value == "enabled";
}

IntArgumentImpl::IntArgumentImpl(int defaultValue, int implicitValue):
        GenericArgumentImpl<int>(defaultValue, implicitValue) {}

IntArgumentImpl::~IntArgumentImpl() = default;

void IntArgumentImpl::setValue(const string& _value) {
    value = stoi(_value);
}

}
