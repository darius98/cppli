#include <kktest.hpp>
#include <kktest_ext/matchers/comparison.hpp>
#include <kktest_ext/matchers/functional.hpp>
#include <kktest_ext/matchers/truth.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::matchers;
using namespace std;

void flagTest() {
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

    test("Passing a flag value 'enabled' enables it", [&] {
        cppli.interpret({"--flag_a=enabled"});
        expect(a.get(), isTrue);
    });

    test("Passing a flag random values throws", [&] {
        expect([&] {
            cppli.interpret({"--flag_a=whatever"});
        }, throwsA<invalid_argument>());
    });

    test("Single dash flag does not associate with the following "
         "positional argument", [&] {
        auto positional = cppli.interpret({"-a", "enabled"});
        expect(positional, isEqualTo(vector<string>{"enabled"}));
        expect(a.get(), isTrue);
    });
}