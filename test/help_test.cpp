#include <iostream>
#include <vector>

#include <kktest.hpp>
#include <kktest_ext/matchers.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::matchers;
using namespace std;

void helpTest() {
    Parser cppli("");

    setUp([&] {
        cppli = Parser("Test help prefix.");
        cppli.addHelpFlag();
    });

    test("Only with the help flag", [&] {
        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
        ));
    });

    test("After adding another flag without help group", [&] {
        cppli.addFlag(FlagSpec("version")
                      .setDescription("Display program version")
                      .setShortName("v"));
        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
            "\t--version,-v\t(Flag)\tDisplay program version\n"
        ));
    });

    test("After adding an argument with default and implicit values", [&] {
        cppli.addArgument(ArgumentSpec("config")
                          .setDescription("File to take config from")
                          .setDefaultValue("/path/to/default-config.txt")
                          .setImplicitValue("./config.txt"));
        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
            "\t--config\tFile to take config from\n"
            "\t\tDefault: '/path/to/default-config.txt', Implicit: './config.txt'\n"
        ));
    });

    test("After adding argument within a group", [&] {
        cppli.addArgument(ArgumentSpec("config")
                          .setDescription("File to take config from")
                          .setHelpGroup("Config")
                          .setDefaultValue("/path/to/default-config.txt")
                          .setImplicitValue("./config.txt"));
        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
            "\n"
            "Config\n"
            "\t--config\tFile to take config from\n"
            "\t\tDefault: '/path/to/default-config.txt', Implicit: './config.txt'\n"
        ));
    });

    test("Arguments in a group are in the same order as they were added.", [&] {
        cppli.addArgument(ArgumentSpec("config")
                          .setDescription("File to take config from")
                          .setHelpGroup("Config")
                          .setDefaultValue("/path/to/default-config.txt")
                          .setImplicitValue("./config.txt"));
        cppli.addArgument(ArgumentSpec("json-config")
                          .setDescription("File to take JSON config from")
                          .setHelpGroup("Config")
                          .setDefaultValue("/path/to/default-config.json")
                          .setImplicitValue("./config.json"));

        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
            "\n"
            "Config\n"
            "\t--config\tFile to take config from\n"
            "\t\tDefault: '/path/to/default-config.txt', Implicit: './config.txt'\n"
            "\t--json-config\tFile to take JSON config from\n"
            "\t\tDefault: '/path/to/default-config.json', Implicit: './config.json'\n"
        ));
    });

    test("Groups are in the same order as their first arguments added", [&] {
        cppli.addArgument(ArgumentSpec("config")
                          .setDescription("File to take config from")
                          .setHelpGroup("Config")
                          .setDefaultValue("/path/to/default-config.txt")
                          .setImplicitValue("./config.txt"));

        cppli.addFlag(FlagSpec("version")
                      .setDescription("Display program version")
                      .setShortName("v"));

        cppli.addArgument(ArgumentSpec("interpreter")
                          .setDescription("Interpreter to use")
                          .setHelpGroup("Runtime")
                          .setShortName("I")
                          .setDefaultValue("python3")
                          .setImplicitValue("python3"));

        cppli.addNumericArgument(NumericArgumentSpec<int>("vm-heap")
                                 .setDescription("Interpreter VM max heap size")
                                 .setHelpGroup("Runtime")
                                 .setDefaultValue(1000)
                                 .setImplicitValue(1000));

        cppli.addArgument(ArgumentSpec("json-config")
                          .setDescription("File to take JSON config from")
                          .setHelpGroup("Config")
                          .setDefaultValue("/path/to/default-config.json")
                          .setImplicitValue("./config.json"));


        expect(cppli.renderHelp(), isEqualTo(
            "Test help prefix.\n"
            "\n"
            "\t--help,-h\t(Flag)\tDisplay this help menu.\n"
            "\t--version,-v\t(Flag)\tDisplay program version\n"
            "\n"
            "Config\n"
            "\t--config\tFile to take config from\n"
            "\t\tDefault: '/path/to/default-config.txt', Implicit: './config.txt'\n"
            "\t--json-config\tFile to take JSON config from\n"
            "\t\tDefault: '/path/to/default-config.json', Implicit: './config.json'\n"
            "\n"
            "Runtime\n"
            "\t--interpreter,-I\tInterpreter to use\n"
            "\t\tDefault: 'python3', Implicit: 'python3'\n"
            "\t--vm-heap\t(Number)\tInterpreter VM max heap size\n"
            "\t\tDefault: 1000, Implicit: 1000\n"
        ));
    });
}
