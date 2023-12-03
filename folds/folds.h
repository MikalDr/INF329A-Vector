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

template<auto X, auto... Xs>
constexpr auto foldl (auto P, auto T, List<X, Xs...>)
requires (std::is_invocable_v<decltype(P), decltype(X), decltype(T)>) &&
(std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...)
{
return foldl(P, P(T, X), List<Xs...>());
}
constexpr auto foldl(auto, auto T, List<>) {
    return T;
}

template<auto... Xs>
constexpr auto foldl1 (auto P, List<Xs...> l) {
    return foldl(P, head(l), tail(l));
}

template<auto... Xs>
constexpr auto foldr (auto P, auto T, List<Xs...> l)
requires (std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...)
{
return foldr(P, P(last(l),T), init(l));
}
constexpr auto foldr(auto, auto T, List<>) {
    return T;
}

template<auto... Xs>
constexpr auto foldr1 (auto P, List<Xs...> l) {
    return foldr(P, last(l), init(l));
}