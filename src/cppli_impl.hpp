#ifndef CPPLI_SRC_CPPLI_IMPL_H_
#define CPPLI_SRC_CPPLI_IMPL_H_

#include <map>
#include <set>
#include <vector>

#include <cppli_impl/cppli_interface.hpp>
#include "command_line_spec.hpp"

namespace cppli {

struct HelpGroup {
    std::string groupName;
    std::string content;
};

class CppliImpl: public Cppli {
 public:
    explicit CppliImpl(const std::string& _helpPrefix);

    ~CppliImpl() override;

    Argument* addArgument(const ArgumentSpec& builder) override;

    IntArgument* addIntArgument(const IntArgumentSpec& builder) override;

    Flag* addFlag(const FlagSpec& builder) override;

    ArgList interpret(const ArgList& args) override;

    void addHelpFlag() override;

    void checkHelpFlag() override;

 private:
    void addHelp(const std::string& helpGroup,
                 const std::string& name,
                 const std::string& shortName,
                 const std::string& description,
                 const std::string& extra);

    std::string renderHelp() const;

    void addSpec(CommandLineSpec* spec,
                 const std::string& name,
                 const std::string& shortName);

    void checkNameAvailability(const std::string& name,
                               const std::string& shortName) const;

    bool shouldApplyValue(const std::string& commandLineString) const;

    void applyValue(const std::string& commandLineString,
                    const std::string& value);

    void applyImplicit(const std::string& commandLineString);

    Flag* helpFlag = nullptr;

    std::vector<CommandLineSpec*> commandLineSpecs;
    std::map<std::string, CommandLineSpec*> specsByCommandLineString;

    std::string helpPrefix;
    std::vector<HelpGroup> helpSections;

    std::set<std::string> reservedNames;
};

}

#endif
