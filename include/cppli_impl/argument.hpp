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

template<class T>
struct GenericArgumentBuilder {
    GenericArgumentBuilder(std::string _name, std::string _helpText):
            name(std::move(_name)), helpText(std::move(_helpText)) {}

    GenericArgumentBuilder& withShortName(const std::string& _shortName) {
        shortName = _shortName;
        return *this;
    }

    GenericArgumentBuilder& withDefaultValue(const T& _defaultValue) {
        defaultValue = _defaultValue;
        return *this;
    }

    GenericArgumentBuilder& withImplicitValue(const T& _implicitValue) {
        implicitValue = _implicitValue;
        return *this;
    }

    std::string name;
    std::string helpText;
    std::string shortName;
    T defaultValue;
    T implicitValue;
};

typedef GenericArgument<std::string> Argument;
typedef GenericArgumentBuilder<std::string> ArgumentBuilder;

typedef GenericArgument<bool> Flag;
typedef GenericArgumentBuilder<bool> FlagBuilder;

typedef GenericArgument<int> IntArgument;
typedef GenericArgumentBuilder<int> IntArgumentBuilder;

}

#endif
