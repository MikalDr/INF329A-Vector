//
// Created by Mikal on 03/12/2023.
//

#include "../list.h"

#pragma once

template<auto... Xs>
constexpr auto map(auto f, List<Xs...> l)
requires(std::is_invocable_v<decltype(f), decltype(Xs)> && ...) && (sizeof... (Xs) > 0)
{
if constexpr (sizeof... (Xs) == 0) {
return l;
}
else {
return prepend<f(head(l))>(map(f, tail(l)));
}
}
constexpr auto map(auto, List<> l){
    return l;
}

// FILTER

constexpr auto filter(List<> l, auto f) {
    return l;
}

template<auto... Xs>
constexpr auto filter(List<Xs...> l, auto f)
requires(sizeof... (Xs) > 0) && (std::is_invocable_r_v<bool, decltype(f), decltype(Xs)> && ...)
{
if constexpr (f(head(l)))
{ return prepend<head(l)>(filter(tail(l), f)); }
else
{ return filter(tail(l), f); }
}

// TAKE

template<std::size_t N, auto... Xs>
requires(N <= (sizeof...(Xs))+1)
constexpr auto take(List<Xs...> l) {
    if constexpr (N <= 0) {
        return List<>();
    } else {
        return prepend<head(l)>(take<N - 1>(tail(l)));
    }
}

// DROP

template<std::size_t N, auto... Xs>
requires(N <= sizeof...(Xs)+1)
constexpr auto drop(List<Xs...> l) {
    if constexpr (N <= 0) {
        return l;
    } else {
        return drop<N - 1>(tail(l));
    }
}
// If N is larger than list length, return empty list
template<std::size_t N>
constexpr auto drop(List<>) {return List<>();}

template<auto... Xs>
constexpr auto takeWhile(auto P, List<Xs...> l)
requires (std::is_invocable_r<bool, decltype(P), decltype(Xs)>::value && ...) && (sizeof... (Xs) > 0)
{
if constexpr(P (head(l))){ return prepend<head(l)>(takeWhile(P, tail(l))); }
else { return List<>(); }
}

constexpr auto takeWhile(auto P, List<> l) { return l;}

template<auto... Xs>
constexpr auto dropWhile(auto P, List<Xs...> l)
requires (std::is_invocable_r<bool, decltype(P), decltype(Xs)>::value && ...) && (sizeof... (Xs) > 0)
{
if constexpr(P (head(l))){ return (dropWhile(P, tail(l))); }
else { return l; }
}

constexpr auto dropWhile(auto P, List<> l) { return l;}

template<List a, List b>
constexpr auto concat(List<a, b>) {
    return append(a, b);
}

template<auto... Xs>
constexpr auto concatMap(auto P,List<Xs...> l)
requires (std::is_invocable_v<decltype(P), decltype(Xs)> &&...)
{
    return append(P(head(l)), concatMap(P, tail(l)));
}

template<auto T, auto... Xs>
constexpr auto scanl (auto P, List<Xs...> l)
requires (sizeof... (Xs) > 0)
{
    return postpend<foldl<T>(P, l)>(scanl<T>(P, init(l)));
}
template<auto T, auto... Xs>
constexpr auto scanl (auto, List<> l) {
    return List<T>();
}

template<auto T, auto... Xs>
constexpr auto scanr (auto P, List<Xs...> l)
requires (sizeof... (Xs) > 0)
{
    return prepend<foldr<T>(P,l)>(scanr<T>(P, tail(l)));
}
template<auto T, auto... Xs>
constexpr auto scanr (auto, List<> l) {
    return List<T>();
}
template<auto... Xs>
requires(sizeof... (Xs) > 0)
constexpr auto scanl1 (auto P, List<Xs...> l)
{
    if constexpr(length(l) == 1) {
        return scanl<head(l)>(P, List<>());
    } else {
        return scanl<head(l)>(P, tail(l));
    }
}

template<auto... Xs>
requires(sizeof... (Xs) > 0)
constexpr auto scanr1 (auto P, List<Xs...> l)
{
    if constexpr(length(l) == 1) {
        return scanr<last(l)>(P, List<>());
    } else {
        return scanr<last(l)>(P, init(l));
    }
}