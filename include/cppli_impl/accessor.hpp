#ifndef CPPLI_IMPL_ACCESSOR_HPP_
#define CPPLI_IMPL_ACCESSOR_HPP_

#include <stdexcept>

namespace cppli {
namespace detail {

template<class T>
class Accessor {
 public:
    explicit Accessor(const T* _resource = nullptr): resource(_resource) {}

    Accessor(const Accessor& other): resource(other.resource) {}

    Accessor(Accessor&& other) noexcept: resource(other.resource) {}

    Accessor& operator=(const Accessor& other) {
        resource = other.resource;
        return *this;
    }

    Accessor& operator=(Accessor&& other) noexcept {
        resource = other.resource;
        return *this;
    }

    bool isValid() const {
        return resource != nullptr;
    }

    decltype(std::declval<T>().get()) get() const {
        if (!isValid()) {
            throw std::invalid_argument(
                "Using an argument accessor that was not initialized with a "
                "call to Parser.add...()!");
        }
        return resource->get();
    }

    decltype(std::declval<T>().appeared()) appeared() const {
        if (!isValid()) {
            throw std::invalid_argument(
                "Using an argument accessor that was not initialized with a "
                "call to Parser.add...()!");
        }
        return resource->appeared();
    }

 private:
    const T* resource = nullptr;
};

}  // namespace detail
}  // namespace cppli

#endif
