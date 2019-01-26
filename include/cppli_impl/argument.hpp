#ifndef CPPLI_IMPL_ARGUMENT_HPP_
#define CPPLI_IMPL_ARGUMENT_HPP_

#include <string>

#include <cppli_impl/command_line_spec.hpp>

namespace cppli {

class Argument: public CommandLineSpec {
 public:
    ~Argument() override;

    std::string get() const;

 private:
    Argument(std::string _defaultValue, std::string _implicitValue);

    void setDefault() override;

    void setImplicit() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;

    std::string value;
    std::string defaultValue;
    std::string implicitValue;

friend class Cppli;
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
