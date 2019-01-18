#ifndef CPPLI_IMPL_ARGUMENT_H_
#define CPPLI_IMPL_ARGUMENT_H_

#include <string>

namespace cppli {

template<class T>
class GenericArgument {
 public:
    virtual ~GenericArgument() = default;

    virtual T get() const = 0;
};

struct GenericArgumentSpec {
    GenericArgumentSpec(std::string _name, std::string _helpText):
            name(std::move(_name)), helpText(std::move(_helpText)) {}

    virtual GenericArgumentSpec& withShortName(const std::string& _shortName) {
        shortName = _shortName;
        return *this;
    }

    std::string name;
    std::string helpText;
    std::string shortName;
};

template<class T>
struct DefaultImplicitValueSpec: public GenericArgumentSpec {
    using GenericArgumentSpec::GenericArgumentSpec;

    DefaultImplicitValueSpec& withShortName(const std::string& _shortName) override {
        shortName = _shortName;
        return *this;
    }

    DefaultImplicitValueSpec& withDefaultValue(const T& _defaultValue) {
        defaultValue = _defaultValue;
        return *this;
    }

    DefaultImplicitValueSpec& withImplicitValue(const T& _implicitValue) {
        implicitValue = _implicitValue;
        return *this;
    }

    T defaultValue;
    T implicitValue;
};

typedef GenericArgument<std::string> Argument;
typedef DefaultImplicitValueSpec<std::string> ArgumentSpec;

typedef GenericArgument<bool> Flag;
typedef GenericArgumentSpec FlagSpec;

typedef GenericArgument<int> IntArgument;
typedef DefaultImplicitValueSpec<int> IntArgumentSpec;

}

#endif
