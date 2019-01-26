#include <cppli_impl/flag.hpp>

#include <stdexcept>

using namespace std;

namespace cppli {

Flag::Flag() = default;

Flag::~Flag() = default;

bool Flag::get() const {
    return value;
}

void Flag::setDefault() {
    value = false;
}

void Flag::setImplicit() {
    value = true;
}

bool Flag::supportsValue() const {
    return false;
}

void Flag::setValue(const string& _value) {
    throw invalid_argument("Tried to give value `" + _value + "` to a flag!");
}

FlagSpec::FlagSpec(string _name): name(move(_name)) {}

FlagSpec& FlagSpec::setDescription(const string& _description) {
    description = _description;
    return *this;
}

FlagSpec& FlagSpec::setHelpGroup(const string& _helpGroup) {
    helpGroup = _helpGroup;
    return *this;
}

FlagSpec& FlagSpec::setShortName(const string& _shortName) {
    shortName = _shortName;
    return *this;
}

}
