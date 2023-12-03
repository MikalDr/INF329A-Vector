//
// Created by Mikal on 03/12/2023.
//

#include <iostream>
#include <string>
#include "../list.h"

#pragma once

template<size_t N, auto... Xs>
requires (sizeof...(Xs) >= 0 && (N < sizeof...(Xs)))
constexpr auto get(List<Xs...> l) {
    if constexpr (N == 0) {
        return head(l);
    } else
        return get<N - 1>(List<Xs...>());
}

template<auto... Xs>
constexpr auto length(List<Xs...>) {return sizeof...(Xs);}

template<auto... Xs>
constexpr auto null(List<Xs...>) { return sizeof...(Xs) == 0; }

template<auto... Xs>
constexpr auto reverse(List<Xs...> l)
requires(sizeof... (Xs) > 0)
{
    return postpend<head(l)>(reverse(tail(l)));
}
constexpr auto reverse(List<> l) {
    return l;
}

template<auto X, auto... Xs>
constexpr auto postpend(List<Xs...> l) { return List<Xs..., X>(); }

template<auto X, auto... Xs>
constexpr auto prepend(List<Xs...> l) { return List<X, Xs...>(); }

template<auto... Xs, auto... Ys>
constexpr auto append(List<Xs...>, List<Ys...>) { return List<Xs..., Ys...>(); }