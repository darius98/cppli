#ifndef CPPLI_IMPL_CPPLI_HPP_
#define CPPLI_IMPL_CPPLI_HPP_

#include <map>
#include <set>
#include <string>
#include <vector>

#include <cppli_impl/argument.hpp>
#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/numeric_argument.hpp>

namespace cppli {

class Cppli {
 public:
    typedef std::vector<std::string> ArgList;

    explicit Cppli(const std::string& _helpPrefix);

    ~Cppli();

    Argument* addArgument(const ArgumentSpec& builder);

    IntArgument* addIntArgument(const IntArgumentSpec& builder);

    Flag* addFlag(const FlagSpec& builder);

    ArgList interpret(const ArgList& argv);

    ArgList interpret(int argc, char** argv);

    void addHelpFlag();

    void checkHelpFlag();

    // Only public for testing.
    std::string renderHelp() const;

 private:
    struct HelpGroup {
        std::string groupName;
        std::string content;
    };

    void addHelp(const std::string& helpGroup,
                 const std::string& name,
                 const std::string& shortName,
                 const std::string& description,
                 const std::string& extra);

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
