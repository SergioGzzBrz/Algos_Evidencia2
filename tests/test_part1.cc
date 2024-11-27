#include "parte1_1.h"
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

TEST_CASE("transmission1 with mcode 1")
{ // Apply Z algorithm to find all occurrences of mcode in transmission
    vector<int> ans = ZAlg1("ab", "hasta la ab abab");
    vector<int> realAns =
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 2, 0, 0, 2, 0, 2, 0};

    REQUIRE(ans == realAns);
}
