#ifndef CPPLI_SRC_NUMERIC_ARGUMENT_IMPL_HPP_
#define CPPLI_SRC_NUMERIC_ARGUMENT_IMPL_HPP_

#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/numeric_argument.hpp>

namespace cppli {

template<class T>
class NumericArgumentImpl: public NumericArgument<T>, public CommandLineSpec {
public:
    NumericArgumentImpl(T _defaultValue, T _implicitValue):
            defaultValue(_defaultValue), implicitValue(_implicitValue) {}

    ~NumericArgumentImpl() override = default;

    T get() const override {
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
void NumericArgumentImpl<int>::setValue(const std::string& _value) {
    value = std::stoi(_value);
}

typedef NumericArgumentImpl<int> IntArgumentImpl;

}

#endif
