#ifndef MY_BASKET_FOR_STATIC_H
#define MY_BASKET_FOR_STATIC_H
#include "algo.h"
#include "search_engine.h"
size_t API::ingredients_to_recipe::shop_mode = 2;
std::vector<search::product> API::ingredients_to_recipe::res_of_request;
std::vector<search::product>
    API::ingredients_to_recipe::chosen_ingredients;
std::vector<search::Recipe>
    API::ingredients_to_recipe::recommended_recipes;
search::Recipe API::ingredients_to_recipe::chosen_recipe;



#endif  // MY_BASKET_FOR_STATIC_H