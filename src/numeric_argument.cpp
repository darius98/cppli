#include <cppli_impl/numeric_argument.hpp>

using namespace std;

namespace cppli {
namespace detail {

template<>
void NumericArgumentDetails<char>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgumentDetails<unsigned char>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgumentDetails<short int>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgumentDetails<unsigned short int>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgumentDetails<int>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgumentDetails<unsigned int>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgumentDetails<long>::setValue(const std::string& _value) {
    value = stol(_value);
}

template<>
void NumericArgumentDetails<unsigned long>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgumentDetails<long long>::setValue(const std::string& _value) {
    value = stoll(_value);
}

template<>
void NumericArgumentDetails<unsigned long long>::setValue(const std::string& _value) {
    value = stoull(_value);
}

template<>
void NumericArgumentDetails<float>::setValue(const std::string& _value) {
    value = stof(_value);
}

template<>
void NumericArgumentDetails<double>::setValue(const std::string& _value) {
    value = stod(_value);
}

template<>
void NumericArgumentDetails<long double>::setValue(const std::string& _value) {
    value = stold(_value);
}

}  // namespace detail
}  // namespace cppli
