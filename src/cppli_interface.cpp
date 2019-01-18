#include <cppli_impl/cppli_interface.hpp>
#include "cppli_impl.hpp"

using namespace std;

namespace cppli {

Cppli* Cppli::create(const string& helpPrefix) {
    return new CppliImpl(helpPrefix);
}

vector<string> Cppli::interpret(int argc, char** argv) {
    vector<string> args(static_cast<size_t>(argc));
    for (int i = 0; i < argc; ++ i) {
        args.emplace_back(argv[i]);
    }
    return interpret(args);
}

}
