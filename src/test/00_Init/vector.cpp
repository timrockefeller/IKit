// test code for move sematic

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
template <typename T>
auto copy_uptr_array(const std::unique_ptr<T[]>& src,
                     std::size_t capacity,
                     std::size_t size) {
    auto result = std::make_unique<T[]>(capacity);
    std::copy(src.get(), src.get() + size, result.get());
    return result;
}

template <typename T>
class vector {
   private:
    std::unique_ptr<T[]> _data;
    std::size_t _size{0}, _capacity{0};

   public:
    vector() = default;
    ~vector() { delete[] _data; }

    vector(vector&& rhs) = default;
    vector& operator=(vector&& rhs) = default;

    vector(const vector& rhs)
        : _size{rhs._size}, _capacity{rhs._capacity} {
        _data = copy_uptr_array(rhs._data, _capacity, _size);
    }
    vector& operator=(const vector& rhs) {
        _size = rhs._size;
        _capacity = rhs._capacity;
        _data = copy_uptr_array(rhs._data, _capacity, _size);
        return *this;
    }

    void push_back(const T& x) {
        if (_capacity == _size) {
            const auto new_capacity = _capacity + 10;
            T* tmp = new T[new_capacity];
            std::copy(_data, _data + _capacity, tmp);
            std::swap(tmp, _data);
            delete[] tmp;
            _capacity = new_capacity;
        }
        _data[_size] = x;
        ++_size;
    }

    const auto& at(std::size_t i) const {
        assert(i < _size);
        return _data[i];
    }
};
void strcd() {
    int b;
    const auto l = [i = 0, a = b] {};
    /* ↑ 等价于 ↓ */
    // struct anonymous {
    //     int i = 0, a;
    //     anonymous(int b)
    //         : a{b} {}
    //     auto operator()() const {}
    // } l{b};
}
