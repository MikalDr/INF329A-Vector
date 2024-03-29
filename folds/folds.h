//
// Created by Mikal on 03/12/2023.
//

#include "../list.h"
#include "../unityped.h"

#pragma once

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto sum (List<Xs...> l) {
    return foldl1([](int x, int y){return x+y;}, l);
}

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto product (List<Xs...> l) {
    return foldl1([](int x, int y){return x*y;}, l);
}

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto product2 (List<Xs...> l) {
    return foldl<head(l)>([](int x, int y){return x*y;}, tail(l));
}
constexpr auto product2 (List<> l) {
    return List<>();
}

template<auto T, auto X, auto... Xs>
constexpr auto foldl (auto P, List<X, Xs...>)
requires (std::is_invocable_v<decltype(P), decltype(X), decltype(T)>) &&
(std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...) && (is_unityped(Xs...))
{
return foldl<P(T, X)>(P, List<Xs...>());
}
template<auto T>
constexpr auto foldl(auto, List<>) {
    return T;
}

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto foldl1 (auto P, List<Xs...> l) {
    return foldl<head(l)>(P, tail(l));
}

template<auto T, auto... Xs>
constexpr auto foldr (auto P, List<Xs...> l)
requires (std::is_invocable_v<decltype(P), decltype(Xs), decltype(T)> && ...) && (is_unityped(Xs...))
{
return foldr<P(last(l),T)>(P, init(l));
}
template<auto T>
constexpr auto foldr(auto, List<>) {
    return T;
}

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto foldr1 (auto P, List<Xs...> l) {
    return foldr<last(l)>(P, init(l));
}
template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto list_and(List<Xs...> l) { return foldl<true>([](bool a, bool b){return a && b;},l);}

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto list_or(List<Xs...> l) { return foldl<true>([](bool a, bool b){return a || b;},l);}