#pragma once
namespace KTKR {
template <typename T>
class UniquePtr {
   private:
    T* _ptr{nullptr};

   public:
    UniquePtr() = default;
    UniquePtr(T* ptr) noexcept
        : _ptr{ptr} {}
    ~UniquePtr() noexcept { delete _ptr; }

    // prevent copies
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // ownership transfer
    UniquePtr(UniquePtr&& rhs) noexcept
        : _ptr{ptr} {
        rhs._ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept {
        _ptr = rhs._ptr;
        rhs._ptr = nullptr;
        return *this;
    }
};

}  // namespace KTKR
