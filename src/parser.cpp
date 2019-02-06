#include <iostream>

#include <cppli_impl/parser.hpp>

using namespace std;

namespace cppli {

using namespace detail;

Parser::Parser(const string& _helpPrefix): helpPrefix(_helpPrefix + "\n") {}

Parser::~Parser() {
    for (CommandLineSpec* spec : commandLineSpecs) {
        delete spec;
    }
}

Argument Parser::addArgument(const ArgumentSpec& builder) {
    checkNameAvailability(builder.name, builder.shortName);
    auto spec = new ArgumentDetails(builder.defaultValue,
                                    builder.implicitValue);
    addSpec(spec, builder.name, builder.shortName);
    string extra;
    if (!builder.defaultValue.empty() || !builder.implicitValue.empty()) {
        extra = "\t\tDefault: '"
                + builder.defaultValue
                + "', Implicit: '"
                + builder.implicitValue
                + "'";
    }
    addHelp(builder.helpGroup,
            builder.name,
            builder.shortName,
            builder.description,
            extra);
    return Argument(spec);
}

Flag Parser::addFlag(const FlagSpec& builder) {
    checkNameAvailability(builder.name, builder.shortName);
    auto spec = new FlagDetails();
    addSpec(spec, builder.name, builder.shortName);
    addHelp(builder.helpGroup,
            builder.name,
            builder.shortName,
            "(Flag)\t" + builder.description,
            "");
    return Flag(spec);
}

void Parser::addTerminalFlag(const FlagSpec& builder,
                            const function<void()>& callback) {
    terminalFlags.emplace_back(addFlag(builder), callback);
}

void Parser::addTerminalFlag(const FlagSpec& builder,
                            const string& message) {
    terminalFlags.emplace_back(addFlag(builder), [message] {
        cout << message;
    });
}

void Parser::addHelpFlag() {
    addTerminalFlag(FlagSpec("help")
                    .setShortName("h")
                    .setDescription("Display this help menu."),
                    [&]() {
        cout << renderHelp();
    });
}

Parser::ArgList Parser::interpret(const ArgList& args) {
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

    for (const pair<Flag, function<void()>>& flag: terminalFlags) {
        if (flag.first.get()) {
            flag.second();
            exit(0);
        }
    }

    return positionalArguments;
}

Parser::ArgList Parser::interpret(int argc, char** argv) {
    ArgList args(static_cast<size_t>(argc));
    for (int i = 0; i < argc; ++ i) {
        args.emplace_back(argv[i]);
    }
    return interpret(args);
}

void Parser::addHelp(const string& helpGroup,
                    const string& name,
                    const string& shortName,
                    const string& description,
                    const string& extra) {
    string helpLine = "\t--" + name;
    if (!shortName.empty()) {
        helpLine += ",-" + shortName;
    }
    helpLine += "\t" + description;
    if (!extra.empty()) {
        helpLine += "\n" + extra;
    }

    if (helpGroup.empty()) {
        helpPrefix += "\n" + helpLine;
        return;
    }

    bool foundHelpGroup = false;
    for (HelpGroup& group : helpSections) {
        if (group.groupName == helpGroup) {
            foundHelpGroup = true;
            group.content += helpLine + "\n";
            break;
        }
    }
    if (!foundHelpGroup) {
        helpSections.push_back({helpGroup, helpGroup + "\n" + helpLine + "\n"});
    }
}

string Parser::renderHelp() const {
    string help = helpPrefix + "\n";
    for (const HelpGroup& group : helpSections) {
        help += "\n" + group.content;
    }
    return help;
}

void Parser::addSpec(CommandLineSpec* spec,
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

void Parser::checkNameAvailability(const string& name,
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

bool Parser::shouldApplyValue(const string& commandLineString) const {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    return specIterator != specsByCommandLineString.end()
           && specIterator->second->eatsPositionalArgument();
}

void Parser::applyValue(const string& commandLineString,
                       const string& value) {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    if (specIterator != specsByCommandLineString.end()) {
        specIterator->second->setValue(value);
    }
}

void Parser::applyImplicit(const string& commandLineString) {
    auto specIterator = specsByCommandLineString.find(commandLineString);
    if (specIterator != specsByCommandLineString.end()) {
        specIterator->second->setImplicit();
    }
}

template<>
string Parser::toString(const string& value) {
    return value;
}

}  // namespace cppli
