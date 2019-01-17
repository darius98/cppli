#ifndef CPPLI_SRC_CPPLI_IMPL_H_
#define CPPLI_SRC_CPPLI_IMPL_H_

#include <map>
#include <set>
#include <vector>

#include <cppli_impl/cppli_interface.hpp>
#include "command_line_spec.hpp"

namespace cppli {

class CppliImpl: public Cppli {
 public:
    explicit CppliImpl(std::string helpPrefix);

    ~CppliImpl() override;

    Argument* addArgument(const ArgumentBuilder& builder) override;

    IntArgument* addIntArgument(const IntArgumentBuilder& builder) override;

    Flag* addFlag(const FlagBuilder& builder) override;

    std::vector<std::string> interpret(const std::vector<std::string>& args) override;

    void addHelpFlag() override;

    void checkHelpFlag() override;

 private:
    void addSpec(CommandLineSpec* spec,
                 const std::string& name,
                 const std::string& helpText,
                 const std::string& shortName,
                 const std::string& defaultValue,
                 const std::string& implicitValue);

    void checkNameAvailability(const std::string& name,
                               const std::string& shortName) const;

    void applyValue(const std::string& commandLineString, const std::string& value);

    void applyImplicit(const std::string& commandLineString);

    Flag* helpFlag = nullptr;

    std::vector<CommandLineSpec*> commandLineSpecs;
    std::map<std::string, CommandLineSpec*> specsByCommandLineString;

    std::string help;
    std::set<std::string> reservedNames;
};

}

#endif
