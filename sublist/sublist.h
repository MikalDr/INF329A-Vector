//
// Created by Mikal on 03/12/2023.
//

#include "../list.h"
#pragma once

template<auto X, auto... Xs>
constexpr auto head(List<X, Xs...>) { return X; }

template<auto X, auto... Xs>
requires(sizeof... (Xs) + sizeof X > 0)
constexpr auto last(List<X, Xs...>) {
    if constexpr (sizeof... (Xs) == 0) {
        return X;
    } else {
        return last(List<Xs...>());
    }
}

template<auto X, auto... Xs>
requires((sizeof... (Xs))+1 > 0)
constexpr auto tail(List<X, Xs...>) { return List<Xs...>(); }

template <auto... Xs>
requires(sizeof... (Xs) > 0)
constexpr auto init(List<Xs...>) { return take<sizeof... (Xs)-1>(List<Xs...>()); }

template<std::size_t N, auto... Xs>
requires (N <= sizeof... (Xs))
constexpr auto splitAt(List<Xs...> l) {
    return std::make_tuple(take<N>(l), drop<N>(l));
}

template<auto... Xs>
constexpr auto span(auto P, List<Xs...> l)
requires (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...)
{ return std::make_tuple(takeWhile(P, l), dropWhile(P, l)); }
