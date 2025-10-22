#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/utils/funcs.cpp"

TEST_CASE("power3 small n") {
    CHECK(power3(0) == 1);
    CHECK(power3(1) == 3);
    CHECK(power3(5) == 243);
}

TEST_CASE("a_closed small n") {
    CHECK(a_closedForm(0) == 1);
    CHECK(a_closedForm(1) == 6);
    CHECK(a_closedForm(2) == 27);
    CHECK(a_closedForm(5) == 6 * 243);
    CHECK(a_closedForm(9)) == 196830);
}