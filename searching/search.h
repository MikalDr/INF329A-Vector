//
// Created by Mikal on 03/12/2023.
//

#include "../list.h"
#include "../unityped.h"

#pragma once

template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto elem (auto T, List<Xs...> l) {
    if constexpr (T == head(l)) {
        return true;
    }
    else {
        return elem(T, tail(l));
    }
}
constexpr auto elem (auto, List<>) {
    return false;
}
template<auto... Xs>
requires (is_unityped(Xs...))
constexpr auto notElem(auto T, List<Xs...> l) {
    return !elem(T, l);
}

template<auto X, auto... Xs>
requires (is_unityped(X, Xs...))
constexpr auto max (List<X, Xs...>) {
    constexpr auto m =  max(List<Xs...>());
    if constexpr(X > m) {
        return X;
    }
    else{
        return m;
    }
}
template<auto X>
constexpr auto max (List<X>) {
    return X;
}
constexpr auto max (List<> l) {
    return l;
}

template<auto X, auto... Xs>
requires (is_unityped(X,Xs...))
constexpr auto min (List<X,Xs...>) {
    constexpr auto m = min(List<Xs...>());
    if constexpr(X < m) {
        return X;
    }
    else {
        return m;
    }
}
template<auto T, std::pair... Xs>
requires(sizeof... (Xs) > 0)
constexpr auto lookup (List<Xs...> l) {
    if constexpr(head(l).first == T) {
            return head(l).second;
    } else {
        return lookup<T>(tail(l));
    }
}
template<auto T>
constexpr auto lookup (List<>) {
    return;
}

template<auto... Xs>
constexpr auto any(auto P, List<Xs...> l)
requires(sizeof... (Xs) > 0) && (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...) && (is_unityped(Xs...))
{
if constexpr (P(head(l))) {
return true;
}
else {
return any(P, tail(l));
}
}
constexpr auto any(auto, List<>){
    return false;
}

template<auto... Xs>
requires(sizeof... (Xs) > 0) && (is_unityped(Xs...))
constexpr auto all(auto P, List<Xs...> l) {
    if constexpr (P(head(l))) {
        return all(P, tail(l));
    }
    else {
        return false;
    }
}
constexpr auto all(auto, List<>){
    return true;
}