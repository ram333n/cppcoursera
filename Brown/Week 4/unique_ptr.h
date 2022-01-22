#pragma once
#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* pointer_ = nullptr;
public:
    UniquePtr() {}

    UniquePtr(T* ptr) {
        pointer_ = ptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) {
        pointer_ = other.pointer_;
        other.pointer_ = nullptr;
    }

    UniquePtr& operator= (const UniquePtr&) = delete;

    UniquePtr& operator= (UniquePtr&& other) {
        if (this != &other) {
            Reset(other.pointer_);
            other.pointer_ = nullptr;
        }
        return *this;
    }

    UniquePtr& operator= (std::nullptr_t) {
        Reset(nullptr);
        return *this;
    }

    ~UniquePtr() {
        delete pointer_;
    }

    T& operator* () const {
        return *pointer_;
    }

    T* operator-> () const {
        return pointer_;
    }

    T* Release() {
        T* result = pointer_;
        pointer_ = nullptr;
        return result;
    }

    void Reset(T* ptr) {
        delete pointer_;
        pointer_ = ptr;
    }

    void Swap(UniquePtr& other) {
        std::swap(pointer_, other.pointer_);
    }

    T* Get() const { 
        return pointer_;
    }
};
