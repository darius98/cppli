#include <cppli_impl/flag.hpp>

using namespace std;

namespace cppli {

Flag::~Flag() = default;

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
