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

    IntArgumentSpec& setDescription(const std::string& _description);
    IntArgumentSpec& setHelpGroup(const std::string& _helpGroup);
    IntArgumentSpec& setShortName(const std::string& _shortName);
    IntArgumentSpec& setDefaultValue(int _defaultValue);
    IntArgumentSpec& setImplicitValue(int _implicitValue);

    std::string name;
    std::string description = "";
    std::string helpGroup = "";
    std::string shortName = "";
    int defaultValue = 0;
    int implicitValue = 0;
};

}

#endif
