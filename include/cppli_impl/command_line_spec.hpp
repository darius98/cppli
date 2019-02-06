#ifndef CPPLI_IMPL_COMMAND_LINE_SPEC_HPP_
#define CPPLI_IMPL_COMMAND_LINE_SPEC_HPP_

#include <string>

namespace cppli {
namespace detail {

class CommandLineSpec {
 public:
    virtual ~CommandLineSpec() = default;

    virtual bool eatsPositionalArgument() const = 0;

    virtual void setDefault() = 0;

    virtual void setImplicit() = 0;

    virtual void setValue(const std::string& _value) = 0;
};

}  // namespace detail
}  // namespace cppli

#endif
