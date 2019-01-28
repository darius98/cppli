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

FlagDetails::FlagDetails() = default;

FlagDetails::~FlagDetails() = default;

bool FlagDetails::get() const {
    return value;
}

void FlagDetails::setDefault() {
    value = false;
}

void FlagDetails::setImplicit() {
    value = true;
}

bool FlagDetails::supportsValue() const {
    return false;
}

void FlagDetails::setValue(const string& _value) {
    throw invalid_argument("Tried to give value `" + _value + "` to a flag!");
}

bool FlagDetails::appeared() const {
    // A flag appears iff it is set to TRUE.
    return value;
}

NullableFlagDetails::NullableFlagDetails() = default;

NullableFlagDetails::~NullableFlagDetails() = default;

bool NullableFlagDetails::get() const {
    return value == True;
}

void NullableFlagDetails::setDefault() {
    value = Null;
}

void NullableFlagDetails::setImplicit() {
    value = True;
}

bool NullableFlagDetails::supportsValue() const {
    return true;
}

void NullableFlagDetails::setValue(const string& _value) {
    value = (_value == "1"
             || _value == "true"
             || _value == "enabled"
             || _value == "TRUE"
             || _value == "ENABLED") ? True : False;
}

bool NullableFlagDetails::appeared() const {
    return value != Null;
}

}  // namespace detail
}  // namespace cppli
