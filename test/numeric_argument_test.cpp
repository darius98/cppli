#include <kktest.hpp>
#include <kktest_ext/matchers.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::matchers;
using namespace std;

void numericArgumentTest() {
    Parser cppli("");

    setUp([&] {
        cppli = Parser("");
    });

    test("Passing a NumericArgument<int> an integer value works", [&] {
        auto arg = cppli.addNumericArgument(NumericArgumentSpec<int>("name"));

        cppli.interpret({"--name=17"});
        expect(arg.get(), isEqualTo(17));

        cppli.interpret({"--name=-7"});
        expect(arg.get(), isEqualTo(-7));

        cppli.interpret({"--name=1337"});
        expect(arg.get(), isEqualTo(1337));
    });

    test("Passing a NumericArgument<int> a non-integer value throws", [&] {
        cppli.addNumericArgument(NumericArgumentSpec<int>("name"));
        expect([&] {
            cppli.interpret({"--name=invalid"});
        }, throwsA<invalid_argument>());
    });

    test("Passing a NumericArgument<int> a negative value works", [&] {
        auto arg = cppli.addNumericArgument(NumericArgumentSpec<int>("name"));
        cppli.interpret({"--name=-1337"});
        expect(arg.get(), isEqualTo(-1337));
    });

    test("Passing a NumericArgument<long long> a 64-bit integer value works",
         [&] {
        auto arg = cppli.addNumericArgument(
                NumericArgumentSpec<long long>("name"));
        cppli.interpret({"--name=12345678912345"});
        expect(arg.get(), isEqualTo(12345678912345LL));
    });
}
