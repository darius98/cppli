#include <cppli_impl/numeric_argument.hpp>

using namespace std;

namespace cppli {

template<>
void NumericArgument<char>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgument<unsigned char>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgument<short int>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgument<unsigned short int>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgument<int>::setValue(const std::string& _value) {
    value = stoi(_value);
}

template<>
void NumericArgument<unsigned int>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgument<long>::setValue(const std::string& _value) {
    value = stol(_value);
}

template<>
void NumericArgument<unsigned long>::setValue(const std::string& _value) {
    value = stoul(_value);
}

template<>
void NumericArgument<long long>::setValue(const std::string& _value) {
    value = stoll(_value);
}

template<>
void NumericArgument<unsigned long long>::setValue(const std::string& _value) {
    value = stoull(_value);
}

template<>
void NumericArgument<float>::setValue(const std::string& _value) {
    value = stof(_value);
}

template<>
void NumericArgument<double>::setValue(const std::string& _value) {
    value = stod(_value);
}

template<>
void NumericArgument<long double>::setValue(const std::string& _value) {
    value = stold(_value);
}

}
