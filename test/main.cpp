#include <kktest.hpp>

using namespace kktest;

extern void choiceArgumentTest();
extern void flagTest();
extern void numericArgumentTest();
extern void parserTest();
extern void helpTest();

int main(int argc, char** argv) {
    return run(argc, argv, {
        TestCase(choiceArgumentTest, "ChoiceArgument"),
        TestCase(flagTest, "Flag"),
        TestCase(numericArgumentTest, "NumericArgument"),
        TestCase(parserTest, "Parser"),
        TestCase(helpTest, "Help")
    });
}
