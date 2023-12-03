//
// Created by Mikal on 03/12/2023.
//

#pragma once

template<std::size_t N, auto... Xs>
requires(N >= 0)
constexpr auto replicate (List<Xs...> l) {
    if constexpr(N == 0) {
        return List<>();
    }
    if constexpr(N == 1){
        return l;
    }
    if constexpr(N > 1) {
        return append(l, replicate<N-1>(l));
    }
}

//Unable to create as these are endless lists, unsure how to do that without haskelss lazy eval
//TODO: Repeat
//TODO: Cycle