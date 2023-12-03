//
// Created by Mikal on 03/12/2023.
//


#pragma once

template <auto... Xs, auto... Ys>
requires (sizeof... (Xs) > 0) && (sizeof... (Ys) > 0)
constexpr auto zip (List<Xs...> a, List<Ys...> b) {
    return prepend<std::pair(head(a), head(b))>(zip(tail(a), tail(b)));
}
//If one of the lists are empty, this should be called
template <auto... Xs, auto... Ys>
constexpr auto zip (List<Xs...>, List<Ys...>) {
return List<>();
}

template <auto P, auto... Xs, auto... Ys>
constexpr auto zipwith (List<Xs...> a, List<Ys...> b) {
    if constexpr (length(a) > 1 && length(b) > 1) {
        return prepend<P(head(a), head(b))>(zipwith<P>(tail(a), tail(b)));
    }
    else {
        return List<P(head(a), head(b))>();
    }
}

template <std::pair... Xs>
constexpr auto unzip (List<Xs...> l)
requires (sizeof... (Xs) > 0)
{
    if constexpr(length(l) > 1) {
        auto rest = unzip(tail(l));
        return std::make_pair(prepend<head(l).first>(rest.first), prepend<head(l).second>(rest.second));
    }
    else {
        return std::make_pair(List<head(l).first>(), List<head(l).second>());
    }
}
constexpr auto unzip (List<> l) { return l;}

//TODO: zip3
//TODO: zipWith
//TODO: zipWith3
//TODO: unzip3