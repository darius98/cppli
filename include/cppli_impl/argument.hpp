#ifndef CPPLI_IMPL_ARGUMENT_H_
#define CPPLI_IMPL_ARGUMENT_H_

#include <string>

namespace cppli {

class Argument {
 public:
    virtual ~Argument();

    virtual std::string get() const = 0;
};

struct ArgumentSpec {
    explicit ArgumentSpec(std::string _name);

    ArgumentSpec& setDescription(const std::string& _helpText);
    ArgumentSpec& setShortName(const std::string& _shortName);
    ArgumentSpec& setDefaultValue(const std::string& _defaultValue);
    ArgumentSpec& setImplicitValue(const std::string& _implicitValue);

    std::string name;
    std::string helpText = "";
    std::string shortName = "";
    std::string defaultValue = "";
    std::string implicitValue = "";
};

}

#endif
