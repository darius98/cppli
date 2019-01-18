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

    FlagSpec& withHelpText(const std::string& _helpText);
    FlagSpec& withShortName(const std::string& _shortName);

    std::string name;
    std::string helpText = "";
    std::string shortName = "";
};

}

#endif
