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

bool FlagImpl::supportsValue() const {
    return false;
}

void FlagImpl::setValue(const string& _value) {
    throw invalid_argument("Tried to give value `" + _value + "` to a flag!");
}

IntArgumentImpl::IntArgumentImpl(int defaultValue, int implicitValue):
        GenericArgumentImpl<int>(defaultValue, implicitValue) {}

IntArgumentImpl::~IntArgumentImpl() = default;

void IntArgumentImpl::setValue(const string& _value) {
    value = stoi(_value);
}

}
