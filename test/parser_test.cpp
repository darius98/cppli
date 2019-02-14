#include <kktest.hpp>
#include <kktest_ext/matchers.hpp>

#include <cppli.hpp>

using namespace cppli;
using namespace kktest;
using namespace kktest::matchers;
using namespace std;

void kkTestCase(Parser) {
    Parser cppli("");

    setUp([&] {
        cppli = Parser("Help prefix.");
    });

    group("Single argument", [&] {
        Argument arg;

        setUp([&] {
            arg = cppli.addArgument(ArgumentSpec("name")
                                    .setShortName("n")
                                    .setDefaultValue("a")
                                    .setImplicitValue("b"));
        });

        test("no value provided leads to argument taking default value", [&] {
            cppli.interpret({});
            expect(arg.get(), isEqualTo("a"));
        });

        test("provided with single dash, short name", [&] {
            cppli.interpret({"-n"});
            expect(arg.get(), isEqualTo("b"));
        });

        test("provided with double dash, short name", [&] {
            cppli.interpret({"--n"});
            expect(arg.get(), isEqualTo("b"));
        });

        test("provided with double dash, long name", [&] {
            cppli.interpret({"--name"});
            expect(arg.get(), isEqualTo("b"));
        });

        test("value provided with single dash & space", [&] {
            cppli.interpret({"-n", "v"});
            expect(arg.get(), isEqualTo("v"));
        });

        test("value provided with single dash & equal sign", [&] {
            cppli.interpret({"-n=v"});
            expect(arg.get(), isEqualTo("v"));
        });

        test("value provided with double dash & space is positional, while "
             "the argument takes implicit value", [&] {
            auto positionalArgs = cppli.interpret({"--name", "v"});
            expect(arg.get(), isEqualTo("b"));
            expect(positionalArgs, isEqualTo(vector<string>{"v"}));
        });

        test("value provided with double dash & equal sign (short name)", [&] {
            cppli.interpret({"--n=v"});
            expect(arg.get(), isEqualTo("v"));
        });

        test("value provided with double dash & equal sign (long name)", [&] {
            cppli.interpret({"--name=v"});
            expect(arg.get(), isEqualTo("v"));
        });

        test("providing value for different argument name does not influence"
             " interesting argument", [&] {
            cppli.interpret({"-m", "v"});
            expect(arg.get(), isEqualTo("a"));
        });

        test("when providing multiple values for one argument, it takes the "
             "last one", [&] {
            cppli.interpret({"-n", "v1", "-n", "--name=v2"});
            expect(arg.get(), isEqualTo("v2"));
        });
    });

    group("Multiple arguments", [&] {
        Argument a;
        Argument b;
        Argument c;

        setUp([&] {
            a = cppli.addArgument(ArgumentSpec("arg_a")
                                  .setShortName("a")
                                  .setDefaultValue("default")
                                  .setImplicitValue("implicit"));
            b = cppli.addArgument(ArgumentSpec("arg_b")
                                  .setShortName("b")
                                  .setDefaultValue("default")
                                  .setImplicitValue("implicit"));
            c = cppli.addArgument(ArgumentSpec("arg_c")
                                  .setShortName("c")
                                  .setDefaultValue("default")
                                  .setImplicitValue("implicit"));
        });

        test("Providing values for multiple arguments via double dash", [&] {
            cppli.interpret({"--arg_a=value", "--b"});
            expect(a.get(), isEqualTo("value"));
            expect(b.get(), isEqualTo("implicit"));
            expect(c.get(), isEqualTo("default"));
        });

        test("Providing values for multiple arguments with multiple single "
             "dash arguments", [&] {
            cppli.interpret({"-a", "-b", "value"});
            expect(a.get(), isEqualTo("implicit"));
            expect(b.get(), isEqualTo("value"));
            expect(c.get(), isEqualTo("default"));
        });

        test("Providing implicit values for multiple arguments via a single"
             " dash argument", [&] {
            cppli.interpret({"-ab"});
            expect(a.get(), isEqualTo("implicit"));
            expect(b.get(), isEqualTo("implicit"));
            expect(c.get(), isEqualTo("default"));
        });

        test("Providing values for multiple arguments via a single dash"
             "argument & space for non-implicit value of the last one", [&] {
            cppli.interpret({"-abc", "value"});
            expect(a.get(), isEqualTo("implicit"));
            expect(b.get(), isEqualTo("implicit"));
            expect(c.get(), isEqualTo("value"));
        });

        test("Providing values for multiple arguments via a single dash"
             "argument & equal sign for non-implicit value of the last one",
             [&] {
                 cppli.interpret({"-abc=value"});
                 expect(a.get(), isEqualTo("implicit"));
                 expect(b.get(), isEqualTo("implicit"));
                 expect(c.get(), isEqualTo("value"));
             });
    });

    group("Invalid argument names", [&] {
        test("Registering an argument with the same name as an existing one "
             "throws", [&] {
            cppli.addArgument(ArgumentSpec("name"));
            expect([&] {
                cppli.addArgument(ArgumentSpec("name"));
            }, throws);
        });

        test("Registering an argument with the same name as an existing one's "
             "short name throws", [&] {
            cppli.addArgument(ArgumentSpec("name").setShortName("n"));
            expect([&] {
                cppli.addArgument(ArgumentSpec("n"));
            }, throws);
        });

        test("Registering an argument with the same short name as an existing "
             "one's name throws", [&] {
            cppli.addArgument(ArgumentSpec("n"));
            expect([&] {
                cppli.addArgument(ArgumentSpec("name").setShortName("n"));
            }, throws);
        });

        test("Registering an argument with the same short name as an existing "
             "one's short name throws", [&] {
            cppli.addArgument(ArgumentSpec("name").setShortName("n"));
            expect([&] {
                cppli.addArgument(ArgumentSpec("name2").setShortName("n"));
            }, throws);
        });

        test("Registering an argument with a short name that is longer than "
             "one character throws", [&] {
            expect([&] {
                cppli.addArgument(ArgumentSpec("name").setShortName("nnn"));
            }, throws);
        });
    });
}
