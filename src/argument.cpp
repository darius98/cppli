#include <cppli_impl/argument.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/numeric_argument.hpp>

using namespace std;

namespace cppli {

Argument::Argument(string _defaultValue, string _implicitValue):
        defaultValue(move(_defaultValue)),
        implicitValue(move(_implicitValue)) {}

Argument::~Argument() = default;

string Argument::get() const {
    return value;
}

void Argument::setDefault() {
    value = defaultValue;
}

void Argument::setImplicit() {
    value = implicitValue;
}

bool Argument::supportsValue() const {
    return true;
}

void Argument::setValue(const string& _value) {
    value = _value;
}

ArgumentSpec::ArgumentSpec(string _name): name(move(_name)) {}

ArgumentSpec& ArgumentSpec::setDescription(const string& _description) {
    description = _description;
    return *this;
}

ArgumentSpec& ArgumentSpec::setHelpGroup(const string& _helpGroup) {
    helpGroup = _helpGroup;
    return *this;
}

ArgumentSpec& ArgumentSpec::setShortName(const string& _shortName) {
    shortName = _shortName;
    return *this;
}

ArgumentSpec& ArgumentSpec::setDefaultValue(const string& _defaultValue) {
    defaultValue = _defaultValue;
    return *this;
}

ArgumentSpec& ArgumentSpec::setImplicitValue(const string& _implicitValue) {
    implicitValue = _implicitValue;
    return *this;
}

}
