#ifndef CPPLI_IMPL_FLAG_HPP_
#define CPPLI_IMPL_FLAG_HPP_

#include <string>

#include <cppli_impl/accessor.hpp>
#include <cppli_impl/command_line_spec.hpp>
#include <cppli_impl/choice_argument.hpp>

namespace cppli {

// Forward declaration so I can declare the accessor.
namespace detail { class FlagDetails; }

typedef detail::Accessor<detail::FlagDetails> Flag;

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

namespace detail {

class FlagDetails: public ChoiceArgumentDetails<bool> {
 public:
    FlagDetails();

    bool eatsPositionalArgument() const override;
};

}  // namespace detail
}  // namespace cppli

#endif
