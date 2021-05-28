#ifndef MY_BASKET_FOR_STATIC_H
#define MY_BASKET_FOR_STATIC_H
#include "API.h"
#include "search_engine.h"
size_t API::ingredients_and_recipes::shop_mode = 2;  // NOLINT
std::vector<search::product>
    API::ingredients_and_recipes::res_of_prod_request;  // NOLINT
std::vector<search::product>
    API::ingredients_and_recipes::chosen_ingredients;  // NOLINT
std::vector<search::Recipe>
    API::ingredients_and_recipes::recommended_recipes;       // NOLINT
search::Recipe API::ingredients_and_recipes::chosen_recipe;  // NOLINT

#endif  // MY_BASKET_FOR_STATIC_H