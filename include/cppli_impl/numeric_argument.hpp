#ifndef CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_
#define CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_

#include <string>
#include <type_traits>

#include <cppli_impl/command_line_spec.hpp>

namespace cppli {

template<class T, class=typename std::enable_if<std::is_arithmetic<T>::value>::type>
class NumericArgument: public CommandLineSpec {
 public:
    ~NumericArgument() override = default;

    T get() const {
        return value;
    }

 private:
    NumericArgument(T _defaultValue, T _implicitValue):
            defaultValue(_defaultValue), implicitValue(_implicitValue) {}

    void setDefault() override {
        value = defaultValue;
    }

    void setImplicit() override {
        value = implicitValue;
    }

    bool supportsValue() const override {
        return true;
    }

    void setValue(const std::string& _value) override;

    T value;
    T defaultValue;
    T implicitValue;

friend class Cppli;
};

template<> void NumericArgument<int>::setValue(const std::string& _value);

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

}

#endif
