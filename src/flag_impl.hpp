#ifndef CPPLI_SRC_FLAG_IMPL_HPP_
#define CPPLI_SRC_FLAG_IMPL_HPP_

#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/flag.hpp>

namespace cppli {

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

}

#endif
