#include <cppli_impl/flag.hpp>

#include <stdexcept>

using namespace std;

namespace cppli {

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

namespace detail {

FlagDetails::FlagDetails():
        ChoiceArgumentDetails<bool>({
            {"1", true}, {"true", true}, {"TRUE", true},
            {"enabled", true}, {"ENABLED", true},

            {"0", false}, {"false", false}, {"FALSE", false},
            {"disabled", false}, {"DISABLED", false}
        }, false, true) {}

bool FlagDetails::eatsPositionalArgument() const {
    return false;
}

}  // namespace detail
}  // namespace cppli
