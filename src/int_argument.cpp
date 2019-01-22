#include <cppli_impl/int_argument.hpp>

using namespace std;

namespace cppli {

IntArgument::~IntArgument() = default;

IntArgumentSpec::IntArgumentSpec(string _name): name(move(_name)) {}

IntArgumentSpec& IntArgumentSpec::setDescription(const string& _description) {
    description = _description;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::setHelpGroup(const string& _helpGroup) {
    helpGroup = _helpGroup;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::setShortName(const string& _shortName) {
    shortName = _shortName;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::setDefaultValue(int _defaultValue) {
    defaultValue = _defaultValue;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::setImplicitValue(int _implicitValue) {
    implicitValue = _implicitValue;
    return *this;
}

}
