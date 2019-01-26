#ifndef CPPLI_SRC_ARGUMENT_IMPL_HPP_
#define CPPLI_SRC_ARGUMENT_IMPL_HPP_

#include <cppli_impl/argument.hpp>
#include <cppli_impl/command_line_spec.hpp>

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

}

#endif
