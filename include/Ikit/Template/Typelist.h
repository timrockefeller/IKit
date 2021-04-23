#pragma once
#include "Basic.h"

namespace KTKR {
template <typename... Ts>
struct TypeList {};

// Status

template <typename List>
struct IsTypeList;
template <typename List>
constexpr bool IsTypeList_v = IsTypeList<List>::value;

template <typename List>
struct Length;
template <typename List>
constexpr size_t Length_v = Length<List>::value;

template <typename List>
struct IsEmpty;
template <typename List>
constexpr bool IsEmpty_v = IsEmpty<List>::value;

template <typename List>
struct Front;
template <typename List>
using Front_t = typename Front<List>::type;

// Get specific type in a typelist
template <typename List, size_t N>
struct At;
template <typename List, size_t N>
using At_t = typename At<List, N>::type;

template <typename List, size_t... Indices>
struct Select;
// template <typename List, size_t... Indices>
// using Select_t = typename Select<List, Indices>::type;

template <typename List>
struct PopFront;
template <typename List>
using PopFront_t = typename PopFront<List>::type;

template <typename List, typename T>
struct Find;
template <typename List, typename T>
constexpr size_t Find_v = Find<List, T>::value;
constexpr size_t Find_fail = static_cast<size_t>(-1);
}  // namespace KTKR

namespace KTKR::Private::Typelist {
template <typename List, typename T, size_t N = 0, bool found = false>
struct Find;
}  // namespace KTKR::Private::Typelist

namespace KTKR {

// =================================================

template <typename List>
struct IsTypeList : is_instance_of<List, TypeList> {};

// =================================================

template <typename... Ts>
struct Length<TypeList<Ts...>> : IValue<size_t, sizeof...(Ts)> {};

// =================================================

template <typename List>
struct IsEmpty : IValue<bool, Length_v<List> == 0> {};

// =================================================

template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> : IType<Head> {};

// =================================================

template <typename List>
struct At<List, 0> : IType<Front_t<List>> {};

template <typename List, size_t N>
struct At : At<PopFront_t<List>, N - 1> {};

// =================================================

template <typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> : IType<TypeList<Tail...>> {};

// =================================================

template <typename List, typename T>
struct Find : Private::Typelist::Find<List, T> {};

// =================================================

template <typename List, size_t... Indices>
struct Select : IType<TypeList<At_t<List, Indices>...>> {};

}  // namespace KTKR

namespace KTKR::Private::Typelist {
template <typename List, typename T, size_t N, bool found>
struct Find;
template <typename T, size_t N, typename... Ts>
struct Find<TypeList<Ts...>, T, N, true> : IValue<size_t, N - 1> {};
template <typename T, size_t N>
struct Find<TypeList<>, T, N, false> : IValue<size_t, Find_fail> {};
template <typename Head, typename... Tails, typename T, size_t N>
struct Find<TypeList<Head, Tails...>, T, N, false> : Find<TypeList<Tails...>, T, N + 1, std::is_same_v<Head, T>> {};
}  // namespace KTKR::Private::Typelist
