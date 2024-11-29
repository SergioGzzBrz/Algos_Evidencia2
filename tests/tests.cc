
#include "parte_1.h"
#include "parte_2.h"
#include "parte_3.h"
#include "parte_4.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Testing with DSU")
{
    // Testing DSU
    dsu_union(1, 2);
    dsu_union(4, 5);
    dsu_union(2, 5);
    REQUIRE(get(1) == get(5));
    REQUIRE(get(1) == get(4));
    REQUIRE(get(2) == get(4));
}

TEST_CASE("euclidean_distance")
{
    pair<int, int> a = make_pair(0, 2);
    pair<int, int> b = make_pair(2, 3);
    double res = sqrt(5);
    double eplison = 1e-6;
    REQUIRE(abs(euclidean_distance(a, b) - res) <= eplison);
}
