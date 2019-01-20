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

    IntArgumentSpec& setDescription(const std::string& _helpText);
    IntArgumentSpec& setShortName(const std::string& _shortName);
    IntArgumentSpec& setDefaultValue(int _defaultValue);
    IntArgumentSpec& setImplicitValue(int _implicitValue);

    std::string name;
    std::string helpText = "";
    std::string shortName = "";
    int defaultValue = 0;
    int implicitValue = 0;
};

}

#endif
