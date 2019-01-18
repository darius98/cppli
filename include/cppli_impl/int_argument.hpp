#ifndef CPPLI_IMPL_INT_ARGUMENT_H_
#define CPPLI_IMPL_INT_ARGUMENT_H_

#include <string>

namespace cppli {

class IntArgument {
 public:
    virtual ~IntArgument();

    virtual int get() const = 0;
};

struct IntArgumentSpec {
    explicit IntArgumentSpec(std::string _name);

    IntArgumentSpec& withHelpText(const std::string& _helpText);
    IntArgumentSpec& withShortName(const std::string& _shortName);
    IntArgumentSpec& withDefaultValue(int _defaultValue);
    IntArgumentSpec& withImplicitValue(int _implicitValue);

    std::string name;
    std::string helpText = "";
    std::string shortName = "";
    int defaultValue = 0;
    int implicitValue = 0;
};

}

#endif
