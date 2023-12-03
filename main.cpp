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

//TODO: zip3

//TODO: zipWith

//TODO: zipWith3

//TODO: unzip

//TODO: unzip3

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
    constexpr auto taketest = take<5>(l3);
    constexpr auto splitAtTest = splitAt<2>(l3);
    constexpr auto filterTest = filter(l3, [](int x){return x <=3;});
    constexpr auto dropWhileTest = dropWhile([](int x){return x <=3;}, l4);
    constexpr auto takeWhileTest = takeWhile([](int x){return x >=3;}, l4);
    constexpr auto f = get<2>(l3);
    constexpr auto g = append(l1, l3);
    constexpr auto lastTest = last(l3);
    constexpr auto initTest = init(l0);
    constexpr auto reverseTest = reverse(l0);
    constexpr auto anyTest = any([](int x){return x >=3;}, l0);
    constexpr auto allTest = all([](int x){return x >=2;}, l0);
    //constexpr auto concatMapAuto = concatMap([](int x){return List<int>(x,x*2);}
    constexpr auto concatTest = concat(List<l0,l1>());

    constexpr auto foldlTest = foldl([](int x, int y){return x / y;}, 64, List<4,2,4>());
    constexpr auto foldl1Test = foldl1(([](int x, int y){return x + y;}), List<1,8,2,4>());
    constexpr auto foldrTest = foldr([](int x, int y){return x / y;}, 2, List<8,12,24,4>());
    constexpr auto foldr1Test = foldr1([](int x, int y){return x / y;}, List<8,12,24,4, 2>());
    constexpr auto sumTest = sum(l0);
    constexpr auto productTest = product(l0);
    std::cout << concatTest.to_string();
    constexpr auto testTakeEmpty = take<0>(List<>());
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
