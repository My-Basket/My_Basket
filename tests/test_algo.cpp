#include "algo.h"
#include "doctest.h"
TEST_CASE("initialize"){
        CHECK(API::ingredients_to_recipe::show_res_of_request().empty());
        CHECK(API::ingredients_to_recipe::show_recipes().empty());
}