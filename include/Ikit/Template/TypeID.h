#pragma once

namespace KTKR::BASIC::TypeID {
// ref: https://github.com/skypjack/entt
template <typename T>
struct TypeID {
    /**
     * @brief Returns the numeric representation of a given type.
     * @return The numeric representation of the given type.
     */
    static constexpr size_t id() noexcept {
        std::string_view name = nameof::nameof_type<T>();
#if defined(_MSC_VER)
        if (name.size() > sizeof("enum") && name[0] == 'e' && name[1] == 'n' && name[2] == 'u' && name[3] == 'm' && name[4] == ' ') {
            name.remove_prefix(sizeof("enum"));
        }
        if (name.size() > sizeof("class") && name[0] == 'c' && name[1] == 'l' && name[2] == 'a' && name[3] == 's' && name[4] == 's' && name[5] == ' ') {
            name.remove_prefix(sizeof("class"));
        }
        if (name.size() > sizeof("struct") && name[0] == 's' && name[1] == 't' && name[2] == 'r' && name[3] == 'u' && name[4] == 'c' && name[5] == 't' && name[6] == ' ') {
            name.remove_prefix(sizeof("struct"));
        }
#endif
        auto value = hashed_string::value(name);
        return value;
    }
};
}  // namespace KTKR::BASIC::TypeID

namespace KTKR {
template<typename T>
constexpr size_t TypeID = BASIC::TypeID::TypeID<T>::id();
}  // namespace KTKR
