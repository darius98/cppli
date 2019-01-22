#ifndef CPPLI_IMPL_CPPLI_INTERFACE_H_
#define CPPLI_IMPL_CPPLI_INTERFACE_H_

#include <string>
#include <vector>

#include <cppli_impl/argument.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/int_argument.hpp>

namespace cppli {

class Cppli {
 public:
    typedef std::vector<std::string> ArgList;

    static Cppli* create(const std::string& helpPrefix);

    virtual ~Cppli() = default;

    virtual Argument* addArgument(const ArgumentSpec& builder) = 0;

    virtual IntArgument* addIntArgument(const IntArgumentSpec& builder) = 0;

    virtual Flag* addFlag(const FlagSpec& builder) = 0;

    virtual ArgList interpret(const ArgList& argv) = 0;

    ArgList interpret(int argc, char** argv);

    virtual void addHelpFlag() = 0;

    virtual void checkHelpFlag() = 0;
};

}

#endif
