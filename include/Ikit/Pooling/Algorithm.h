#pragma once
#include <algorithm>
#include <iterator>
#include <set>
namespace KTKR {

template <typename Container>
Container SetUnion(const Container&, const Container&);

template <typename Container>
Container SetDifference(const Container&, const Container&);

template <typename Container>
Container SetIntersection(const Container&, const Container&);

template <typename Container>
Container SetSymmetricDifference(const Container&, const Container&);

}  // namespace KTKR

#include "details/Algorithm.inl"
