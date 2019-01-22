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

    ArgumentSpec& setDescription(const std::string& _description);
    ArgumentSpec& setHelpGroup(const std::string& _helpGroup);
    ArgumentSpec& setShortName(const std::string& _shortName);
    ArgumentSpec& setDefaultValue(const std::string& _defaultValue);
    ArgumentSpec& setImplicitValue(const std::string& _implicitValue);

    std::string name;
    std::string description = "";
    std::string helpGroup = "";
    std::string shortName = "";
    std::string defaultValue = "";
    std::string implicitValue = "";
};

}

#endif
