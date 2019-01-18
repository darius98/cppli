#include <cppli_impl/int_argument.hpp>

using namespace std;

namespace cppli {

IntArgument::~IntArgument() = default;

IntArgumentSpec::IntArgumentSpec(string _name): name(move(_name)) {}

IntArgumentSpec& IntArgumentSpec::withHelpText(const string& _helpText) {
    helpText = _helpText;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::withShortName(const string& _shortName) {
    shortName = _shortName;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::withDefaultValue(int _defaultValue) {
    defaultValue = _defaultValue;
    return *this;
}

IntArgumentSpec& IntArgumentSpec::withImplicitValue(int _implicitValue) {
    implicitValue = _implicitValue;
    return *this;
}

}
