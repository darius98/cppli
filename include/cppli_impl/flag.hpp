#ifndef CPPLI_IMPL_FLAG_HPP_
#define CPPLI_IMPL_FLAG_HPP_

#include <string>

#include <cppli_impl/command_line_spec.hpp>

namespace cppli {

class Flag: public CommandLineSpec {
 public:
    ~Flag() override;

    bool get() const;

 private:
    Flag();

    void setDefault() override;

    void setImplicit() override;

    bool supportsValue() const override;

    void setValue(const std::string& _value) override;

    bool value;

friend class Cppli;
};

struct FlagSpec {
    explicit FlagSpec(std::string _name);

    FlagSpec& setDescription(const std::string& _description);
    FlagSpec& setHelpGroup(const std::string& _helpGroup);
    FlagSpec& setShortName(const std::string& _shortName);

    std::string name;
    std::string description = "";
    std::string helpGroup = "";
    std::string shortName = "";
};

}

#endif
