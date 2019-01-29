#ifndef CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_
#define CPPLI_IMPL_NUMERIC_ARGUMENT_HPP_

#include <string>
#include <type_traits>

#include <cppli_impl/accessor.hpp>
#include <cppli_impl/command_line_spec.hpp>

namespace cppli {

// Forward declaration so I can declare the accessor.
namespace detail {
template<class T, class=typename std::enable_if<std::is_arithmetic<T>::value>::type>
class NumericArgumentDetails;
}

template<class T>
using NumericArgument = detail::Accessor<detail::NumericArgumentDetails<T>>;

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

namespace detail {

template<class T, class>
class NumericArgumentDetails: public CommandLineSpec {
 public:
    NumericArgumentDetails(T _defaultValue, T _implicitValue):
            defaultValue(_defaultValue), implicitValue(_implicitValue) {}

    ~NumericArgumentDetails() override = default;

    T get() const {
        return value;
    }

    void setDefault() override {
        value = defaultValue;
        appearedInArgs = false;
    }

    void setImplicit() override {
        value = implicitValue;
        appearedInArgs = true;
    }

    bool supportsValue() const override {
        return true;
    }

    void setValue(const std::string& _value) override;

    bool appeared() const {
        return appearedInArgs;
    }

 private:
    T value;
    T defaultValue;
    T implicitValue;
    bool appearedInArgs = false;
};

template<>
void NumericArgumentDetails<char>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<unsigned char>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<short int>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<unsigned short int>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<int>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<unsigned int>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<long>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<unsigned long>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<long long>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<unsigned long long>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<float>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<double>::setValue(const std::string& _value);

template<>
void NumericArgumentDetails<long double>::setValue(const std::string& _value);

}  // namespace detail
}  // namespace cppli

#endif
