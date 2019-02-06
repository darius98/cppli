#include <cppli_impl/argument.hpp>

using namespace std;

namespace cppli {

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

namespace detail {

ArgumentDetails::ArgumentDetails(string _defaultValue, string _implicitValue):
        defaultValue(move(_defaultValue)),
        implicitValue(move(_implicitValue)) {}

ArgumentDetails::~ArgumentDetails() = default;

string ArgumentDetails::get() const {
    return value;
}

void ArgumentDetails::setDefault() {
    value = defaultValue;
    appearedInArgs = false;
}

void ArgumentDetails::setImplicit() {
    value = implicitValue;
    appearedInArgs = true;
}

bool ArgumentDetails::eatsPositionalArgument() const {
    return true;
}

void ArgumentDetails::setValue(const string& _value) {
    value = _value;
    appearedInArgs = true;
}

bool ArgumentDetails::appeared() const {
    return appearedInArgs;
}

}  // namespace detail
}  // namespace cppli
