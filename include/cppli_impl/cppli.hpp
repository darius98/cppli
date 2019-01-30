#ifndef CPPLI_IMPL_CPPLI_HPP_
#define CPPLI_IMPL_CPPLI_HPP_

#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <cppli_impl/argument.hpp>
#include <cppli_impl/choice_argument.hpp>
#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/flag.hpp>
#include <cppli_impl/numeric_argument.hpp>

namespace cppli {

class Cppli {
 public:
    typedef std::vector<std::string> ArgList;

    explicit Cppli(const std::string& _helpPrefix);

    ~Cppli();

    Argument addArgument(const ArgumentSpec& builder);

    template<class T>
    NumericArgument<T> addNumericArgument(
            const NumericArgumentSpec<T>& builder) {
        checkNameAvailability(builder.name, builder.shortName);
        auto spec = new detail::NumericArgumentDetails<T>(
                builder.defaultValue,
                builder.implicitValue);
        addSpec(spec, builder.name, builder.shortName);
        std::string extra;
        if (builder.defaultValue != 0 || builder.implicitValue != 0) {
            extra = "\t\tDefault: "
                    + toString(builder.defaultValue)
                    + ", Implicit: "
                    + toString(builder.implicitValue);
        }
        addHelp(builder.helpGroup,
                builder.name,
                builder.shortName,
                "(Number)\t" + builder.description,
                extra);
        return NumericArgument<T>(spec);
    }

    Flag addFlag(const FlagSpec& builder);

    NullableFlag addNullableFlag(const FlagSpec& builder);

    void addTerminalFlag(const FlagSpec& builder,
                         const std::function<void()>& callback);

    void addTerminalFlag(const FlagSpec& builder, const std::string& message);

    void addHelpFlag();

    template<class T>
    ChoiceArgument<T> addChoiceArgument(const ChoiceArgumentSpec<T>& builder) {
        checkNameAvailability(builder.name, builder.shortName);
        auto spec = new detail::ChoiceArgumentDetails<T>(
                builder.options,
                builder.defaultValue,
                builder.implicitValue);
        addSpec(spec, builder.name, builder.shortName);
        std::string renderedOptions;
        bool first = true;
        for (const std::pair<std::string, T>& option: builder.options) {
            if (!first) {
                renderedOptions += ",";
            }
            first = false;
            renderedOptions += "'" + option.first + "'";
        }
        addHelp(builder.helpGroup,
                builder.name,
                builder.shortName,
                builder.description,
                "\t\tDefault: "
                + toString(builder.defaultValue)
                + ", Implicit: "
                + toString(builder.implicitValue)
                + ", allowed values: [" + renderedOptions + "]");
        return ChoiceArgument<T>(spec);
    }

    ArgList interpret(const ArgList& argv);

    ArgList interpret(int argc, char** argv);

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

    void addSpec(detail::CommandLineSpec* spec,
                 const std::string& name,
                 const std::string& shortName);

    void checkNameAvailability(const std::string& name,
                               const std::string& shortName) const;

    bool shouldApplyValue(const std::string& commandLineString) const;

    void applyValue(const std::string& commandLineString,
                    const std::string& value);

    void applyImplicit(const std::string& commandLineString);

    template<class T>
    static std::string toString(const T& value) {
        return std::to_string(value);
    }

    std::vector<detail::CommandLineSpec*> commandLineSpecs;
    std::map<std::string, detail::CommandLineSpec*> specsByCommandLineString;

    std::string helpPrefix;
    std::vector<HelpGroup> helpSections;

    std::set<std::string> reservedNames;

    std::vector<std::pair<Flag, std::function<void()>>> terminalFlags;
};

template<>
std::string Cppli::toString(const std::string& value);

}  // namespace cppli

#endif
