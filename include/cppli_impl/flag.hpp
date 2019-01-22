#ifndef CPPLI_IMPL_FLAG_H_
#define CPPLI_IMPL_FLAG_H_

#include <string>

namespace cppli {

class Flag {
 public:
    virtual ~Flag();

    virtual bool get() const = 0;
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
