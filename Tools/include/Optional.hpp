#pragma once

namespace tools {

    struct nullopt_t {};
    const nullopt_t nullopt {};

    template <typename T>
    struct Optional {
        T value;
        bool has_value = false;

        Optional() : has_value(false) {}
        Optional(T value) : value(value), has_value(true) {}
        Optional(nullopt_t) : has_value(false) {}

        bool hasValue() const { return has_value; }
        explicit operator bool() const { return has_value; } // allows for if (myOpt) { ... }

        T& operator*() { return value; } // allows for *myOpt = ... 
        const T& operator*() const { return value; }

        T* operator->() { return &value; }
        const T* operator->() const { return &value; }

        bool operator==(const Optional<T>& other) const {
            return has_value == other.has_value && (!has_value || value == other.value);
        }

        bool operator!=(const Optional<T>& other) const {
            return !(value == other.value);
        }

        bool operator==(const nullopt_t) const { return !has_value; }
        bool operator!=(const nullopt_t) const { return has_value; }
    };

}