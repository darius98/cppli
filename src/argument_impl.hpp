#ifndef CPPLI_SRC_ARGUMENT_IMPL_HPP_
#define CPPLI_SRC_ARGUMENT_IMPL_HPP_

#include <cppli_impl/argument.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/int_argument.hpp>
#include "command_line_spec.hpp"

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

class IntArgumentImpl: public IntArgument, public CommandLineSpec {
 public:
    IntArgumentImpl(int _defaultValue, int _implicitValue);

    ~IntArgumentImpl() override;

    int get() const override;

    void setDefault() override;

    void setImplicit() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;

 private:
    int value;
    int defaultValue;
    int implicitValue;
};

}

#endif
