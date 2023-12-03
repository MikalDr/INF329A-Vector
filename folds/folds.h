//
// Created by Mikal on 03/12/2023.
//

#include "../list.h"

#pragma once

template<auto... Xs>
constexpr auto sum (List<Xs...> l) {
    return foldl1([](int x, int y){return x+y;}, l);
}

template<auto... Xs>
constexpr auto product (List<Xs...> l) {
    return foldl1([](int x, int y){return x*y;}, l);
}

template<auto T, auto X, auto... Xs>
constexpr auto foldl (auto P, List<X, Xs...>)
requires (std::is_invocable_v<decltype(P), decltype(X), decltype(T)>) &&
(std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...)
{
return foldl<P(T, X)>(P, List<Xs...>());
}
template<auto T>
constexpr auto foldl(auto, List<>) {
    return T;
}

template<auto... Xs>
constexpr auto foldl1 (auto P, List<Xs...> l) {
    return foldl<head(l)>(P, tail(l));
}

template<auto T, auto... Xs>
constexpr auto foldr (auto P, List<Xs...> l)
requires (std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...)
{
return foldr<P(last(l),T)>(P, init(l));
}
template<auto T>
constexpr auto foldr(auto, List<>) {
    return T;
}

template<auto... Xs>
constexpr auto foldr1 (auto P, List<Xs...> l) {
    return foldr<last(l)>(P, init(l));
}