#include <cppli_impl/argument.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/int_argument.hpp>

using namespace std;

namespace cppli {

Argument::~Argument() = default;

ArgumentSpec::ArgumentSpec(string _name): name(move(_name)) {}

ArgumentSpec& ArgumentSpec::setDescription(const string& _helpText) {
    helpText = _helpText;
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
