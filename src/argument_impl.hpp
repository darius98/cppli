#ifndef CPPLI_SRC_ARGUMENT_IMPL_HPP_
#define CPPLI_SRC_ARGUMENT_IMPL_HPP_

#include <cppli_impl/argument.hpp>
#include "command_line_spec.hpp"

namespace cppli {

template<class T>
class GenericArgumentImpl: public GenericArgument<T>, public CommandLineSpec {
 public:
    GenericArgumentImpl(const T& _defaultValue, const T& _implicitValue):
            value(_defaultValue),
            defaultValue(_defaultValue),
            implicitValue(_implicitValue) {}

    ~GenericArgumentImpl() override = default;

    T get() const override {
        return value;
    }

    void setDefault() override {
        value = defaultValue;
    }

    void setImplicit() override {
        value = implicitValue;
    }

 protected:
    T value;
    T defaultValue;
    T implicitValue;
};

class ArgumentImpl: public GenericArgumentImpl<std::string> {
 public:
    ArgumentImpl(const std::string& defaultValue, std::string implicitValue);

    ~ArgumentImpl() override;

    void setValue(const std::string& _value) override;
};

class FlagImpl: public GenericArgumentImpl<bool> {
 public:
    FlagImpl();

    ~FlagImpl() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;
};

class IntArgumentImpl: public GenericArgumentImpl<int> {
 public:
    IntArgumentImpl(int defaultValue, int implicitValue);

    ~IntArgumentImpl() override;

    void setValue(const std::string& _value) override;
};

}

#endif
