#include <cppli_impl/flag.hpp>

using namespace std;

namespace cppli {

Flag::~Flag() = default;

FlagSpec::FlagSpec(string _name): name(move(_name)) {}

FlagSpec& FlagSpec::setDescription(const string& _helpText) {
    helpText = _helpText;
    return *this;
}

FlagSpec& FlagSpec::setShortName(const string& _shortName) {
    shortName = _shortName;
    return *this;
}

}
