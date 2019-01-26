#ifndef CPPLI_SRC_ARGUMENT_IMPL_HPP_
#define CPPLI_SRC_ARGUMENT_IMPL_HPP_

#include <cppli_impl/argument.hpp>
#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/numeric_argument.hpp>

namespace cppli {

class ArgumentImpl: public Argument, public CommandLineSpec {
 public:
    ArgumentImpl(std::string _defaultValue, std::string _implicitValue);

    ~ArgumentImpl() override;

    std::string get() const override;

    void setDefault() override;

    void setImplicit() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;

 private:
    std::string value;
    std::string defaultValue;
    std::string implicitValue;
};

class FlagImpl: public Flag, public CommandLineSpec {
 public:
    FlagImpl();

    ~FlagImpl() override;

    bool get() const override;

    void setDefault() override;

    void setImplicit() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;

 private:
    bool value;
};

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
