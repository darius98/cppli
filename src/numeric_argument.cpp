#include <cppli_impl/numeric_argument.hpp>

using namespace std;

namespace cppli {

template<> void NumericArgument<int>::setValue(const string& _value) {
    value = stoi(_value);
}

}
