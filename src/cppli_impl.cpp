#include <iostream>
#include <stdexcept>

#include "cppli_impl.hpp"
#include "argument_impl.hpp"

using namespace std;

namespace cppli {

CppliImpl::CppliImpl(const string& _helpPrefix):
        helpPrefix(_helpPrefix + "\n") {}

CppliImpl::~CppliImpl() {
    for (CommandLineSpec* spec : commandLineSpecs) {
        delete spec;
    }
}

Argument* CppliImpl::addArgument(const ArgumentSpec& builder) {
    checkNameAvailability(builder.name, builder.shortName);
    auto spec = new ArgumentImpl(builder.defaultValue, builder.implicitValue);
    addSpec(spec, builder.name, builder.shortName);
    addHelp(builder.helpGroup,
            builder.name,
            builder.shortName,
            builder.description,
            "\t\tDefault: '"
                + builder.defaultValue
                + "', Implicit: '"
                + builder.implicitValue
                + "'\n");
    return spec;
}

IntArgument* CppliImpl::addIntArgument(const IntArgumentSpec& builder) {
    checkNameAvailability(builder.name, builder.shortName);
    auto spec = new IntArgumentImpl(builder.defaultValue,
                                    builder.implicitValue);
    addSpec(spec, builder.name, builder.shortName);
    addHelp(builder.helpGroup,
            builder.name,
            builder.shortName,
            builder.description,
            "\t\tDefault: '"
            + to_string(builder.defaultValue)
            + "', Implicit: '"
            + to_string(builder.implicitValue)
            + "'\n");
    return spec;
}

Flag* CppliImpl::addFlag(const FlagSpec& builder) {
    checkNameAvailability(builder.name, builder.shortName);
    auto spec = new FlagImpl();
    addSpec(spec, builder.name, builder.shortName);
    addHelp(builder.helpGroup,
            builder.name,
            builder.shortName,
            builder.description,
            "\t\tFlag <default: false, implicit: true>"
                "does not accept explicit values)");
    return spec;
}

CppliImpl::ArgList CppliImpl::interpret(const ArgList& args) {
    for (CommandLineSpec* spec : commandLineSpecs) {
        spec->setDefault();
    }

    ArgList positionalArguments;
    string lastShortName;
    bool onlyPositional = false;
    for (const string& arg: args) {
        // on encountering the "--" argument, all arguments from that point on
        // are considered positional.
        if (arg == "--") {
            onlyPositional = true;
            continue;
        }

        // all arguments after "--" are considered positional.
        if (onlyPositional) {
            positionalArguments.push_back(arg);
            continue;
        }

        // an argument that does not start with '-' (or is equal to "-") is not
        // considered special, and therefore will be treated like either a
        // positional argument or a value filler for the last unfulfilled short
        // name argument given in the format "-XYZ".
        if (arg.substr(0, 1) != "-" || arg == "-") {
            if (shouldApplyValue(lastShortName)) {
                // `lastShortName` is an unfulfilled argument given by short
                // name in the format "-XYZ v" as "Z".
                applyValue(lastShortName, arg);
                lastShortName = "";
            } else {
                // no unfulfilled argument given by short name, considering a
                // positional argument.
                positionalArguments.push_back(arg);
            }
            continue;
        }

        // if we reached this point without hitting a `continue`, now the
        // current argument is definitely a special one.

        // if we had an unfulfilled argument given by short name, we will give
        // it its implicit value since it won't be fulfilled by this argument.
        if (!lastShortName.empty()) {
            applyImplicit(lastShortName);
            lastShortName = "";
        }

        auto equalPos = arg.find('=');

        // 1. for "--X", give argument "X" its implicit value
        if (arg.substr(0, 2) == "--" && equalPos == string::npos) {
            applyImplicit(arg.substr(2));
        }

        // 2. for "--X=v", give argument "X" value "v"
        if (arg.substr(0, 2) == "--" && equalPos != string::npos) {
            applyValue(arg.substr(2, equalPos - 2), arg.substr(equalPos + 1));
        }

        // 3. for "-XYZ", give arguments "X" and "Y" their implicit values, and
        // remember "Z" as the last short name, as a construct of the form
        // "-XYZ v" is allowed, equivalent with "--X --Y --Z=v".
        if (arg.substr(0, 2) != "--" && equalPos == string::npos) {
            for (size_t j = 1; j + 1 < arg.length(); ++j) {
                applyImplicit(arg.substr(j, 1));
            }
            lastShortName = arg.substr(arg.length() - 1, 1);
        }

        // 4. for "-XYZ=v", give arguments "X" and "Y" their implicit values and
        // argument "Z" value "v".
        if (arg.substr(0, 2) != "--" && equalPos != string::npos) {
            for (size_t j = 1; j + 1 < equalPos; ++j) {
                applyImplicit(arg.substr(j, 1));
            }
            applyValue(arg.substr(equalPos - 1, 1), arg.substr(equalPos + 1));
        }
    }
    if (!lastShortName.empty()) {
        applyImplicit(lastShortName);
    }
    return positionalArguments;
}

void CppliImpl::addHelpFlag() {
    helpFlag = addFlag(FlagSpec("help")
                       .setDescription("Display this help menu.")
                       .setShortName("h"));
}

void CppliImpl::checkHelpFlag() {
    if (helpFlag != nullptr && helpFlag->get()) {
        cout << renderHelp() << "\n";
        exit(0);
    }
}

void CppliImpl::addHelp(const string& helpGroup,
                        const string& name,
                        const string& shortName,
                        const string& description,
                        const string& extra) {
    string helpLine = "\n\t--" + name;
    if (!shortName.empty()) {
        helpLine += ",-" + shortName;
    }
    helpLine += "\t" + description + "\n";
    helpLine += extra;

    if (helpGroup.empty()) {
        helpPrefix += helpLine;
    }

    bool foundHelpGroup = false;
    for (HelpGroup& group : helpSections) {
        if (group.groupName == helpGroup) {
            foundHelpGroup = true;
            group.content += helpLine;
            break;
        }
    }
    if (!foundHelpGroup) {
        helpSections.push_back({helpGroup, helpGroup + "\n"});
    }
}

string CppliImpl::renderHelp() const {
    string help = helpPrefix + "\n";
    for (const HelpGroup& group : helpSections) {
        help += "\n" + group.content;
    }
    return help;
}

void CppliImpl::addSpec(CommandLineSpec* spec,
                        const string& name,
                        const string& shortName) {
    commandLineSpecs.push_back(spec);
    reservedNames.insert(name);
    specsByCommandLineString[name] = spec;
    if (!shortName.empty()) {
        reservedNames.insert(shortName);
        specsByCommandLineString[shortName] = spec;
    }
}

void CppliImpl::checkNameAvailability(const string& name,
                                      const string& shortName) const {
    if (reservedNames.count(name) != 0) {
        throw runtime_error(
            "Argument tried to register " + name + " as a command-line name, "
            "but a different argument already has it as a name.");
    }
    if (!shortName.empty() && reservedNames.count(shortName) != 0) {
        throw runtime_error(
            "Argument tried to register " + shortName + " as a command-line "
            "short name, but a different argument already has it as a short "
            "name.");
    }
    if (shortName.size() > 1) {
        throw runtime_error("Argument short name should always have length 1.");
    }
}

bool CppliImpl::shouldApplyValue(const string& commandLineString) const {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    return specIterator != specsByCommandLineString.end()
           && specIterator->second->supportsValue();
}

void CppliImpl::applyValue(const string& commandLineString,
                           const string& value) {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    if (specIterator != specsByCommandLineString.end()) {
        specIterator->second->setValue(value);
    }
}

void CppliImpl::applyImplicit(const string& commandLineString) {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    if (specIterator != specsByCommandLineString.end()) {
        specIterator->second->setImplicit();
    }
}

}
