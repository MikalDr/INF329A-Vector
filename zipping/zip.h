//
// Created by Mikal on 03/12/2023.
//


#pragma once

template <auto... Xs, auto... Ys>
requires (sizeof... (Xs) > 0) && (sizeof... (Ys) > 0)
constexpr auto zip (List<Xs...> a, List<Ys...> b) {
    return append(std::make_pair(head(a), head(b))), zip(tail(a), tail(b));
}
template <auto... Xs>
constexpr auto zip (List<>, List<Xs...> l) {
return l;
}
template <auto... Xs>
constexpr auto zip (List<Xs...> l, List<>) {
    return l;
}