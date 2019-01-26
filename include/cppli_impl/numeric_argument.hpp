#ifndef CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_
#define CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_

#include <string>
#include <type_traits>

#include <cppli_impl/accessor.hpp>
#include <cppli_impl/command_line_spec.hpp>

namespace cppli {

template<class T, class=typename std::enable_if<std::is_arithmetic<T>::value>::type>
class NumericArgument: public CommandLineSpec {
 public:
    NumericArgument(T _defaultValue, T _implicitValue):
            defaultValue(_defaultValue), implicitValue(_implicitValue) {}

    ~NumericArgument() override = default;

    T get() const {
        return value;
    }

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

 private:
    T value;
    T defaultValue;
    T implicitValue;
};

template<>
void NumericArgument<char>::setValue(const std::string& _value);

template<>
void NumericArgument<unsigned char>::setValue(const std::string& _value);

template<>
void NumericArgument<short int>::setValue(const std::string& _value);

template<>
void NumericArgument<unsigned short int>::setValue(const std::string& _value);

template<>
void NumericArgument<int>::setValue(const std::string& _value);

template<>
void NumericArgument<unsigned int>::setValue(const std::string& _value);

template<>
void NumericArgument<long>::setValue(const std::string& _value);

template<>
void NumericArgument<unsigned long>::setValue(const std::string& _value);

template<>
void NumericArgument<long long>::setValue(const std::string& _value);

template<>
void NumericArgument<unsigned long long>::setValue(const std::string& _value);

template<>
void NumericArgument<float>::setValue(const std::string& _value);

template<>
void NumericArgument<double>::setValue(const std::string& _value);

template<>
void NumericArgument<long double>::setValue(const std::string& _value);

template<class T>
using NumericArgumentAccessor = Accessor<NumericArgument<T>>;

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
