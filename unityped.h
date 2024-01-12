//
// Created by Mikal on 12/01/2024.
//
#pragma once
#include <type_traits>//is_same_v

consteval bool is_unityped() {return true;}
consteval bool is_unityped(auto) {return true;}
consteval bool is_unityped(auto X, auto... Xs) {return (std::is_same_v<decltype(X), decltype(Xs)> && ...);}

template<typename T>
constexpr bool is_list() {
    return std::is_same_v<T, decltype(List<>{})>;
}