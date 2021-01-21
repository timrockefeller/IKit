#pragma once

#include <type_traits>

namespace KTKR {
template <typename T>
struct IType { using type = T; };
template <typename T, T V>
struct IValue { static constexpr T value = V; };

template <typename Instance, template <typename...> class T>
struct is_instance_of;
template <typename Instance, template <typename...> class T>
constexpr bool is_instance_of_v = is_instance_of<Instance, T>::value;

// =================================================


template <typename Instance, template <typename...> class T>
struct is_instance_of : std::false_type {};

template <typename... Args, template <typename...> class T>
struct is_instance_of<T<Args...>, T> : std::true_type {};
}  // namespace KTKR
