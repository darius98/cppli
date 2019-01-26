#ifndef CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_
#define CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_

#include <string>
#include <type_traits>

namespace cppli {

template<class T, class=typename std::enable_if<std::is_arithmetic<T>::value>::type>
class NumericArgument {
 public:
    virtual ~NumericArgument() = default;

    virtual T get() const = 0;
};

template<class T, class=typename std::enable_if<std::is_arithmetic<T>::value>::type>
struct NumericArgumentSpec {
    explicit NumericArgumentSpec(std::string _name): name(std::move(_name)) {}

    NumericArgumentSpec& setDescription(const std::string& _description) {
        description = _description;
        return *this;
    }

    NumericArgumentSpec& setHelpGroup(const std::string& _helpGroup) {
        helpGroup = _helpGroup;
        return *this;
    }

    NumericArgumentSpec& setShortName(const std::string& _shortName) {
        shortName = _shortName;
        return *this;
    }

    NumericArgumentSpec& setDefaultValue(T _defaultValue) {
        defaultValue = _defaultValue;
        return *this;
    }

    NumericArgumentSpec& setImplicitValue(T _implicitValue) {
        implicitValue = _implicitValue;
        return *this;
    }

    std::string name;
    std::string description = "";
    std::string helpGroup = "";
    std::string shortName = "";
    T defaultValue = 0;
    T implicitValue = 0;
};

typedef NumericArgument<int> IntArgument;
typedef NumericArgumentSpec<int> IntArgumentSpec;

}

#endif
