#include <kktest.hpp>
#include <kktest_ext/core_matchers.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::core_matchers;
using namespace std;

void kkTestCase(CppliFlag) {
    Parser cppli("");
    Flag a;
    Flag b;

    setUp([&] {
        cppli = Parser("");
        a = cppli.addFlag(FlagSpec("flag_a").setShortName("a"));
        b = cppli.addFlag(FlagSpec("flag_b").setShortName("b"));
    });

    test("Default flag value is false", [&] {
        expect(a.get(), isFalse);
        expect(b.get(), isFalse);
    });

    test("Implicit flag value is true", [&] {
        cppli.interpret({"--flag_a"});
        expect(a.get(), isTrue);
        expect(b.get(), isFalse);

        cppli.interpret({"--a"});
        expect(a.get(), isTrue);
        expect(b.get(), isFalse);

        cppli.interpret({"-ab", "-a"});
        expect(a.get(), isTrue);
        expect(b.get(), isTrue);
    });

    test("Passing a flag values throws", [&] {
        expect([&] {
            cppli.interpret({"--flag_a=enabled"});
        }, throwsA<invalid_argument>());
    });

    test("Single dash flag does not associate with the following "
         "positional argument", [&] {
        auto positional = cppli.interpret({"-a", "enabled"});
        expect(positional, isEqualTo(vector<string>{"enabled"}));
        expect(a.get(), isTrue);
    });
}