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

FlagImpl::FlagImpl() = default;

FlagImpl::~FlagImpl() = default;

bool FlagImpl::get() const {
    return value;
}

void FlagImpl::setDefault() {
    value = false;
}

void FlagImpl::setImplicit() {
    value = true;
}

bool FlagImpl::supportsValue() const {
    return false;
}

void FlagImpl::setValue(const string& _value) {
    throw invalid_argument("Tried to give value `" + _value + "` to a flag!");
}

IntArgumentImpl::IntArgumentImpl(int _defaultValue, int _implicitValue):
        defaultValue(_defaultValue), implicitValue(_implicitValue) {}

IntArgumentImpl::~IntArgumentImpl() = default;

int IntArgumentImpl::get() const {
    return value;
}

void IntArgumentImpl::setImplicit() {
    value = implicitValue;
}

void IntArgumentImpl::setDefault() {
    value = defaultValue;
}

bool IntArgumentImpl::supportsValue() const {
    return true;
}

void IntArgumentImpl::setValue(const string& _value) {
    value = stoi(_value);
}

}
