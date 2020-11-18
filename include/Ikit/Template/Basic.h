#pragma once


namespace KTKR
{
    template<typename T> struct IType { using type = T; };
	template<typename T, T V> struct IValue { static constexpr T value = V; };

} // namespace KTKR
