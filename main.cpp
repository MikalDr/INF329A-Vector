#include <iostream>
#include <string>

template<auto n>
struct fact
{
    static constexpr unsigned value = n * fact<n-1>::value;
};

template<>
struct fact<0>
{
    static constexpr unsigned value = 1;
};

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

};

/* ###########################
 *       LIST OPERATIONS
 * ###########################
 */

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

template<auto X, auto... Xs>
requires(sizeof... (Xs) + sizeof X > 0)
constexpr auto head(List<X, Xs...>) { return X; }

template<auto X, auto... Xs>
requires(sizeof... (Xs) + sizeof X > 0)
constexpr auto last(List<X, Xs...>) {
    if constexpr (sizeof... (Xs) == 0) {
        return X;
    } else {
        return last(List<Xs...>());
    }
}

template<auto X, auto... Xs>
requires(sizeof... (Xs) + sizeof X > 0)
constexpr auto tail(List<X, Xs...>) { return List<Xs...>(); }

template <auto... Xs>
requires(sizeof... (Xs) > 0)
constexpr auto init(List<Xs...>) { return take<sizeof... (Xs)-1>(List<Xs...>()); }

template<auto... Xs>
constexpr auto null(List<Xs...>) { return sizeof...(Xs) == 0; }

template<auto... Xs>
constexpr auto length(List<Xs...>) {return sizeof...(Xs);}

// This is the index function (!!)
template<size_t N, auto X, auto... Xs>
requires (sizeof...(Xs) > 0 && (N <= sizeof...(Xs)))
constexpr auto bb(List<X, Xs...>) {
    if constexpr (N == 0) {
        return X;
    } else
        return bb<N - 1>(List<Xs...>());
}

template<auto X, auto... Xs>
constexpr auto reverse(List<X, Xs...>)
requires(sizeof... (Xs) + sizeof X > 0)
{
    return postpend<X>(reverse(List<Xs...>()));
}
constexpr auto reverse(List<> l) {
    return l;
}

template<auto X, auto... Xs>
constexpr auto postpend(List<Xs...> l) { return List<Xs..., X>(); }

template<auto X, auto... Xs>
constexpr auto prepend(List<Xs...> l) { return List<X, Xs...>(); }

template<auto... Xs, auto... Ys>
constexpr auto append(List<Xs...>, List<Ys...>) { return List<Xs..., Ys...>(); }

/* ###########################
 *          FOLDS
 * ###########################
 */

//This is the "any" function
template<auto... Xs>
constexpr auto any(auto P, List<Xs...> l)
requires(sizeof... (Xs) > 0) && (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...)
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
requires(sizeof... (Xs) > 0)
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

//TODO: or
//TODO: and

template<auto... Xs, auto... Ys>
constexpr auto concat(List<Xs...> l0, List<Ys...> l1) {
    return append(l0, l1);
}

template<auto... Xs, auto... Ys>
constexpr auto concatMap(auto P,List<Xs...> l0, List<Ys...> l1)
requires (std::is_invocable_v<decltype(P), decltype(Xs)> &&...) && (std::is_invocable_r_v<bool, decltype(P), decltype(Ys)> &&...)
{
    return map(P, concat(l0, l1));
}

//TODO: show
//TODO: showList

/* ###########################
 *          SUBLISTS
 * ###########################
 */

template<std::size_t N, auto... Xs>
requires(N <= sizeof...(Xs))
constexpr auto take(List<Xs...> l) {
    if constexpr (N == 0) {
        return List<>();
    } else {
        return prepend<head(l)>(take<N - 1>(tail(l)));
    }
}
// Allows for take on empty lists
template<std::size_t> constexpr auto take(List<>) {return List<>();}


template<std::size_t N, auto... Xs>
requires(N <= sizeof...(Xs))
constexpr auto drop(List<Xs...> l) {
    if constexpr (N == 0) {
        return l;
    } else {
        return drop<N - 1>(tail(l));
    }
}

// Allows for drop on empty lists
template<std::size_t> constexpr auto drop(List<>) {return List<>();}

template<std::size_t N, auto... Xs>
requires (N <= sizeof... (Xs))
constexpr auto splitAt(List<Xs...> l) {
    return std::make_tuple(take<N>(l), drop<N>(l));
}

template<auto... Xs>
constexpr auto takeWhile(auto P, List<Xs...> l)
requires (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...) && (sizeof... (Xs) > 0)
{
    if constexpr(P (head(l))){ return prepend<head(l)>(takeWhile(P, tail(l))); }
    else { return List<>(); }
}

constexpr auto takeWhile(auto P, List<> l) { return l;}

template<auto... Xs>
constexpr auto dropWhile(auto P, List<Xs...> l)
requires (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...)
{
    if constexpr(P (head(l))){ return dropWhile(tail(l), P); }
    else { return l;}
}

constexpr auto dropWhile(auto, List<> l) {
    return std::make_pair(List < > (), List < > ());
}

template<auto... Xs>
constexpr auto span(auto P, List<Xs...> l)
requires (std::is_invocable_r_v<bool, decltype(P), decltype(Xs)> &&...)
{ return std::make_tuple(takeWhile(P, l), dropWhile(P, l)); }

// Todo: Break

template<auto... Xs>
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

//TODO: notElem

//TODO: lookup

template<auto X, auto... Xs>
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
constexpr auto min (List<X,Xs...>) {
    constexpr auto m = min(List<Xs...>());
    if constexpr(X < m) {
        return X;
    }
    else {
        return m;
    }
}


template<auto... Xs>
constexpr auto sum (List<Xs...> l) {
    return foldl1([](int x, int y){return x+y;}, l);
}

template<auto... Xs>
constexpr auto product (List<Xs...> l) {
    return foldl1([](int x, int y){return x*y;}, l);
}

/* ###########################
 *          SCANS
 * ###########################
 */

//TODO: scanl
//TODO: scanl1
//TODO: scanr
//TODO: scanr1

/* ###########################
 *          FOLDS
 * ###########################
 */

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
template<std::size_t N, auto... Xs>
requires(N > 0)
constexpr auto replicate (List<Xs...> l) {
    if constexpr(N == 1){
        return l;
    }
    if constexpr(N > 1) {
        return append(l, replicate<N-1>(l));
    }
}

//TODO: Repeat
//TODO: Cycle

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

//TODO: zip3

//TODO: zipWith

//TODO: zipWith3

//TODO: unzip

//TODO: unzip3


/*
namespace app {
    template<auto X> struct postpend {
        template<auto... Xs>
        constexpr auto operator () (List<Xs...> l) const
        requires (std::is_same_v<decltype(X), decltype(Xs)> && ...){return l.template postpend2<X>(l);}
    };
}

template<auto... Xs>
constexpr auto operator >>(List<Xs...> l, auto f) {return f(l);}
*/

int main() {
    using namespace std;
    //cout << fact<10>::value;
    constexpr auto l0 = List<1,2,9,4,5,6,7,8>();
    constexpr auto l1 = prepend<0>(List<1,2,3,4>());
    constexpr auto l2 = l1.postpend2<5>();
    constexpr auto l3 = postpend<5>(List<1,2,3,4>());
    constexpr auto l4 = l3.prepend2<5>();
    constexpr auto e = head(l3);
    constexpr auto droptest = drop<3>(l3);
    constexpr auto taketest = take<3>(l3);
    constexpr auto splitAtTest = splitAt<2>(l3);
    constexpr auto filterTest = filter(l3, [](int x){return x <=3;});
    constexpr auto dropWhileTest = dropWhile([](int x){return x <=3;}, l4);
    constexpr auto takeWhileTest = takeWhile([](int x){return x >=3;}, l4);
    constexpr auto f = bb<2>(l3);
    constexpr auto g = append(l1, l3);
    constexpr auto lastTest = last(l3);
    constexpr auto initTest = init(l0);
    constexpr auto reverseTest = reverse(l0);
    constexpr auto anyTest = any([](int x){return x >=3;}, l0);
    constexpr auto allTest = all([](int x){return x >=2;}, l0);
    constexpr auto concatMapAuto = concatMap([](int x){return x * 3;}, l1, l2);
    constexpr auto foldlTest = foldl([](int x, int y){return x / y;}, 64, List<4,2,4>());
    constexpr auto foldl1Test = foldl1(([](int x, int y){return x + y;}), List<1,8,2,4>());
    constexpr auto foldrTest = foldr([](int x, int y){return x / y;}, 2, List<8,12,24,4>());
    constexpr auto foldr1Test = foldr1([](int x, int y){return x / y;}, List<8,12,24,4, 2>());
    constexpr auto sumTest = sum(l0);
    constexpr auto productTest = product(l0);
    std::cout << productTest;
    constexpr auto testTakeEmpty = take<3>(List<>());
    constexpr auto testDropEmpty = drop<3>(List<>());
    constexpr auto testTrueNull = null(List<>());
    constexpr auto testFalseNull = null(List<1,2,3>());
    constexpr auto headTest = head(List<1,2,3>());
    constexpr auto maxTest = max(l0);
    //std::cout << maxTest;
    //constexpr auto initTest = init(List<1,2>());

    /*
    constexpr auto l0 = List<1,2,3,4,5,6,7,8>();
    constexpr auto test = List<3>() >> app::postpend<l0>();
    */

    return 0;
}
