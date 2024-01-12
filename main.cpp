#include <string>
#include "basic/basic_operators.h"
#include "transformations/transformations.h"
#include "folds/folds.h"
#include "sublist/sublist.h"
#include "searching/search.h"
#include "zipping/zip.h"
#include "special/special.h"

//TODO: or
//TODO: and
//TODO: show
//TODO: showList
// Todo: Break
//TODO: notElem
//TODO: lookup
//TODO: scanl
//TODO: scanl1
//TODO: scanr
//TODO: scanr1

int main() {
    //cout << fact<10>::value;
    constexpr auto l0 = List<1,2,3>();
    constexpr auto l1 = List<4,5,6>();
    constexpr auto l2 = List<7,8,9>();
    constexpr auto l3 = postpend<5>(List<1,2,3,4>());
    constexpr auto l4 = l3.prepend2<5>();
    constexpr auto e = head(l3);
    constexpr auto droptest = drop<3>(l3);
    constexpr auto taketest = take<5>(l3);
    constexpr auto splitAtTest = splitAt<2>(l3);
    constexpr auto filterTest = filter(l3, [](int x){return x <=3;});
    constexpr auto dropWhileTest = dropWhile([](int x){return x < 3;},List<1,2,3,4,5>());
    constexpr auto takeWhileTest = takeWhile([](int x){return x >=3;}, l4);
    constexpr auto f = get<2>(l3);
    constexpr auto g = append(l1, l3);
    constexpr auto lastTest = last(l3);
    constexpr auto initTest = init(l0);
    constexpr auto reverseTest = reverse(l0);
    constexpr auto anyTest = any([](int x){return x >=3;}, l0);
    constexpr auto allTest = all([](int x){return x >=2;}, l0);
    //constexpr auto concatMapAuto = concatMap([](int x){return List<int>(x,x*2);}
    constexpr auto concatTest = concat(List<l0,l1, l2>());
    constexpr auto foldlTest = foldl<64>([](int x, int y){return x / y;}, List<4,2,4>());
    constexpr auto scanlTest = scanl<64>([](int x, int y){return x / y;}, List<4,2,4>());
    constexpr auto scanl1Test = scanl1([](int x, int y){return x / y;}, List<64,4,2,8>());
    constexpr auto scanrTest = scanr<2>([](int x, int y){return x / y;}, List<8,12,24,4>());
    constexpr auto scanr1Test = scanr1([](int x, int y){return x / y;}, List<8,12,24,2>());
    constexpr auto foldl1Test = foldl1(([](int x, int y){return x + y;}), List<1,8,2,4>());
    constexpr auto foldrTest = foldr<2>([](int x, int y){return x / y;}, List<8,12,24,4>());
    constexpr auto foldr1Test = foldr1([](int x, int y){return x / y;}, List<8,12,24,4, 2>());
    constexpr auto sumTest = sum(l0);
    constexpr auto lookupTest = lookup<'c'>(List<std::pair('a', 0), std::pair('b', 1), std::pair('c',2)>());
    constexpr auto productTest = product(l0);
    //constexpr auto productTest2 = product(List<>());
    constexpr auto zipTest = zip(l0, l1);
    constexpr auto unzipTest = unzip(zipTest);
    constexpr auto zipwithTest = zipwith<([](int x, int y){return x + y;})>(l0,l1);
    constexpr auto breakTest = list_break(([](int x){return x == 3;}), List<1,2,3,4,5>());
    constexpr auto testTakeEmpty = take<0>(List<>());
    constexpr auto testDropEmpty = drop<3>(List<>());
    constexpr auto testTrueNull = null(List<>());
    constexpr auto testFalseNull = null(List<1,2,3>());
    constexpr auto headTest = head(List<1,2,3>());
    constexpr auto maxTest = max(l0);
    std::cout << get<1>(concatTest);
    //constexpr auto initTest = init(List<1,2>());

    /*
    constexpr auto l0 = List<1,2,3,4,5,6,7,8>();
    constexpr auto test = List<3>() >> app::postpend<l0>();
    */

    return 0;
}
