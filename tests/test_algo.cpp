#include "algo.h"
#include "doctest.h"
TEST_CASE("initialize") {
    CHECK(API::ingredients_and_recipes::show_res_of_request().empty());
    CHECK(API::ingredients_and_recipes::show_recipes().empty());
}