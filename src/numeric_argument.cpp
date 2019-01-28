#include <cppli_impl/numeric_argument.hpp>

using namespace std;

namespace cppli {
namespace detail {

template<>
void NumericArgumentDetails<char>::setValue(const string& _value) {
    value = stoi(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<unsigned char>::setValue(const string& _value) {
    value = stoul(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<short int>::setValue(const string& _value) {
    value = stoi(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<unsigned short int>::setValue(
        const string& _value) {
    value = stoul(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<int>::setValue(const string& _value) {
    value = stoi(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<unsigned int>::setValue(const string& _value) {
    value = stoul(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<long>::setValue(const string& _value) {
    value = stol(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<unsigned long>::setValue(const string& _value) {
    value = stoul(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<long long>::setValue(const string& _value) {
    value = stoll(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<unsigned long long>::setValue(
        const string& _value) {
    value = stoull(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<float>::setValue(const string& _value) {
    value = stof(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<double>::setValue(const string& _value) {
    value = stod(_value);
    appearedInArgs = true;
}

template<>
void NumericArgumentDetails<long double>::setValue(const string& _value) {
    value = stold(_value);
    appearedInArgs = true;
}

}  // namespace detail
}  // namespace cppli
