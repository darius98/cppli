#include <kktest.hpp>
#include <kktest_ext/matchers/comparison.hpp>
#include <kktest_ext/matchers/functional.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::matchers;
using namespace std;

void choiceArgumentTest() {
    Parser cppli("");

    setUp([&] {
        cppli = Parser("");
    });

    test("String choice argument, setting valid value", [&] {
        auto arg = cppli.addChoiceArgument(ChoiceArgumentSpec<string>("name")
                                           .addOption("value", "value"));
        cppli.interpret({"--name=value"});
        expect(arg.get(), isEqualTo("value"));
    });

    test("String choice argument, setting invalid value throws", [&] {
        cppli.addChoiceArgument(ChoiceArgumentSpec<string>("name")
                                .addOption("value", "value"));
        expect([&] {
            cppli.interpret({"--name=other"});
        }, throwsA<invalid_argument>());
    });

    test("Argument with multiple choices, mapping to the same value", [&] {
        auto arg = cppli.addChoiceArgument(ChoiceArgumentSpec<string>("name")
                                           .addOption("key1", "value")
                                           .addOption("key2", "value"));

        cppli.interpret({"--name=key1"});
        expect(arg.get(), isEqualTo("value"));

        cppli.interpret({"--name=key2"});
        expect(arg.get(), isEqualTo("value"));
    });

    test("Argument that maps to integers", [&] {
        auto arg = cppli.addChoiceArgument(ChoiceArgumentSpec<int>("name")
                                           .addOption("1", 1)
                                           .addOption("ONE", 1));
        cppli.interpret({"--name=1"});
        expect(arg.get(), isEqualTo(1));

        cppli.interpret({"--name=ONE"});
        expect(arg.get(), isEqualTo(1));
    });

    test("ArgumentSpec options manipulation", [&] {
        ChoiceArgumentSpec<int> spec("name");

        expect(spec.options, isEqualTo(map<string, int>{}));

        spec.addOption("key", 1).addOption("key2", 2);
        expect(spec.options, isEqualTo(map<string, int>{
            {"key", 1},
            {"key2", 2}
        }));

        spec.addOptions({{"key", 3}, {"key3", 4}});
        expect(spec.options, isEqualTo(map<string, int>{
            {"key", 3},
            {"key2", 2},
            {"key3", 4}
        }));

        spec.setOptions({{"k", 12}, {"l", 14}});
        expect(spec.options, isEqualTo(map<string, int>{
            {"k", 12},
            {"l", 14}
        }));

    });
}
