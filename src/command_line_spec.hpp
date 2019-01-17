#ifndef CPPLI_SRC_COMMAND_LINE_SPEC_H_
#define CPPLI_SRC_COMMAND_LINE_SPEC_H_

#include <string>

namespace cppli {

class CommandLineSpec {
 public:
    virtual ~CommandLineSpec() = default;

    virtual void setDefault() = 0;

    virtual void setImplicit() = 0;

    virtual void setValue(const std::string& _value) = 0;
};

}

#endif
