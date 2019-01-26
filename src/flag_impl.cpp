#include <stdexcept>

#include "flag_impl.hpp"

using namespace std;

namespace cppli {

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

}
