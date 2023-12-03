//
// Created by Mikal on 03/12/2023.
//

#ifndef UNTITLED1_LIST_H
#define UNTITLED1_LIST_H

#endif //UNTITLED1_LIST_H

#include <string>

#pragma once

template<auto... Xs>
//requires (is_unityped(Xs...))
struct List
{
    template<auto X>
    constexpr auto postpend2() const {return List<Xs..., X>();}

    //template<std::size_t N>
    //requires (sizeof...(Xs) > 0) && (N <= sizeof... (Xs))
    //constexpr auto bb() const;
    template<auto X>
    constexpr auto prepend2() const {return List<X, Xs...>();}

    //read chapter 12, on where to use pack expansion
    //template<> constexpr auto head2() {return Xs...;}

    constexpr std::string to_string() const {
        if constexpr (sizeof...(Xs) == 1) {
            return "[" + std::to_string(Xs...) + "]";
        }
        std::string myString = (... + (std::to_string(Xs)+", "));
        myString.pop_back();
        myString.pop_back();
        return ("[ " + myString + " ]");
    }
};