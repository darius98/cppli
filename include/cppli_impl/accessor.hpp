#ifndef CPPLI_IMPL_ACCESSOR_HPP_
#define CPPLI_IMPL_ACCESSOR_HPP_

#include <stdexcept>

namespace cppli {

template<class T>
class Accessor {
 public:
    Accessor(): resource(nullptr) {}

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
                "call to Cppli.add...()!");
        }
        return resource->get();
    }

 private:
    explicit Accessor(const T* _resource): resource(_resource) {}

    const T* resource = nullptr;

friend class Cppli;
};

}

#endif
